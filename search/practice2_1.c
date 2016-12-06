#include <stdio.h>

int main(void)
{
    /*initialization*/
    int i;
    int cnt = 0;
    char input_str[10];
    char search_str[1];
    
    /*input*/
    printf("input string...");
    fgets(input_str, 10, stdin);
    
    printf("Search character...");
    scanf("%s", search_str);
    
    /*output format*/
    printf("Character [%s] Count =", search_str);
    
    /*calculation*/
    for(i=0; i<10; i++)
    {
        if(input_str[i]==search_str[0]) cnt = cnt + 1;
    }

	/*output*/
	printf("%d\n", cnt);
	
	for(i=0; i<10; i++)
	{
	    fputs(input_str, stdout);
	    if(input_str[i]==search_str[0]) printf("*");
	}
	
    return 0;
}
