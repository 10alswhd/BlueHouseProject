#include <sys/time.h>	// timer
#include <stdio.h>		// printf
#include <stdlib.h>		// malloc, free
#include <stdbool.h>	// bool

const int N = 1000000;	// Range of Prime
const int nTest = 2;	// Two test

struct Measurement {
	int nPrime;			// number of Primes
	double time_use;	// Duration
};

int Prime_Sequential_Search(bool *isPrime, int *PrimeNumber);	// Return the number of Primes
int Prime_Sieve_Eratosthenes(bool *isPrime, int *PrimeNumber);	// Return the number of Primes
struct Measurement Time_Measure(bool *isPrime, int *PrimeNumber, struct timeval *start_time, struct timeval *end_time, int (*prime)(bool*, int*));
void reset(bool *isPrime, int *PrimeNumber);

int main(){
	
	struct timeval start_time, end_time;
	bool *isPrime = malloc(N * sizeof(bool));
	int *PrimeNumber = calloc(N/2, sizeof(int));
	struct Measurement *measure = malloc(nTest * sizeof(struct Measurement));
	
	printf("1. Sequential Search : \n");
	measure[0] = Time_Measure(isPrime, PrimeNumber, &start_time, &end_time, Prime_Sequential_Search);

	printf("2. Sieve of Eratosthenes : \n");
	measure[1] = Time_Measure(isPrime, PrimeNumber, &start_time, &end_time, Prime_Sieve_Eratosthenes);
	
	free(isPrime) ;
	free(PrimeNumber) ;
	free(measure);
	return 0;
}

int Prime_Sequential_Search(bool *isPrime, int *PrimeNumber) {
	int i, j, ans=0;
	for (i=2; i<N; ++i) {
		if (ans == 0) {
			PrimeNumber[ans++] = i;
		} else {
			for (j=0; j<ans; ++j) {
				if (i%PrimeNumber[j] == 0) {
					isPrime[i] = false;
					break;
				}
			}
			if (isPrime[i]) {
				PrimeNumber[ans++] = i;
			}
		}
	}
	
	return ans;
}

int Prime_Sieve_Eratosthenes(bool *isPrime, int *PrimeNumber) {
	long i, j, ans=0;
	for (i=2; i<=N; ++i){
		if (isPrime[i]) {
			PrimeNumber[ans++] = i;
			for (j=i*i; j<=N; j+=i){
				isPrime[j] = false;
			}
		}
	}
	return ans;
}

struct Measurement Time_Measure(bool *isPrime, int *PrimeNumber, struct timeval *start_time, struct timeval *end_time, int (*prime)(bool*, int*)) {
	reset(isPrime, PrimeNumber);
	struct Measurement ans;
	gettimeofday(start_time,0);
	ans.nPrime = prime(isPrime, PrimeNumber);
	gettimeofday(end_time,0);
	ans.time_use = 1000*(end_time->tv_sec - start_time->tv_sec) + (end_time->tv_usec - start_time->tv_usec)/1000;
	printf("Number of Primes : %d\n", ans.nPrime);
	printf("Total time : %f ms\n\n", ans.time_use);
	return ans;
}

void reset(bool *isPrime, int *PrimeNumber) {
	for (int i=0; i<N; ++i){
		if (i<N/2) PrimeNumber[i] = 0;
		isPrime[i] = true;
	}
	isPrime[0] = false;
	isPrime[1] = false;
}
