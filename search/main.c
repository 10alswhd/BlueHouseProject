#define PATTERNBYTE1 0xAA
#define PATTERNBYTE2 0xBB
#define PATTERNBYTEC 0xCC

int main(void)
{
  char *pointer=(char*)0x20000000; //Framebuffer address is over this address
  char *Address_of_thing_were_searching_for = 0;// 0 = NULL
  
  int i = 0;
  
  while(1==1)
  {
    //Hmm.. is this better now?
    if(pointer[i]==PATTERNBYTE1 && pointer[i+1]==PATTERNBYTE2 && pointer[i+2]==PATTERNBYTE3 )
    {
          Address_of_thing_were_searching_for = &pointer[i];
          break;
    }
    
  i++;
  }

/*Try write the framebfufers..*/

}
