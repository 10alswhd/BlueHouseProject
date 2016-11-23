/*
//5줄삼각형
#include<stdio.h>

void main()
{
	int fa,fb;

	for(fa=0;fa<5;fa++)
	{
		for(fb=0;fb<=fa;fb++)
		{
			printf("*");
		}
		printf("\n");
	}
}
*/

//5줄역삼각형
/*
#include<stdio.h>

void main()
{
	int fa,fb;
	for(fa=0;fa<5;fa++)
	{
		for(fb=fa;fb<5;fb++)
		{
			printf("*");
		}
		printf("\n");
	}
}
*/
/*
//5줄피라미드
#include<stdio.h>

void main()
{
	int fa,fb,fc;

	for(fa=0;fa<5;fa++)
	{
		for(fb=fa;fb<5;fb++)
		{
			printf(" ");
		}
		for(fc=0;fc<=fa*2;fc++)
		{
			printf("*");
		}
		printf("\n");
	}
}
*/
/*
//역피라미드
#include<stdio.h>

void main()
{
	int fa,fb,fc;

	for(fa=0;fa<5;fa++)
	{
		for(fb=0;fb<fa;fb++)
		{
			printf(" ");
		}
		for(fc=fa*2+1;fc<10;fc++)
		{
			printf("*");
		}
		printf("\n");
	}
}
*/
/*
//다이아
#include<stdio.h>
void main()
{
	int fa,fb,fc;
	
	for(fa=0;fa<5;fa++)
	{
		for(fb=fa;fb<4;fb++)
		{
			printf(" ");
		}
		for(fc=0;fc<=fa*2;fc++)
		{
			printf("*");
		}
		printf("\n");
	}
	for(fa=0;fa<5;fa++)
	{
		for(fb=0;fb<fa;fb++)
		{
			printf(" ");
		}
		for(fc=fa*2+1;fc<10;fc++)
		{
			printf("*");
		}
		printf("\n");
	}	
}
*/
/*
//빈속 다이아
#include<stdio.h>
void main()
{
	int fa,fb,fc,fd;
	for(fa=0;fa<11;fa++)
	{
		printf("*");
	}
	printf("\n");
	for(fa=0;fa<5;fa++)
	{
		for(fb=fa;fb<5;fb++)
		{
			printf("*");
		}
		for(fc=0;fc<fa*2+1;fc++)
		{
			printf(" ");
		}
		for(fd=fa;fd<5;fd++)
		{
			printf("*");
		}
		printf("\n");
	}
	for(fa=0;fa<5;fa++)
	{
		for(fb=0;fb<=fa;fb++)
		{
			printf("*");
		}
		for(fc=fa*2+1;fc<10;fc++)
		{
			printf(" ");
		}
		for(fd=0;fd<=fa;fd++)
		{
			printf("*");
		}
		if(fa==4)
		{
			printf("\n");
			for(fa=0;fa<11;fa++)
			{
				printf("*");
			}
		}
		printf("\n");
	}
}
*/
/*
//실다이아
#include<stdio.h>
void main()
{
	int fa,fb,fc;

	for(fa=0;fa<5;fa++)
	{
		for(fb=fa;fb<5;fb++)
		{
			printf(" ");
		}
		printf("*");
		for(fc=0;fc<fa*2-1;fc++)
		{
			printf(" ");
		}
		if(fa>0)
		{
		printf("*");
		}
		printf("\n");
	}
	for(fa=0;fa<=5;fa++)
	{
		for(fb=0;fb<fa;fb++)
		{
			printf(" ");
		}
		printf("*");
		for(fc=fa*2+1;fc<10;fc++)
		{
			printf(" ");
		}
		if(fa<5)
		{
		printf("*");
		}
		printf("\n");
	}
}
*/
//홀짝
/*
#include<stdio.h>
void main()
{
	int x;
	printf("수를 입력: ");
	scanf("%d",&x);
	if(x%2==0)
	{
		printf("%d : 짝\n",x);
	}
	else
	{
		printf("%d : 홀\n",x);
	}
}
*/
/*
//scanf다이아
#include<stdio.h>
void main()
{
	int s,x,fa,fb,fc;
	printf("몇줄?: ");
	scanf("%d",&s);
	if(s%2==0)
	{
		s=s/2;
		for(fa=0;fa<s;fa++)
		{
			for(fb=fa;fb<s-1;fb++)
			{
				printf(" ");
			}
			for(fc=0;fc<=fa*2;fc++)
			{
				printf("*");
			}
			printf("\n");
		}
		for(fa=0;fa<s;fa++)
		{
			for(fb=0;fb<fa;fb++)
			{
				printf(" ");
			}
			for(fc=fa*2+1;fc<s*2;fc++)
			{
				printf("*");
			}
			printf("\n");
		}
	}
	else
	{
		s=s/2;
		x=s+1;
		for(fa=0;fa<s;fa++)
		{
			for(fb=fa;fb<=s-1;fb++)
			{
				printf(" ");
			}
			for(fc=0;fc<=fa*2;fc++)
			{
				printf("*");
			}
			printf("\n");
		}
		for(fa=0;fa<x;fa++)
		{
			for(fb=0;fb<fa;fb++)
			{
				printf(" ");
			}
			for(fc=fa*2+1;fc<x*2;fc++)
			{
				printf("*");
			}
			printf("\n");
		}

	}
}
*/
//구구단
/*
#include<stdio.h>
void main()
{
	int fa,fb;

	for(fa=1;fa<=9;fa++)
	{
		printf("%d단\n",fa);
		for(fb=1;fb<=9;fb++)
		{
			printf("%d X %d = %d \n",fa,fb,fa*fb);
		}
		printf("\n");
	}
}
*/
//1~100까지 소수 
/* 
#include<stdio.h>
void main()
{
	int fa,fb,c=0;

	for(fa=1;fa<=100;fa++)
	{
		for(fb=1;fb<=100;fb++)
		{
			if(fa%fb==0)
			{
				c++;
			}
		}
		if(c==2)
		{
			printf("[%2d]",fa);
		}
		c=0;
	}
}
*/
//5 5 가로 2차원 배열
/*
#include<stdio.h>

void main()
{
	int bin[5][5],fa,fb,x=1;
	for(fa=0;fa<5;fa++)
	{
		for(fb=0;fb<5;fb++)
		{
			bin[fa][fb]=x++;
		}
	}
	for(fa=0;fa<5;fa++)
	{
		for(fb=0;fb<5;fb++)
		{
			printf("[%2d]",bin[fa][fb]);
		}
		printf("\n");
	}
}
*/
//5 5 세로 2차원 배열
/*
#include<stdio.h>

void main()
{
	int bin[5][5],fa,fb,x=1;
	for(fa=0;fa<5;fa++)
	{
		for(fb=0;fb<5;fb++)
		{
			bin[fb][fa]=x++;
		}
	}
	for(fa=0;fa<5;fa++)
	{
		for(fb=0;fb<5;fb++)
		{
			printf("[%2d]",bin[fa][fb]);
		}
		printf("\n");
	}
}
*/
/*
//빗방울
#include<stdio.h>

void main()
{
	int fa,fb,bin[5][5]={0},x=0,y=0,n=1;
	
	for(fa=0;fa<5;fa++)
	{
		y=0;
		x=0;
		for(fb=0;fb<=fa;fb++)
		{
			if(fb==0)
			{
			y=fa;
			}
			bin[x][y]=n++;
			
			y--;
			x++;
		}
	}

	for(fa=1;fa<=4;fa++)
	{
		y=4;
		x=fa;
		for(fb=fa;fb<=4;fb++)
		{

			if(y==0)
			{
				break;
			}
			bin[x][y]=n++;
			x++;
			y--;	
	
		}
	}
	for(fa=0;fa<5;fa++)
	{
		for(fb=0;fb<5;fb++)
		{
			printf("[%2d]",bin[fa][fb]);
		}
		printf("\n");
	}
}
*/
//팽이 팽이 달팽이
/*
#include<stdio.h>
void main()
{
	int a=4,b,c=1,d=0,e=-1,f=1,g[5][5]={0,};
	while(a!=0)
	{
		for(b=0;b<=a;b++)
		{
			e=e+f;
			g[d][e]=c++;
		}
		a--;
		for(b=0;b<=a;b++)
		{
			d=d+f;
			g[d][e]=c++;
		}
		f=f*-1;
	}
	g[2][2]=25;
	for(a=0;a<=4;a++)
	{
		for(b=0;b<=4;b++)
		{
			if(a==0 ||b==4)
			printf("[0%d]",g[a][b]);
			else
			printf("[%d]",g[a][b]);
		}
		printf("\n");
	}
}
*/
//오름차순 & 내림차순
/*
#include<stdio.h>
void main()
{
	int fa,fb,c,a[10],num;
	
	printf("수를 입력해 주세요:");
	for(fa=0;fa<10;fa++)
	{
		scanf("%d",&a[fa]);
	}
	printf("차수 선택 1.오름차순 2.내림차순:");
	scanf("%d",&num);
	if(num==1)
	{
	for(fa=0;fa<10;fa++)
	{
		for(fb=fa+1;fb<10;fb++)
		{
			if(a[fa]>a[fb])
			{
				c=a[fa];
				a[fa]=a[fb];
				a[fb]=c;
			}
		}
	}
	}
	else if(num==2)
	{
	for(fa=0;fa<10;fa++)
	{
		for(fb=fa+1;fb<10;fb++)
		{
			if(a[fa]<a[fb])
			{
				c=a[fa];
				a[fa]=a[fb];
				a[fb]=c;
			}
		}
	}
	}
	else
	{
		printf("잘못 선택 하셨습니다.");
	}
	for(fa=0;fa<10;fa++)
	{
		printf("[%2d]",a[fa]);
	}
}

*/

//아스키값
/*
#include<stdio.h>

void main()
{
	char bin[3];
	
	scanf("%c %c %c",&bin[0],&bin[1], &bin[2]);

	printf("[%c: %d] [%c: %d] [%c: %d]",bin[0],bin[0],bin[1],bin[1],bin[2],bin[2]);
}
*/

