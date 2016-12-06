# include <stdio.h>
	
	int main()
	{
		int i, j, k, cnt=0;
		
		printf("Armstrong Number Search\n");
		printf("=======================\n");
		printf("Count  Number\n");
		printf("-----  ------\n");
		
		for(i=1;i<=9;i++)
		{
			for(j=0;j<=9;j++)
			{
				for(k=0;k<=9;k++)
				{
					if(i*100+j*10+k==i*i*i+j*j*j+k*k*k)
						printf("%3d%9d\n", ++cnt, i*100+j*10+k);
				}
			}
		}
		printf("There are %d 3-digit Armstrong Numbers.", cnt);
		
		system("pause");
		return 0;
	}
	/*
		之前就打過了
		其實還有另外一種方式
		但是要算百位、十位還有個位數
		很麻煩
		我比較喜歡這種XD
	*/
