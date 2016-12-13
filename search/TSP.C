#include<math.h>
#include<stdio.h>
#include <stdlib.h>
#define N 5//定义城市的个数 
#define M (N-1)*(N-2)/2+1 //定义城市交换的次数 
int gCityDistance[5][5]={{0,10,7,12,4},{10,0,8,2,9},{7,8,0,20,15},{12,2,20,0,5},{4,9,15,5,0}};
char gCity[N]={'A','B','C','D','E'};
int gCityNum[N]={0,1,2,3,4};
int gTravelDistance[M]={0};
char FirstWay[N]={0};
int BestDis;
int gindex;
char BestWay[N]={0};
int BestWayNum[N]={0};
int FirstWaynum[N]={0};
/*************交换城市***********/ 
void swap(char *i,char *j)
{
	char temp;
	temp=*i;
	*i=*j;
	*j=temp;
}
/************交换城市对应的数字*************/ 
void swapnum(int *i,int *j)
{
	int temp;
	temp=*i;
	*i=*j;
	*j=temp;
}
/**************打印城市路径*************/ 
void showcity(char cityarray[])
{
	int n;
	for(n=0;n<N;n++)
	printf("%c",cityarray[n]);
	printf("\t");
}
/*************打印城市对应的数字***************/ 
void showcitynum(int a[])
{
	int n;
	for(n=0;n<N;n++)
	printf("%d",a[n]);
	printf("\t");
	
}
/***************数组之间的赋值,用于缓存城市路径*************/ 
void cityfuzhi(char a[],char b[])
{   
    int n;
	for(n=0;n<N;n++)
    a[n]=b[n];
}
/****************缓存数字*****************/ 
void citynumfuzhi(int a[],int b[])
{
	int n;
	for(n=0;n<N;n++)
	a[n]=b[n];
}
/**************比较两数组是否相等，若相等则返回1否则返回0***************/ 
int equal(int a[],int b[])
{
	int n;
	for(n=0;n<N;n++)
	{
	if(a[n]!=b[n])
	return 0;
	}
	return 1;
}
/***********计算路径*************/ 
int calculatedistance(int CityNum[])
{   
    int n;
    int Dis=0;
	for(n = 0;n < N;n++)
   {
	 if(n == N-1)
     CityNum[ n+1 ]=0;//终点回到初始点的路程 
	 Dis += gCityDistance[ CityNum[n] ][ CityNum[n+1] ];
   }
   return Dis;
}
/**************局部搜索算法***************/ 
void NeighborSearch(char city[],int cityNum[],int num)
{   int j;
	int n;
	int k; 
	int Dis=0,FirstDis=0;

    gindex=0; 						 //循环次数清零
    showcity(city); 				 //打印最初的城市
   	//showcitynum(cityNum);		     // 打印最初的城市对应的数字 
    cityfuzhi(BestWay,city);		 //将初始城市顺序先赋值为最佳路径 
    citynumfuzhi(BestWayNum,cityNum);//对应的数字 
    Dis=calculatedistance(cityNum);//计算初始路径
    printf("%d\n",Dis);
    gTravelDistance[gindex]=Dis;
    FirstDis=Dis; 
    BestDis=FirstDis;
  
    for(k=1;k<=num;k++)
	{   
	    for(j=k+1;j<=num;j++)
		{   
			Dis=0;
			gindex++;
			/***********交换城市***************/ 
		    swap(&city[k],&city[j]);
		    swapnum(&gCityNum[k],&gCityNum[j]);//交换城市对应的数字，为计算路径做准备  
		    /************打印城市*************/ 
			showcity(city);
			//showcitynum(cityNum);
			Dis=calculatedistance(cityNum);
			printf("%d\n",Dis);
			gTravelDistance[gindex]=Dis;
           /**********每计算出一次路径都进行比较是否是最短路径************/ 
			if(Dis<BestDis)
			{
				BestDis=Dis;
				cityfuzhi(BestWay,city);
				citynumfuzhi(BestWayNum,cityNum);
			}
			else
			{
				BestDis=BestDis;
				cityfuzhi(BestWay,BestWay);
				citynumfuzhi(BestWayNum,BestWayNum);
			}
			/***********换回来,为下一次交换做准备***********/ 
			swap(&city[k],&city[j]);
		    swapnum(&cityNum[k],&cityNum[j]);
		}
	}
}
/****************打印城市路径矩阵*********************/ 
void showmatrix()
{
	 int i,j;
    for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			printf("%3d",gCityDistance[i][j]);
		}
			printf("\n");
	}
}
int main()
{ 
     int i,j,n;
     int fuck;
     showmatrix();
     for(fuck=0;fuck<1000;fuck++) 
     {       
             NeighborSearch(gCity,gCityNum,N-1); 

		 	/*
             for(i=0;i<M;i++)
			 printf("%5d",gTravelDistance[i]);
			 printf("\n");*/
		     printf("bestway:");
		     showcity(BestWay);
		     printf("Best:%d\n",BestDis);
		     
	         if(equal(gCityNum,BestWayNum))//终止条件：如果这一次全邻域搜索的最短路径和上一次相等则跳出循环 
             break;
       
		     cityfuzhi(gCity,BestWay);//把这一次的最段路径的城市顺序赋给gCity以作为下一次循环的初始城市 
             citynumfuzhi(gCityNum,BestWayNum);
     }
}
