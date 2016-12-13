#include "brilliant.h"
#define true 1
#define false 0

int gcd(int a, int b) {
  int c;
  while (a!=0) {
    c=a; 
    a=b%a;  
    b=c;
  }
  return b;
}

int gcd3(int a, int b, int c) {
	return gcd(gcd(a,b),c);
}

int reverse(int n) {
        int result = 0;
        while (n > 0) {
            result = result * 10 + n%10;
            n = n/10;
        }
        return result;
}

int isPrime(int n) {
	int i;
	for (i=1; i<n; i++) {
		if (n % i == 0 && i!=1) {
			return false;
		}
	}
	return true;
};

int min(int a, int b) {
	int result = b;
	if (a < b) {
		result = a;
	}
	return result;
}

int max(int a, int b) {
	int result = b;
	if (a > b) {
		result = a;
	}
	return result;
}

int cmpInt(const void *a, const void *b) {
	return ( *(int*) a - *(int*) b);
}
