#include <stdio.h>
#include <stdint.h>
#include <glib.h>
#include <gmp.h>

int main(){
    uint64_t i, maybe_prime;
    mpz_t candidate, next, remainder;
    GArray *primes;

    mpz_init(candidate);
    mpz_init(next);
    mpz_init(remainder);

    // create vector with a small initial capacity
    primes = g_array_new(FALSE, TRUE, sizeof(mpz_t));

    // seed primes vector with initial prime 2.
    mpz_set_si(candidate, 2);
    g_array_append_val(primes, candidate);

    // begin the main prime finding loop
    mpz_set_si(candidate, 3); // TODO: create a new one
    while(1){
        maybe_prime = 1;

        // search for a prime factor of candidate
        for(i=0; i<primes->len; i++){
            mpz_mod(remainder, candidate, g_array_index(primes, mpz_t, i));
            // if the remainder is 0 then the candidate number is not prime
            if(mpz_cmp_si(remainder, 0) == 0) maybe_prime = 0;
            //release((obj *)remainder);
            if(!maybe_prime) break;
        }

        // if the number is still maybe prime then it is now definitely prime,
        // add it to the end of the primes vector
        if(maybe_prime){
            g_array_append_val(primes, candidate);
            fputs("Prime found:", stdout);
            mpz_out_str(stdout, 10, candidate);
            fputc('\n', stdout);
        }

        // increment candidate by 2 and release old candidate, it is not needed
        // by main loop
        mpz_add_ui(next, candidate, 2u);
        //release((obj *)candidate);
        mpz_set(candidate, next);
    }
}
