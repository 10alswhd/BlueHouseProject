#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef struct RSDPDescriptor20 {
	char		Signature[8];
	uint8_t		Checksum;
	char		OEMID[6];
	uint8_t		Revision;
	uint32_t	RsdtAddress;

	uint32_t	Length;
	uint64_t	XsdtAddress;
	uint8_t		ExtendedChecksum;
	uint8_t		reserved[3];
} Rsdp_20, *PtrRsdp_20;

static const off_t		ShadowSeg = 0xe0000;
static const size_t		ShadowSize = 0x20000;
static const size_t		RsdpBound = 0x10;
static const char		RsdPtrSig[] = { 'R', 'S', 'D', ' ', 'P', 'T', 'R', ' ' };

static int		FdMem = -1;
static Rsdp_20	Rsdp;

int main(int argc, char **argv)
{
	ssize_t	size;
	FdMem = open("/dev/mem", O_RDONLY);

	if (FdMem < 0) return -1;

	for (uint32_t i = ShadowSeg; i < ShadowSeg + ShadowSize - sizeof(RsdPtrSig); i += RsdpBound) {
		size = pread(FdMem, &Rsdp, sizeof(Rsdp_20), i);
		if (size == sizeof(Rsdp_20) && 0 == memcmp(Rsdp.Signature, RsdPtrSig, sizeof(RsdPtrSig))) {
			printf("Found \"RSD PTR\" at %08X\n", i);
			printf("  RSDT -> %08X\n", Rsdp.RsdtAddress);
			printf("  XSDT -> %016lX\n", Rsdp.XsdtAddress);
		}
	}

	close(FdMem);
	return 0;
}
