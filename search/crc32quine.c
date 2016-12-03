#include<stdio.h>
#include<stdint.h>

#ifdef CAPITAL
#define CHAR_A 'A'
#define FORMAT "%08X\n"
#else
#define CHAR_A 'a'
#define FORMAT "%08x\n"
#endif

#define hexchar(c) ((unsigned char)((c)<10?(c)+'0':(c)-10+CHAR_A))

#define crc32(crc, n) (crc_table[((crc)^(n))&0xff]^((crc)>>8))

#define POLYNOMIAL 0xedb88320

void crc_init(uint32_t *crc_table)
{
    unsigned int i;
    for(i=0; i<0x100; i++){
	uint32_t crc=i;
	int j;
	for(j=0; j<8; j++){
	    uint32_t shift1=crc>>1;
	    crc=crc&1?shift1^POLYNOMIAL:shift1;
	}
	crc_table[i]=crc;
    }
}

int main()
{
    uint32_t crc_table[0x100];
    uint32_t crc0=~0;

    crc_init(crc_table);

    unsigned char i1;
    for(i1=0; i1<0x10; i1++){
	uint32_t crc1=crc32(crc0,hexchar(i1));

	unsigned char i2;
	for(i2=0; i2<0x10; i2++){
	    uint32_t crc2=crc32(crc1,hexchar(i2));

	    unsigned char i3;
	    for(i3=0; i3<0x10; i3++){
		uint32_t crc3=crc32(crc2,hexchar(i3));

		unsigned char i4;
		for(i4=0; i4<0x10; i4++){
		    uint32_t crc4=crc32(crc3,hexchar(i4));

		    unsigned char i5;
		    for(i5=0; i5<0x10; i5++){
			uint32_t crc5=crc32(crc4,hexchar(i5));

			unsigned char i6;
			for(i6=0; i6<0x10; i6++){
			    uint32_t crc6=crc32(crc5,hexchar(i6));

			    unsigned char i7;
			    for(i7=0; i7<0x10; i7++){
				uint32_t crc7=crc32(crc6,hexchar(i7));

				unsigned char i8;
				for(i8=0; i8<0x10; i8++){
				    uint32_t crc8=crc32(crc7,hexchar(i8));
#ifdef CR
				    crc8=crc32(crc8,'\r');
#endif
#ifdef LF
				    crc8=crc32(crc8,'\n');
#endif
				    uint32_t i0=(i1<<28)|(i2<<24)|(i3<<20)
					|(i4<<16)|(i5<<12)|(i6<<8)|(i7<<4)|i8;
				    if(~crc8==i0){
					printf(FORMAT, i0);
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    return 0;
}
