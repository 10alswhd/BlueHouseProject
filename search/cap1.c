/*
 * Compile just with `gcc -o cap1 cap1.c`
 */


#include <stdio.h>
#include <stdlib.h>


char *get_cap_name(unsigned short cap_index)
{
  static char *dict[] = {
    "CAP_CHMOD",
    "CAP_DAC_OVERRIDE",
    "CAP_DAC_READ_SEARCH",
    "CAP_FOWNER",
    "CAP_FSETID",
    "CAP_KILL",
    "CAP_SETGID",
    "CAP_SETUID",
    "CAP_SETPCAP",
    "CAP_LINUX_IMMUTABLE",
    "CAP_NET_BIND_SERVICE",
    "CAP_NET_BROADCAST",
    "CAP_NET_ADMIN",
    "CAP_NET_RAW",
    "CAP_IPC_LOCK",
    "CAP_IPC_OWNER",
    "CAP_SYS_MODULE",
    "CAP_SYS_RAWIO",
    "CAP_SYS_CHROOT",
    "CAP_SYS_PTRACE",
    "CAP_SYS_PACCT",
    "CAP_SYS_ADMIN",
    "CAP_SYS_BOOT",
    "CAP_SYS_NICE",
    "CAP_SYS_RESOURCE",
    "CAP_SYS_TIME",
    "CAP_SYS_TTY_CONFIG",
    "CAP_MKNOD",
    "CAP_LEASE",
    "CAP_AUDIT_WRITE",
    "CAP_AUDIT_CONTROL",
    "CAP_SETFCAP",
    "CAP_MAC_OVERRIDE",
    "CAP_MAC_ADMIN",
    "CAP_SYSLOG",
    "CAP_WAKE_ALARM",
    "CAP_BLOCK_SUSPEND"
  };

  return dict[cap_index];
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr,
    "Syntax: %s hexa-cap-code.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  unsigned long long cap, mask;
  unsigned short is_enabled, i;
  char *cap_status, *cap_name;

  cap = strtoull(argv[1], NULL, 16);
  printf("capab.: %016llx\n", cap);

  for(mask=1, i=0; i<32; i++, mask<<=1) {
    //printf("mask: %016llx\n", mask);
    is_enabled = (cap & mask) != 0;
    cap_status = is_enabled?"enabled":"disabled";
    cap_name = get_cap_name(i);
    printf("%s(%d) is %s.\n", cap_name, i, cap_status);
  }

  exit(EXIT_SUCCESS);
}
