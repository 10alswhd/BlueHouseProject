
#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{   
    printf("%lld\n",atoll("12345678901234567"));
    printf("%lld\n",atoll("-12345678901234567"));
    printf("%lld\n",atoll("12345678901234567ab"));
    printf("%lld\n",atoll("ab12345678901234567"));   
 
    return 0;
}
