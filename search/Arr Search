#include <stdio.h>
#include <stdlib.h>		//system("pause") 뗌에

	int LinearSearch(int *ar, unsigned num, int key)
	{
		unsigned i;

		for (i = 0; i < num; i++)
		{
			if (ar[i] == key)return i;
		}
		return -1;
	}

	void main()
	{
		int arr[] = { 26, 27, 39, 63, 57, 75, 71, 76, 80, 18, 47, 15 };
		unsigned num;
		int key, idx;
		
		printf("찾고 싶은 값을 입력하시오: ");
		num = sizeof(arr) / sizeof(arr[0]);
		scanf("%d", &key);
		idx = LinearSearch(arr, num, key);
		if (idx == -1)
		{
			puts("찾는 값이 없습니다.");
		}
		else
		{
			printf("찾는 값은 %d번째에 있습니다.\n", idx);
		}
		system("pause");

}
