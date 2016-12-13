#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>
#include "prlib.h"

#define PROTOLOG "protolog.txt"
#define SHAKESPERE "shakespere.txt"
#define LINEM 81

int top = -1 ; // top for Proto's Stack.
time_t protos_time;

void poem()
{
    FILE *pt;
    int j,c = '\n';
    char *line[LINEM];

    pt = fopen(SHAKESPERE,"r");


    c = fgetc(pt);
    while(c != EOF)
    {
        printf("%c",c);
        c=fgetc(pt);
    }
    fclose(pt);

}

void rst()
{
    FILE *fp;
    fp = fopen(PROTOLOG,"w");
    fclose(fp);
}

void log()
{
    int c;
    protos_time = time(NULL);
    printf(ctime(&protos_time));

    FILE *m ;
    m=fopen(PROTOLOG,"r");
    c = fgetc(m);
    if(c != EOF)
    {
        printf("User : \n");

        do
        {
            printf("%c",c);
            c = fgetc(m);
        } while(c != EOF);
        printf("\n\tProto.(written in C)\n");
        fclose(m);
    }

    else
    {
        char name[10],secname[15];
        FILE *p = fopen(PROTOLOG,"w") ;
        if( p == NULL)
        {
            printf("Error opening log..\n");
            exit(1);
        }

        printf("What 's your first name?\n");
        scanf("%s",&name);
        printf("What 's your second name?\n");
        scanf("%s",&secname);
        fprintf(p,"%s ",name);
        fprintf(p,"%s.",secname);

        fclose(p) ;
        }

}

void isEmpty(int a[])
{
    if(top == -1)
        printf("Your stack is empty !\n") ;
    else
        printf("Stack is not empty it contains %d elements.",top+1);
}

void pop(int a[],int n)
{
    if(top != -1)
    {
        top -= 1;
        printf("element removed.\n");
    }

    else
        printf("Your stuck is empty.!\n");
}

void push(int a[],int n)
{
     int p ;

     if(top != n-1)
     {
        printf("Enter the number to pop in stuck.\n");
        scanf("%d",&p);
        a[top+1]=p;
        top += 1;
    }
    else
        printf("Your stuck is full.\n");
}

void show(int a[],int n)
{
    int i ;

    printf("Your stuck is: ");
    for(i = 0; i < top+1; i++)
        printf("%3d ",a[i]);
    printf("\n");
}

void shutdown()
{
    printf("Shuting down.\n");

}

void Protostack()
{
    int N = 10;
    int stuck[N];
    int answer = 1;

    while (answer != 5)
    {
        printf("Enter your choice: \n");
        printf("1.Push \n");
        printf("2.Pop \n");
        printf("3.Show \n");
        printf("4.IsEmpty\n");
        printf("5.Exit \n");

        scanf("%d",&answer);

        switch(answer){
            case 1:
                push(stuck,N);
                break;
            case 2:
                pop(stuck,N);
                break;
            case 3:
                show(stuck,N);
                break;
            case 4:
                isEmpty(stuck);
                break;
            case 5:
                shutdown();
                break;
            }
    }
}

void tpsearch()
{
    int i,j,counter,N ;
    int *psize ;
    printf("Prime_PLUS2_BePrime.\n") ;
    printf("Performing a search from 2 up to a\ngiven number,to get all\n") ;
    printf("primes,and checking out if ,\na prime added to 2 is prime.\n") ;

    printf("Enter the limit of your search(integer)\n") ;
    scanf("%d",&N) ;

    for(i=2,counter=0; i<N ; i++)
        if(isPrime(i))
              counter++ ;
    //printing counted primes in between 2-N(without N).
    printf("Primes counted %d .\n",counter) ;
    //getting dynamically an array to store the primes.
    psize = malloc(counter*sizeof(int)) ;

     for(i=2,counter=0; i<N ; i++)
        if(isPrime(i)){
             psize[counter]=i ;
             counter++ ;
        }

    printf("\n\t TWIN PRIMES Search.\n");
    for(i=0; i<counter ; i++)
    {
        if(isPrime(psize[i]+2))
            printf("%d +2 = %d\t\t %d,%d \n",psize[i],psize[i]+2,psize[i],psize[i]+2) ;
    }
    //Shuting down message.
    printf("\n\nOperation completed.\n") ;
}

void newLine()
{
    printf("\n");
}

void manual()
{
    printf("-----------------Listing Proto 's operations.--------------\n-----------------------------------------------------------");
    printf("\n");
    protos_time = time(NULL);
    printf(ctime(&protos_time));
    printf("\n");
    printf("\thelp - prints out manual 's functions.\n");
    printf("\tlog - user's details.\n");
    printf("\tpoem - read a poem by Shakespeare.\n");
    printf("\ttps - searching twin primes up to given limit.\n");
    printf("\tstack - implementation of Proto's stack 10 elements.\n");
    printf("\trst - reseting log 's data.\n");
    printf("\texit - shutting down Proto.\n");
    printf("---> ");
}

void help()
{
    printf("Welcome to Proto's Help.\n");
    manual();
}

void greet()
{
    printf("Welcome.\n\t-Proto.\n");
}

void cls()
{
    printf("\nGoodbye\n\t-Proto.");
}

int main(void)
{

    char rd[64];
    greet();
    newLine();

    while(1)
    {
        manual();
        scanf("%64s",&rd);
        if(!strncmp(rd,"help",sizeof(rd)))
            help();

        if(!strncmp(rd,"exit",sizeof(rd)))
            break;

        if(!strncmp(rd,"tps",sizeof(rd)))
            tpsearch();

        if(!strncmp(rd,"stack",sizeof(rd)))
            Protostack();

        if(!strncmp(rd,"log",sizeof(rd)))
            log();

        if(!strncmp(rd,"rst",sizeof(rd)))
            rst();
        if(!strncmp(rd,"poem",sizeof(rd)))
            poem();
        else
            newLine();
    }
    cls();
    return (0);
}
