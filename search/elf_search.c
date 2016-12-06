#include <stdio.h>
#include <elf.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void hoge(){
  printf("hoge!\n");
}

int main(void){
  char filename[] = "a.out";
  hoge();

  // search hoge address

  // file read
  struct stat st;
  stat(filename, &st);
  int size = st.st_size;
  char *buf = malloc(size);
  FILE *fp = NULL;
  if((fp = fopen(filename, "rb")) == NULL){
      printf("read error\n");
      return -1;
  }
  fread(buf, size, 1, fp);
  fclose(fp);
  
  //printf("%c%c%c\n", buf[1],buf[2],buf[3]);

  
  // get ELF_header e_shoff
  Elf64_Ehdr *header = (Elf64_Ehdr *)buf;
  
  // get Section_header
  Elf64_Shdr *shdr_start = (Elf64_Shdr *)(buf + header->e_shoff);
  Elf64_Shdr *shdr_shstrtab = shdr_start + header->e_shstrndx;
  char *shstrtab = buf + shdr_shstrtab->sh_offset;
  Elf64_Shdr *shdr_symtab = NULL;
  Elf64_Shdr *shdr_strtab = NULL;
  

  printf("strtb_sec name = %s\n", shstrtab + shdr_shstrtab->sh_name);
  
  // if *sh_name == ".symtab" then sh_offset
  for(int i=0;i<header->e_shnum;i++){
    Elf64_Shdr *shdr = shdr_start + i;
    char *shname = shstrtab + shdr->sh_name;
    //    printf("%s\n", shname);
    if(strncmp(shname, ".symtab", 100) == 0){
      //printf("section = %s\n", shname);
      shdr_symtab = shdr;
    }
    if(strncmp(shname, ".strtab", 100) == 0){
      //printf("section = %s\n", shname);
      shdr_strtab = shdr;
    }
  }
  if(shdr_symtab == NULL || shdr_strtab == NULL){
    // not found
    return -1;
  }

  char *strtab = buf + shdr_strtab->sh_offset;

  // get symbol_table
  // if *st_name == "hoge" then st_value
  Elf64_Sym *symtb_start = (Elf64_Sym *)(buf + shdr_symtab->sh_offset);
  for(int i=0;i<(shdr_symtab->sh_size/sizeof(Elf64_Sym));i++){
    Elf64_Sym *symtb = symtb_start + i;
    char *symname = strtab + symtb->st_name;
    printf("%s = %x\n", symname, symtb->st_value);
  }
  
  free(buf);
  
  return 0;
}
