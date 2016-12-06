#include <stdio.h>

int main(void){
	
	int sayilar[10] = {1,2,3,4,5,6,7,8,9,10};
	int i,search,flag=0;
	
	printf("Aranacak Sayiyi Giriniz :"); scanf("%d",&search);
	
	for(i=0; i<10; i++)
	{
		if(sayilar[i] == search ) 
		{
			flag = 1; break;
		}
		else
		{
			continue ;
		}
	}
	
	
		if(flag == 1)
			{
				printf("Aranan Sayi Dizide Mevcut !");	
			}
			else
			{
				printf("Aranan Sayi Dizide Mevcut Degil !");
			}
	
}
