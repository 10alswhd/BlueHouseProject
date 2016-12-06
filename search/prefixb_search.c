#include <assert.h>

static inline int prefix_cmp(char *prefix, char *str)
{
	unsigned char *p = (unsigned char *)prefix;
	unsigned char *s = (unsigned char *)str;
	while (*p && *s && *p == *s)
		p++, s++;

	return (*p == 0) ? 0 : *p - *s;
}

/* 查找一个一排序数组的以@prefix为前缀的所有项
 * 返回以@prefix为前缀的数组元素的个数,
 * @pos返回大于或等于@prefix的第一项的位置 */
size_t prefix_search(char **strs, size_t n, char *prefix, size_t *pos)
{
	size_t min = 0, max = n;
	while (min < max) { /* 找到包含prefix最小的一项, 循环结束后min指向这一项 */
		size_t m = (min + max) / 2;
		int cmp = prefix_cmp(prefix, strs[m]);
		if (cmp <= 0) {
			if (cmp < 0) /* 缩小第二次查找的范围 */
				n = m;
			max = m;
		} else
			min = m + 1;
	}
	/* 找到不包含prefix,大于prefix最小的一项, 循环结束后max指向这一项 */
	while (max < n) {
		size_t m = (max + n) / 2;
		if (prefix_cmp(prefix, strs[m]) < 0)
			n = m;
		else
			max = m + 1;
	}
	assert((max == min && max == n) ||
	       (!prefix_cmp(prefix, strs[min]) && !prefix_cmp(prefix, strs[max-1])));
	*pos = min;
	return max - min;
}

size_t prefix_search2(char **strs, size_t n, char *prefix, size_t *pos)
{
	size_t min = 0, max = n;
	/* 找到包含prefix最小的一项, 循环结束后min指向这一项 */
	while (min < max) {
		size_t m = (min + max) / 2;
		if (prefix_cmp(prefix, strs[m]) <= 0)
			max = m;
		else
			min = m + 1;
	}
	/* 当prefix_cmp(prefix, strs[min] != 0时max不会增加 */
	for (; max < n && !prefix_cmp(prefix, strs[max]); max++) {
	}

	*pos = min;
	return max - min;
}

#if 0
size_t prefix_search(char **strs, size_t n, char *prefix, size_t *pos)
{
	size_t min = 0, max = n, mid = 0, tmp;
	int cmp = 0;
	/* 二分法找到strs数组中的一个前缀为prefix的一项 */
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
		if (prefix_cmp(prefix, strs[m]) == 0)
			mid = m;
		else
			min = m + 1;
	}
	assert(mid == min && (min == 0 || prefix_cmp(prefix, strs[min - 1]) > 0));
	mid = tmp;
	while (max > mid) { /* 找到strs数组中比prefix大的最小的一项 */
		size_t m = (max + mid) / 2;
		if (prefix_cmp(prefix, strs[m]) == 0)
			mid = m + 1;
		else
			max = m;
	}
	assert(mid == max && prefix_cmp(prefix, strs[mid - 1]) == 0);
	*pos = min;
	return max - min;
}
size_t prefix_search4(char **strs, size_t n, char *prefix, size_t *pos)
{
	ssize_t min = 0, max = n, mid = 0;
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
	for (min = mid - 1; min >= 0; min--) {
		if (prefix_cmp(prefix, strs[min]) != 0)
			break;
	}
	for (max = mid + 1; max < n; max++) {
		if (prefix_cmp(prefix, strs[min]) != 0)
			break;
	}
	*pos = min + 1;
	return max - min - 1;
}
size_t prefix_search2(char **strs, size_t n, char *prefix, size_t *pos)
{
	size_t min = 0, max = n - 1;
	if (n == 0 || strs == NULL)
		return 0;
	/* 找到包含prefix最小的一项, 循环结束后min指向这一项 */
	while (min < max) {
		size_t m = (min + max) / 2;
		if (prefix_cmp(prefix, strs[m]) <= 0)
			max = m;
		else
			min = m + 1;
	}
	assert(max == min);
	if (prefix_cmp(prefix, strs[min]) != 0)
		return 0;
	*pos = min, max = n;
	/* 找到包含prefix最大的一项, 循环结束后min的前一项是数组中最大的一项 */
	while (min < max) {
		size_t m = (max + min) / 2;
		if (prefix_cmp(prefix, strs[m]) < 0)
			max = m;
		else
			min = m + 1;
	}
	assert(min == max && prefix_cmp(prefix, strs[min - 1]) == 0);
	return min - *pos;
}
#endif
