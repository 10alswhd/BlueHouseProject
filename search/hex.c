#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/types.h>

int usage () {
	printf ("hex file [params]\n"
	        "  -d Display\n"
		"  -s Search (requires -n NUM_BYTES and bytes list)\n"
		"  -r Replace (requires -o OUTPUT, -a START_ADDRESS, -n NUM_BYTES and bytes list\n\n"
		"hex file -d\n"
		"hex file -s -n 3 75 0e 55\n"
		"hex file -r -o new_file -a 0005da -n 2 90 90\n");
	exit (0);
}

int main (int argc, char *argv[]) {
	int fd,out,i,n;
	unsigned int addr,c;
	__u8 byte,*pattern,*mem;
	if (argc<3) {
		usage ();
	}

	if (!strcmp(argv[2],"-d")) {
		fd = open (argv[1], O_RDONLY);
		if (fd==-1) {
			usage ();
		}
		for (addr=0;read(fd,&byte,1)==1;addr++) {
			if (!(addr%16)) {
				printf ("\n0x%08x: ",addr);
			}
			printf ("%02x ", byte);
		}
		printf("\n");
		close (fd);
	}
	else if (!strcmp(argv[2],"-s")) {
		if (argc<4) {
			usage();
		}
		fd = open (argv[1], O_RDONLY);
		if (fd==-1) {
			usage();
		}
		if (strcmp(argv[3],"-n")) {
			usage();
		}
		n = atoi(argv[4]);
		pattern = malloc(n);
		mem = malloc (n);
		if (pattern==NULL || mem==NULL) {
			return 0;
		}
		for (i=0;i<n;i++) {
			pattern[i] = (__u8)strtol(argv[5+i],NULL,16);
		}
		for (addr=0;read(fd,mem,n)==n;addr++) {
			if (!memcmp(mem,pattern,n)) {
				printf ("0x%08x\n",addr);
			}
			lseek (fd, -(n-1), SEEK_CUR);
		}
		close(fd);
	}
	else if (!strcmp(argv[2],"-r")) {
		if (argc<10) {
			usage();
		}
		if (strcmp(argv[3],"-o") || strcmp(argv[5],"-a") || strcmp(argv[7],"-n")) {
			usage();
		}
		fd = open(argv[1], O_RDONLY);
		out = open(argv[4], O_WRONLY | O_CREAT);
		if (fd==-1 || out==-1) {	
			usage();
		}
		addr = strtol(argv[6],NULL,16);
		n = atoi(argv[8]);
		pattern=malloc(n);
		if (pattern==NULL) {
			return 0;
		}
		for(i=0;i<n;i++) {
			pattern[i]=(__u8)strtol(argv[9+i],NULL,16);
		}
		for (i=0;read(fd,&byte,1)==1;i++) {
			if (i>=addr && i<addr+n) {
				write(out,pattern+(i-addr),1);
			}
			else {
				write(out,&byte,1);
			}
		}
		close(fd);
		close(out);
	}
	return 0;
}
