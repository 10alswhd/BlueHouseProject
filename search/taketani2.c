#include <stdio.h>
#include <math.h>

#define MAXN 10

int /* gauss_jordan method */
gauss_jordan(int n, double a[][MAXN+10], double b[]){
	int ipv, i, j;
	double inv_pivot, temp;
	double big;
	int pivot_row, row[MAXN+10];
	for(ipv=0 ; ipv<n ; ipv++){
		/* search max value */
		big=0.0;
		for(i=ipv ; i<n ; i++){
			if(fabs(a[i][ipv]) > big){
				big = fabs(a[i][ipv]);
				pivot_row = i;
			}
		}
		if(big == 0.0) return 1;
		row[ipv] = pivot_row;
		/* pivot row */
		if(ipv != pivot_row){
			for(i=0 ; i<n ; i++){
				temp = a[ipv][i];
				a[ipv][i] = a[pivot_row][i];
				a[pivot_row][i] = temp;
			}
			temp = b[ipv];
			b[ipv] = b[pivot_row];
			b[pivot_row] = temp;
		}
		/* taikakuseibun = 1 */
		inv_pivot = 1.0/a[ipv][ipv];
		a[ipv][ipv]=1.0;
		for(j=0 ; j<n ; j++){
			a[ipv][j] *= inv_pivot;
		}
		b[ipv] *= inv_pivot;
		/* process */
		for(i=0 ; i<n ; i++){
			if(i != ipv){
				temp = a[i][ipv];
				a[i][ipv]=0.0;
				for(j=0 ; j<n ; j++){
					a[i][j] -= temp*a[ipv][j];
				}
				b[i] -= temp*b[ipv];
			}
		}
	}
	for(j=n-1 ; j>=0 ; j--){
		if(j != row[j]){
			for(i=0 ; i<n ; i++){
				temp = a[i][j];
				a[i][j]=a[i][row[j]];
				a[i][row[j]]=temp;
			}
		}
	}
	return 0;
}

void /* for output */
output(const int n, double a[][MAXN+10], const double *b) {
	int i;
	printf("# result #\n");
	for(i=0; i<n; i++) {
		printf("(%6.3lf) + (%6.3lf) y + (%6.3lf) z = %6.3lf\n",
				a[i][0], a[i][1], a[i][2], b[i]);
	}
	for(i=0; i<3; i++) {
		printf("\t>> %c = %6.3lf\n", 117+i+n, b[i]); /* 117 ... x */
	}
}

int main() {
	const int n = 3;
	/*
	 * test case
	 */
	/* keisu gyoretu */
	double a[][MAXN+10] = {
		{3, 2, -1},
		{1, -1, 1},
		{-1, -1, 1}
	};
	/* x, y, z */
	double b[] = {2, -3, 2};
	gauss_jordan(n, a, b);
	output(n, a, b);
	return 0;
}
