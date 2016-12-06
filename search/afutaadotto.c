#include <stdio.h>

int memo[100000];

int search(int warareru, int waru) {
	int ret, next;
	if (memo[warareru]) return 0;
	memo[warareru] = 1;
	next = (warareru * 10) % waru;
	ret = search(next, waru);
	if (ret > 0) {
		memo[warareru] = 2;
		ret++;
	} else if (memo[next] == 2) {
		memo[warareru] = 2;
		ret = 1;
	}
	return ret;
}

int main(void) {
	int n;
	int ans = 0, cur, i, j;
	memo[0] = 2;
	if (scanf("%d", &n) != 1) return 1;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) memo[j] = 0;
		cur = 0;
		for (j = 1; j <= i; j++) cur += search(j, i);
		cur *= n / i;
		for (j = n - n % i + 1; j <= n; j++) cur += search(j, i);
		ans += cur;
	}
	printf("%d\n", ans);
	return 0;
}
