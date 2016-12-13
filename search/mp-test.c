#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MEMORY_FILE "/dev/mem"

struct floating_pointer {
     char fp_signature[4]; 
     u_int32_t fp_mp_table; 
     u_int8_t fp_length;    
     u_int8_t fp_version;   
     u_int8_t fp_cheksum;   
     u_int8_t fp_sd_config_num;
     u_int8_t fp_imcrp;        
     char unused[3];
};

struct mp_config_header {
     char mpch_signature[4];
     u_int16_t mpch_length; 
     u_int8_t mpch_version;       
     u_int8_t mpch_checksum;      
     char mpch_oem_id[8];         
     char mpch_product_id[12];    
     u_int32_t mpch_oem_table;    
     u_int16_t mpch_oem_table_size;
     u_int16_t mpch_entry_count;   
     u_int32_t mpch_apic_addr;     
     u_int16_t mpch_extended_length;   
     u_int8_t mpch_extended_checksum;
     char mpch_reserved; 
};


struct cpu_entry {
     u_int8_t  entry_type;
     u_int8_t  local_apic_id;   
     u_int8_t  local_apic_version;  
     u_int8_t  cpu_flags;           
     u_int32_t signature;       
     u_int32_t features;        
     char  reserved[8];        
};

struct bus_entry {
     u_int8_t c[8];
};

struct io_apic_entry {
     u_int8_t c[8];
};

struct io_int_entry {
     u_int8_t c[8];
};


struct local_int_entry {
     u_int8_t c[8];
};

enum {
     CPU_ENTRY_ID =  0,
     BUS_ENTRY_ID,
     IO_APIC_ENTRY_ID,
     IO_INT_ENTRY_ID,
     LOCAL_INT_ENTRY_ID,
};

static void show_cpu_info(struct cpu_entry *p)
{
     u_int32_t model = ((p->signature >> 4) & 0xf) + ((p->signature >> 12) & 0xff);
     u_int32_t family = (p->signature >> 8) & 0xf;
     u_int32_t stepping = p->signature & 0x0f;

     putchar('\n');
     printf("CPU is %s\n", p->cpu_flags & 0x02 ? "BSP" : "AP");
     printf("CPU status is %s\n", p->cpu_flags & 0x01 ? "Enable" : "Disable");
     printf("CPU family is 0x%04x model is 0x%04x\n", family, model);
     printf("CPU stepping ix 0x%04x\n", stepping);
     printf("CPU feature flasgs is 0x%08x\n", p->features);
}

static void read_entries(int fd, struct floating_pointer *fps, struct mp_config_header *mpch)
{
     u_int32_t next = 0;
     int entry_count = mpch->mpch_entry_count;
     u_int8_t this;
     struct cpu_entry ce;

     next = fps->fp_mp_table + sizeof(struct mp_config_header);
     while (entry_count-- > 0) {
	  lseek(fd, next, SEEK_SET);
	  read(fd, &this, 1);
	  switch (this) {
	  case CPU_ENTRY_ID:
	       lseek(fd, -1, SEEK_CUR);
	       read(fd, &ce, sizeof(ce));
	       show_cpu_info(&ce);

	       next += sizeof(struct cpu_entry);

	       break;
	  case BUS_ENTRY_ID:
	       next += sizeof(struct bus_entry);
	       break;
	  case IO_APIC_ENTRY_ID:
	       next += sizeof(struct io_apic_entry);
	       break;
	  case IO_INT_ENTRY_ID:
	       next += sizeof(struct io_int_entry);
	       break;
	  case LOCAL_INT_ENTRY_ID:
	       next += sizeof(struct local_int_entry);
	       break;
	  default:
	       entry_count = 0;
	  }
     }

}

static uid_t check_uid(void)
{
     return getuid() == 0;
}

static int check_mptable_signature(struct mp_config_header *mpch)
{
     static const char mpch_sign[] = "PCMP";
     return memcmp(mpch->mpch_signature, mpch_sign, sizeof(mpch_sign) - 1);
}
     
static int check_mptable_checksum(int fd, struct floating_pointer *fps, struct mp_config_header *mpch)
{
     unsigned char checksum = 0;
     unsigned char c = 0;
     int i;

     for (i = 0; i < mpch->mpch_length; i++) {
	  lseek(fd, fps->fp_mp_table + i, SEEK_SET);
	  read(fd, &c, 1);
	  checksum += c;
     }
     // checksum should be zero.
     return checksum;
}

static int check_mp_config_header(int fd, struct floating_pointer *fps, struct mp_config_header *mpch)
{
     if (check_mptable_signature(mpch))
	  return -1;

     return check_mptable_checksum(fd, fps, mpch);
      
}

static void read_mpch(int fd, struct floating_pointer *fps, struct mp_config_header *mpch)
{
     lseek(fd, fps->fp_mp_table, SEEK_SET);
     read(fd, mpch, sizeof(*mpch));
}

static int check_checksum(struct floating_pointer *fps)
{
     unsigned char *data = (unsigned char *) fps;
     unsigned char checksum = 0;
     int i = 0;

     for (i = 0; i < sizeof(struct floating_pointer); i++)
	  checksum+= data[i];

     // if checksum is 0, this is the fps.
     return checksum;
}

static int check_signature(struct floating_pointer *fps)
{
     // The fps signature is "_MP_"
     static const char fps_sign[] = "_MP_";
     return memcmp(fps->fp_signature, fps_sign, sizeof(fps_sign) - 1);
}

static int search_fps_from_given_addr(unsigned long start, unsigned long end, struct floating_pointer *fps, int fd)
{
     unsigned long addr = 0;
     long i = 0;

     lseek(fd, start, SEEK_SET);
     for (addr = start; addr < end; addr += 0x10) {
	  read(fd, fps, sizeof(*fps));
	  if (!check_signature(fps)) 
	       if (!check_checksum(fps))
		    return 0;
     }
     return -1;

}

static int search_fps(int fd, struct floating_pointer *fps)
{
     int ret = search_fps_from_given_addr(0xa0000, 0xfffff, fps, fd);
     if (ret)
	  return search_fps_from_given_addr(0xffffe0000, 0xffffffff, fps, fd);

     return ret;
}


int main(int argc, char **argv)
{
     int fd = 0;
     struct floating_pointer fps;
     struct mp_config_header mpch;

     if (!check_uid()) {
	  fprintf(stderr, "You need to have root privilege to read %s\n", MEMORY_FILE);
	  exit(-1);
     }

     fd = open(MEMORY_FILE, O_RDONLY);
     if (fd < 0) {
	  perror("open");
	  exit(-1);
     }

     memset(&fps, 0x0, sizeof(fps));

     if (search_fps(fd, &fps)) {
	  printf("fps not found\n");
	  return 0;
     }

     read_mpch(fd, &fps, &mpch);

     if (check_mp_config_header(fd, &fps, &mpch)) {
	  printf("mptable not found\n");
	  return 0;
     }

     read_entries(fd, &fps, &mpch);
     close(fd);

     printf("Done.\n");

     return 0;
}
