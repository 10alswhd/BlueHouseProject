#include <assert.h>

static inline int prefix_cmp(char *prefix, char *str)
{
	unsigned char *p = (unsigned char *)prefix;
	unsigned char *s = (unsigned char *)str;
	while (*p && *s && *p == *s)
		p++, s++;

	return (*p == 0) ? 0 : *p - *s;
}

size_t prefix_search(char **strs, size_t n, char *prefix, size_t *pos)
{
	size_t min = 0, max = n, mid = 0, tmp;
	int cmp = 0;

	/* 二分法茶找到strs数组中的一个前缀为prefix的一项 */
	while (min < max) {
		mid = (min + max) / 2;
		cmp = prefix_cmp(prefix, strs[mid]);
		if (cmp > 0)
			min = mid + 1;
		else if (cmp < 0)
			max = mid;
		else
			break;
	}
	if (min >= max) // 没有找到
		return 0;

	tmp = mid;
	while (min < mid) {
		/* 找到strs数组中比prefix小的最大的一项 */
		size_t m = (min + mid) / 2;
		if ((cmp = prefix_cmp(prefix, strs[m])) == 0)
			mid = m;
		else
			min = m + 1;
	}
	assert(mid == min && (min == 0 || prefix_cmp(prefix, strs[min - 1]) > 0));

	mid = tmp;
	while (max > mid) { /* 找到strs数组中比prefix大的最小的一项 */
		size_t m = (max + mid) / 2;
		if ((cmp = prefix_cmp(prefix, strs[m])) == 0)
			mid = m + 1;
		else
			max = m;
	}
	assert(mid == max && prefix_cmp(prefix, strs[mid - 1]) == 0);

	*pos = min;
	return max - min;
}
