#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

// ARM Linux defines
#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

// memory defines
#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd;
void *gpio_map;
volatile unsigned *gpio;

#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

int digitalReadGpio(int pin);
void noop();
void setup_io();
void delayMicrosec (unsigned int howLong);

int main()
{
  setup_io(); 		// Set up gpio pointer for direct register access

  INP_GPIO(17); 	// must use INP_GPIO before we can use OUT_GPIO

  int i;
  int j = 0;
  //int _sync[24] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  //int _syncSearch[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  int _sync[32] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int _syncSearch[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  while(1 == 1)
  { 
    for(i = 1; i <= sizeof(_syncSearch)/sizeof(_syncSearch[0]); i++)
	  _syncSearch[i-1] = _syncSearch[i];
  
    _syncSearch[sizeof(_syncSearch)/sizeof(_syncSearch[0])] = digitalReadGpio(17);
	
	for(i = 0; i <= sizeof(_syncSearch)/sizeof(_syncSearch[0]); i++)
	  printf("%d", _syncSearch[i]);
	printf("\n");
	
	
	
	;
	if(memcmp(_sync, _syncSearch, sizeof(_syncSearch)) > 31)
	  printf("SYNC!\n");
	
	delayMicrosec(350); //freq des senders
	
	if(j > 1)
	  break;
  }
  
  
  
  /*
  
  //
  //int _syncSearch[32];
  
  int _sync[32] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  
  
  
    
  
  
  
    for(i = 0; i <= sizeof(_sync)/sizeof(_sync[0]); i++)
	  printf("%d", _sync[i]);
	  
	printf("\n");
	
	_sync = SchiebWertInArray(_sync, 1);
 
    for(i = 0; i <= sizeof(_sync)/sizeof(_sync[0]); i++)
	  printf("%d", _sync[i]);
	  
	printf("\n");
  */
  /*while(1 == 1)
    {
	  x = x + 1;
	  //printf("i");
	  if(digitalReadGpio(17) == 1)
		printf("1");
      else
	    printf("0");
      
	  printf("\nloop #%d\n", x);
	  delayMicrosec(350);
	  
	  //noop();
	}*/
}

/*int* SchiebWertInArray(int[*] array, int wert)
{
  int i;
  for(i = 1; i < sizeof(array)/sizeof(array[0]); i++)
	array[i-1] = array[i];
  
  array[sizeof(array)/sizeof(array[0])]=wert;
  
  return array;
}*/

void noop(){}

/*int CompareDemArrays(int *x, int *y)
{
  int i;
  for(i=0; i<sizeof(x)/sizeof(x[0]);i++)
    if(x[i] != y[i])
	  return 0;
  
  return 1;
}*/

void delayMicrosec (unsigned int howLong)
{
  struct timespec sleeper ;

  /**/ if (howLong ==   0)
    return ;
  else if (howLong  < 100) //we cannot sleep below 100 microsec with this code.
    return ;
  else
  {
    sleeper.tv_sec  = 0 ;
    sleeper.tv_nsec = (long)(howLong * 1000) ;
    nanosleep (&sleeper, NULL) ;
  }
}

int digitalReadGpio (int pin)
{
  pin &= 63 ;

  if ((*(gpio + 13) & (1 << (pin & 31))) != 0) // + 13 // + 14
    return 1 ;
  else
    return 0 ;
}

void setup_io()
{
   
   /* open /dev/mem */
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }

   /* mmap GPIO */
   gpio_map = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );

   close(mem_fd); //No need to keep mem_fd open after mmap

   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);//errno also set!
      exit(-1);
   }

   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;
} // setup_io
