#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long * get_primes(long num_primes);

int main(int argc, char * argv[]){
        if (argc != 3) {
                fprintf(stderr, "Syntax: ./primes max_number_to_test out_file\n");
                exit(-1);
        }
        if (atoi(argv[1]) < 0){
                fprintf(stderr, "I don't test negative numbers.\n");
                exit(-1);
        }
        FILE * f = fopen(argv[2], "w");
        long * primes = get_primes(atoi(argv[1]));

        while(*primes != 0){
                fprintf(f, "%d\n", *primes);
                primes++;
        }
        fclose(f);
        return 0;
};


long * get_primes(long max_search){
        long alloc_size = 32;
        long * primes = malloc(sizeof(long)*alloc_size); //might want to make this a dynamically growing list if I want to do arbitrary size and not allocate more memory than I need....
        if (primes == NULL){
                fprintf(stderr, "Couldn't alloc space\n");
                exit(-1);
        }
        if (max_search < 2) {
                primes [0] = 0;
                return primes;
        }
        primes[0] = 2;
        long primes_len = 1;

        for (long test_num = 3; test_num < max_search; test_num+=2){
                long sqrt_of_test = (long)sqrtl((long double)test_num);

                int pass = 1;
                for (long prime_num = 1; prime_num < primes_len; prime_num += 1){
                        if (!(test_num % primes[prime_num])){
                                pass = 0;
                                break;
                        }
                        else if (primes[prime_num] > sqrt_of_test){
                                break;
                        }
                }
                if (pass){
                        if (primes_len == alloc_size){
                                primes = realloc(primes, sizeof(long)*alloc_size * 2);
                                if (primes == NULL){
                                        fprintf(stderr, "Couldn't realloc space\n");
                                        exit(-1);
                                } else{
                                        fprintf(stderr, "Successfully grew alloc'd memory to %d\n", alloc_size);
                                }
                                alloc_size = alloc_size * 2;
                        }
                        primes[primes_len] = test_num;
                        primes_len ++;
                }
        }
        primes[primes_len] = 0;
        return primes;
}
