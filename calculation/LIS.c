#include <stdio.h>
#define N 40008
int min(int a[], int n)
{
	int min = a[0];
	int i;
	for (i = 1; i < n; i++)
		if (a[i] < min)
			min = a[i];
	return min;
}

int binarySearch(int a[], int n, int key)
{
	int left = -1;
	int right = n+1;

	while (left+1 != right) {
		int mid = left+(right-left)/2;
		if (a[mid] <= key)
			left = mid;
		else
			right = mid;
	}

	return left;
}

int LIS(int a[], int n)
{
	int maxv[N];//maxv[i]表示长度为i的递增子序列最后一个元素的最小值，比如3， 4和1，2两个子序列，maxv[2] = min(4,2)=2
	maxv[0] = min(a, n)-1;//这样保证二分查找时，每个值都能找到相应的位置
	maxv[1] = a[0];

	int lis[N];
	int i;
	for (i = 0; i < n; i++)
		lis[i] = 1;

	int max = 1;

	for (i = 1; i < n; i++) {
		int j;
		j = binarySearch(maxv, max, a[i]);//返回小于等于a[i]的最大值的下标
		if (a[i] == maxv[j])
			continue;
	    lis[i] = j+1;//不等于一定是大于
		if (lis[i] > max) {//如果比最长距离大
			max = lis[i];
			maxv[lis[i]] = a[i];
		}
		else {
			if (a[i] < maxv[lis[i]])
				maxv[lis[i]] = a[i];
		}
	}

	return max;
}
