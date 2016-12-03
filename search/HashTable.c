#include<stdio.h>
#include<stdlib.h>

typedef int KeyType;
typedef struct LNODE
{
   KeyType data;
   struct LNODE * next;    
}NODE;

typedef struct Hash
{
	NODE * next;
	NODE * pCurtail;
	int count;
}HashTable;

HashTable* CreatHashTable(KeyType keyset[], int size, int htsize, int p);
int SearchHT(HashTable* phashtable, KeyType k, int p);

int  main()
{
	int i = 0;
	int size = 11;     //size of array 
	int htsize = 13;   //size of hashtable
	int p = 13;
	int count = 0;
	int index = 0;
	int ret = 0;
	KeyType keyset[]={16,74,60,43,54,90,46,31,29,88,77};
	HashTable * pht = NULL;
	HashTable * phttemp = NULL;
	NODE * pNode = NULL;
	pht = CreatHashTable(keyset, size, htsize ,p);
	
	/************search data**************/
	ret = SearchHT(pht, 1000, p);
	if (ret)
		printf("it can't find 1000\n");
	else
		printf("it can find 1000\n");
	
	for (i = 0; i < size; i++)
	{
		ret = SearchHT(pht, keyset[i], p);
		if (ret)
			printf("it can't find %d\n", keyset[i]);
		else
			printf("it can find %d\n", keyset[i]);
	
	}
	
	/*******************free memory********************/
	for (index = 0; index < htsize; index++)
	{
		phttemp = pht + index;
		pNode = phttemp -> next;
		while(pNode != NULL)
		{
			free(pNode);
			pNode = pNode -> next;
		}
	}
	free(pht);   //注意free(pht)和free(pNode)的先后
	return 0;
}


/******************************creat hashtable*************************
输入：（1）keyset[]，关键字数组（2）size，数组大小（3）htsize,哈希表大小（4）p,哈希函数参数（除留余数法）
返回值：哈希表指针*/

HashTable* CreatHashTable(KeyType keyset[], int size, int htsize, int p)
{
     int index = 0;
     int i = 0;
     HashTable * pHashtable = NULL;
     HashTable * pHttemp = NULL;
     NODE * pNodetemp = NULL;
     pHashtable = (HashTable *)malloc(htsize * sizeof(HashTable));
     if (NULL == pHashtable)
     {
	 printf("malloc fails\n");
	 exit(0);
     }
     memset(pHashtable, 0, htsize * sizeof(HashTable));

     for (i = 0; i < size; i++)
     {
		pNodetemp = NULL;
		pHttemp = NULL;
		index = keyset[i] % p;
	
		pHttemp = pHashtable + index; 
		pNodetemp = (NODE *)malloc(sizeof(NODE));
		if (NULL == pNodetemp)
		{
			printf("malloc fails\n");
			exit(0);
		}
		pNodetemp -> data = keyset[i];
		pNodetemp -> next = NULL;
                /***********对应的索引已有数据*************/
		if (pHttemp -> next != NULL)
		{
			pHttemp -> pCurtail -> next = pNodetemp;

		}
		else
			pHttemp -> next = pNodetemp;
		pHttemp -> pCurtail = pNodetemp;
		pHttemp -> count++;
	}
	return pHashtable;
}

/*****************************search key in hashtable***********************
输入：（1）phashtable,哈希表指针（2）k,要查询的数据（3）p,哈希函数参数
返回值：（1）返回值=1，查询失败（2）返回值=0，查询成功*/

int SearchHT(HashTable * phashtable, KeyType k, int p)
{
	int index;
	KeyType curdata;
	NODE * pNodetemp;

	index = k % p;
	pNodetemp = (phashtable + index) -> next;
	if(NULL == pNodetemp)
		return 1;
	else
	{
		while(pNodetemp != NULL)
		{
			curdata = pNodetemp -> data ;
			if (k == curdata)
				return 0;
			pNodetemp = pNodetemp -> next;
		}
		return 1;
	}
}
















