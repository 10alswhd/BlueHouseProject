include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>              /* fcntl */
#include <sys/mman.h>           /* mmap */
#include <sys/ioctl.h>          /* fopen/fread */
#include "vpu_io.h"
#include "vpu_lib.h"

#define NUM_INPUT_BUF           3

#define SPS_HDR                 0
#define PPS_HDR                 1

#define BUFF_FILL_SIZE          (64 * 1024)
#define DEFAULT_HEIGHT          360
#define DEFAULT_WIDTH           640
#define DEFAULT_FRAME_RATE      30
#define DEFAULT_GOP_SIZE        30
#define VPU_DEFAULT_H264_QP     25

#define H264_QP_MAX             51
#define H264_QP_MIN             21

int main(void){
    int ret = 0, i;
    vpu_versioninfo ver;            // vpu version information
    vpu_mem_desc bit_stream_buf;    // input bit stream allocated memory
    vpu_mem_desc source_buf;        // source buffer allocated memory
    FrameBuffer source_frame;       // source framebuffer

    // VPU specific members defined in vpu_lib.h
    EncHandle *handle = malloc(sizeof(EncHandle));
    EncOpenParam *encOP = malloc(sizeof(EncOpenParam));
    EncInitialInfo *initialInfo = malloc(sizeof(EncInitialInfo));
    EncOutputInfo *outputInfo = malloc(sizeof(EncOutputInfo));
    EncParam *encParam = malloc(sizeof(EncParam));

    // Set allocated memory to zero
    memset (initialInfo, 0, sizeof (EncInitialInfo));
    memset (encParam, 0, sizeof (EncParam));
    memset (encOP, 0, sizeof (EncOpenParam));
    memset (outputInfo, 0, sizeof (EncOutputInfo));
    memset (&bit_stream_buf, 0, sizeof (vpu_mem_desc));

    // Init VPU
    if(vpu_Init (NULL) < 0) {
        printf(">> failed to call vpu_Init()\n");
        ret = -1;
        goto free;
    }
    vpu_GetVersionInfo(&ver);
    printf("VPU Version: firmware %d.%d.%d; libvpu: %d.%d.%d \n", ver.fw_major,
              ver.fw_minor, ver.fw_release, ver.lib_major, ver.lib_minor,
              ver.lib_release);

    // Allocate input buffer
    bit_stream_buf.size = BUFF_FILL_SIZE;
    IOGetPhyMem (&bit_stream_buf);
    if(bit_stream_buf.phy_addr == 0) {
        printf(">> error allocating encoder bitstream buffer\n");
        ret = -1;
        goto free;
    }
    IOGetVirtMem (&bit_stream_buf);

    // Set up encoder operation parameters
    encOP->bitstreamBuffer = bit_stream_buf.phy_addr;
    encOP->bitstreamBufferSize = BUFF_FILL_SIZE;
    encOP->bitstreamFormat = STD_AVC;
    encOP->gopSize = DEFAULT_GOP_SIZE;
    encOP->rcIntraQp = VPU_DEFAULT_H264_QP;
    encOP->userQpMaxEnable = 1;
    encOP->userQpMax = H264_QP_MAX;
    encOP->userQpMinEnable = 1;
    encOP->userQpMin = H264_QP_MIN;
    encOP->frameRateInfo = DEFAULT_FRAME_RATE;
    encOP->picWidth = DEFAULT_WIDTH;
    encOP->picHeight = DEFAULT_HEIGHT;
    encOP->ringBufferEnable = 0;

    // Open encoder
    vpu_EncOpen (handle, encOP);

    // Configure IRAM memory
    SearchRamParam search_pa = { 0 };
    iram_t iram;
    int ram_size;
    memset (&iram, 0, sizeof (iram_t));
    ram_size = ((DEFAULT_WIDTH + 15) & ~15) * 36 + 2048;
    IOGetIramBase (&iram);
    if ((iram.end - iram.start) < ram_size)
      ram_size = iram.end - iram.start;
    search_pa.searchRamAddr = iram.start;
    search_pa.SearchRamSize = ram_size;
    vpu_EncGiveCommand (*handle, ENC_SET_SEARCHRAM_PARAM, &search_pa);

    vpu_EncGetInitialInfo (*handle, initialInfo);

    // Disable rotation/mirroring
    vpu_EncGiveCommand (*handle, DISABLE_ROTATION, 0);
    vpu_EncGiveCommand (*handle, DISABLE_MIRRORING, 0);

    // Allocate memory for source frame buffer
    source_buf.size = DEFAULT_WIDTH * DEFAULT_HEIGHT * 3/2;
    IOGetPhyMem (&source_buf);
    if(source_buf.phy_addr == 0) {
        printf(">> error allocating source frame buffer\n");
        ret = -1;
        goto close;
    }
    IOGetVirtMem(&source_buf);
    source_frame.strideY = DEFAULT_WIDTH;
    source_frame.strideC = DEFAULT_WIDTH >> 1;
    source_frame.bufY = source_buf.phy_addr;
    source_frame.bufCb = source_frame.bufY + DEFAULT_WIDTH * DEFAULT_HEIGHT;
    source_frame.bufCr = source_frame.bufCb + (DEFAULT_WIDTH * DEFAULT_HEIGHT >> 2);
    printf("source frame buffer %i phys(%p) virt(%p)\n", 0, source_buf.phy_addr, source_buf.virt_uaddr);

    // Get number of destination frame buffers and allocate
    int num = initialInfo->minFrameBufferCount;
    printf("number of needed frame buffers: %d\n", num);

    vpu_mem_desc *framedesc = malloc(sizeof(vpu_mem_desc) * num);
    FrameBuffer *frame = malloc(sizeof(FrameBuffer) * num);
    memset (framedesc, 0, (sizeof (vpu_mem_desc) * num));
    memset (frame, 0, (sizeof (FrameBuffer) * num));

    // Allocate each destination frame buffer
    for (i = 0; i < num; i++) {
        framedesc[i].size = DEFAULT_WIDTH * DEFAULT_HEIGHT * 3/2;
        IOGetPhyMem (&(framedesc[i]));
        if (framedesc[i].phy_addr == 0) {
            printf(">> error allocating destination frame buffers\n");
            ret = -1;
            goto frame;
        }
        IOGetVirtMem (&(framedesc[i]));
        frame[i].strideY = DEFAULT_WIDTH;
        frame[i].strideC = DEFAULT_WIDTH >> 1;

        frame[i].bufY = framedesc[i].phy_addr;
        frame[i].bufCb = frame[i].bufY + (DEFAULT_WIDTH * DEFAULT_HEIGHT);
        frame[i].bufCr = frame[i].bufCb + ((DEFAULT_WIDTH * DEFAULT_HEIGHT) >> 2);
        printf("destination frame buffer %i phys(%p) virt(%p)\n", i, framedesc[i].phy_addr, framedesc[i].virt_uaddr);
    }

    // Register allocated frame buffers
    vpu_EncRegisterFrameBuffer (*handle, frame, num, DEFAULT_WIDTH, DEFAULT_WIDTH, 0, 0, NULL);

    encParam->forceIPicture = 0;
    encParam->skipPicture = 0;
    encParam->enableAutoSkip = 0;
    encParam->quantParam = VPU_DEFAULT_H264_QP;

    // Get encoding Headers
    EncHeaderParam enchdr_param = { 0 };
    uint8_t *ptr;
    uint8_t *header[NUM_INPUT_BUF];
    uint32_t headersize[NUM_INPUT_BUF];      // size for each header element

    enchdr_param.headerType = SPS_RBSP;
    vpu_EncGiveCommand (*handle, ENC_PUT_AVC_HEADER, &enchdr_param);
    headersize[SPS_HDR] = enchdr_param.size;
    header[SPS_HDR] = malloc (enchdr_param.size);
    if (header[SPS_HDR] == NULL) {
      printf (">> error in allocating memory for SPS_RBSP Header" );
      ret = -1;
      goto frame;
    }
    ptr = (uint8_t*) (bit_stream_buf.virt_uaddr + enchdr_param.buf - bit_stream_buf.phy_addr);
    memcpy (header[SPS_HDR], ptr, enchdr_param.size);
    printf("header[SPS_HDR]: %d bytes\n",  headersize[SPS_HDR]);

    enchdr_param.headerType = PPS_RBSP;
    vpu_EncGiveCommand (*handle, ENC_PUT_AVC_HEADER, &enchdr_param);
    headersize[PPS_HDR] = enchdr_param.size;
    header[PPS_HDR] = malloc (enchdr_param.size);
    if (header[PPS_HDR] == NULL) {
      printf (">> error in allocating memory for PPS_HDR Header" );
      ret = -1;
      goto frame;
    }
    ptr = (uint8_t*) (bit_stream_buf.virt_uaddr + enchdr_param.buf - bit_stream_buf.phy_addr);
    memcpy (header[PPS_HDR], ptr, enchdr_param.size);
    printf("header[PPS_HDR]: %d bytes\n",  headersize[PPS_HDR]);

    // Open output file and write headers
    FILE *out = fopen ("BigBuckBunny_640x360_small.h264", "w"); //stdout
    fwrite(header[SPS_HDR], 1, headersize[SPS_HDR], out);
    fwrite(header[PPS_HDR], 1, headersize[PPS_HDR], out);

    // Copy and Encode
    FILE *in = fopen ("BigBuckBunny_640x360_small.yuv", "r");
    while(fread((void*) source_buf.virt_uaddr, 1, DEFAULT_WIDTH * DEFAULT_HEIGHT * 3/2, in)) {
        encParam->sourceFrame = &source_frame;

        // Encode a single frame
        vpu_EncStartOneFrame (*handle, encParam);
        while(vpu_IsBusy()) {
            vpu_WaitForInt (100);
        }

        vpu_EncGetOutputInfo (*handle, outputInfo);

        // Write bitstream to file
        fwrite((void*) bit_stream_buf.virt_uaddr, 1, outputInfo->bitstreamSize, out);
    }
    printf("\n");
    fclose(in);
    fclose(out);
frame:
    for (i = 0; i < num; i++) {
        IOFreeVirtMem(&(framedesc[i]));
        IOFreePhyMem(&(framedesc[i]));
    }
    free(frame);
    free(framedesc);
close:
    // Close encoder
    vpu_EncClose (*handle);

    // Free alocated input buffer
    IOFreeVirtMem (&bit_stream_buf);
    IOFreePhyMem (&bit_stream_buf);
free:
    free(encOP);
    free(initialInfo);
    free(outputInfo);
    free(encParam);
    free(handle);
    return ret;
}
