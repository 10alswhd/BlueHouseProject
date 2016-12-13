/* Simple Packet Dump Program Using libpcap */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

int main(void) 
{
  struct pcap_pkthdr header;    //Packet Header Structure for pcap
  const u_char *packet_data;    //Pointer to Packet Data Buffer
  char errbuf[PCAP_ERRBUF_SIZE];    //Buffer for Error Message
  char *device;    //Network Device for Capturing Packets
  pcap_t *pcap_handle;    //Packet Capture Descripter

  /* Search Suitable Device for Capturing Packets */
  device = pcap_lookupdev(errbuf);
  if (device == NULL) {
    fprintf(stderr, "%s\n", errbuf);
    exit(1);
  }

  /* Open Packet Capturing Device */
  pcap_handle = pcap_open_live(device, 1518, 1, 1000, errbuf);
  if (pcap_handle == NULL) {
    fprintf(stderr, "%s\n", errbuf);
    exit(1);
  }

  printf("Capturing on %s\n", device);

  while(1) {
    /* Capture Packets */
    packet_data = pcap_next(pcap_handle, &header);
    printf("Got a %d byte packet\n", header.len);

    /* Dump Packet Data */

    unsigned int i, j, length;

    length = header.len;

    for (i = 0; i < length; i++) {
      if((i % 16) == 0)
	printf("%#07x: ", i);    //Print Offset
      
      printf("%02x ", packet_data[i]);    //Print Data in Hex Format
      
      /* Print Data in ASCII Format */
      if (((i % 16) == 15) || (i == length - 1)) {
	for (j = 0; j < 15 - (i % 16); j++)
	  printf("   ");
	printf(" |");
	for (j = (i - (i % 16)); j <= i; j++)
	  if ((packet_data[j] > 31) && (packet_data[j] < 127)) {
	      printf("%c", packet_data[j]);
	    } else {
	      printf(".");
	    }
	    printf("|\n");
	  }
    }
  }

  /* Close Packet Capture Descripter */
  pcap_close(pcap_handle);
  
  return(0);
}
