#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

/**
 * When it becomes worthwile to do a binary search for the upper bound.
 * 
 * Normally, to check that a number is prime, we simply check that it's not divisible by any previous primes.
 * At first, this is very very fast, but it gets slower as the number of primes grows.
 * However, we don't need to search _all_ previous primes, just all less than the sqrt.
 * This is [all we need to verify it's prime](http://stackoverflow.com/questions/5811151/).
 * 
 * However, we still are only checking primes, so we have to determine the maximum index in the preivous prime array to search up to.
 * Niavely, we could loop over all previous primes until we found the highest number less than the sqrt.
 * However, since the array of previous primes is already sorted, we can just use a binary search!
 * 
 * This makes the primarlity check much faster, as it's O(sqrt(N)) the previous primes, instead of O(N) the previous primes.
 * However, for smaller numbers, it isn't really worth the additional search overhead.
 * 
 * This is the threshold at which it becomes worthwile to do the binary search.
 */
#define BINARY_SEARCH_BOUND_THRESHOLD 128

//
// Utilities
//

#define STATIC_ASSERT(pred) switch(0){case 0:case pred:;}

void fputCommaSeperated(int i, FILE *stream);

/**
 * Return the sqrt of the specified number.
 * 
 * @param num the number to find the square root of
 * @return the square root of the number
 */
double sqrt(double num); // NOTE: <math.h> isn't present

/**
 * Round the specified number up towards positive infinity.
 * 
 * If the argument is NaN, infinity or zero, then the result is the same as the argument.
 * 
 * @param num the number to round up
 * @param the number rounded up to the nearest integer
 */
double ceil(double num);

/**
 * Perform a binary search over the specified array, to find the index of the greatest value
 * less than or equal to the limit.
 * 
 * @param data the sorted array to search through
 * @param size the size of the array
 * @param limit the maximum value to look for
 * @return the index of the highest element less than or equal to the limit, or -1 if not found
 */
int greatestIndexNotExceeding(int const* data, int size, int limit);

int *computePrimes(int amount) {
    int *result=malloc(amount * sizeof(int));
    if (result == NULL) return NULL;
    int lastPrime=1;
    int index;
    for (index = 0; index < amount; index++) {
        inline bool isPrime(int num) {
            int searchBound;
            int previousPrimeIndex;
            if (index > BINARY_SEARCH_BOUND_THRESHOLD) {
                // Break early if it's divisible by the first primes
                // We use the same threshold here, since it's what they determined
                // was the threshold for the binary search
                int i = 0;
                #pragma simd
                for (; i < BINARY_SEARCH_BOUND_THRESHOLD; i++) {
                    if (num % result[i] == 0) return false;
                }
                // Next loop we start out at `BINARY_SEARCH_BOUND_THRESHOLD`
                // Since we already checked up to `BINARY_SEARCH_BOUND_THRESHOLD`,
                // it'd be wasted effort to do it again ;)
                previousPrimeIndex = BINARY_SEARCH_BOUND_THRESHOLD; 
                
                // Try and find the greatest prime number <= its sqrt
                // NOTE: This should never overflow, and must return correct results
                // Since a int can exactly fit in a double, this'll never overflow
                STATIC_ASSERT(sizeof(double) >= sizeof(int));
                int numSqrt = (int) ceil(sqrt((double) num));
                searchBound = greatestIndexNotExceeding(result, index, numSqrt);
                if (searchBound < 0 | searchBound > index | result[searchBound] > numSqrt) {
                    fprintf(
                        stderr,
                        "Invalid search bound for %d with sqrt %d: %d",
                        num,
                        numSqrt,
                        searchBound
                    );
                    if (result[searchBound] > numSqrt) {
                        fprintf(
                            stderr,
                            "result[searchBound] (%d) > numSqrt (%d)",
                            result[searchBound],
                            numSqrt
                        );
                    }
                    abort();
                }
            } else {
                previousPrimeIndex = 0;
                searchBound = index; // Search it all
            }
            #pragma simd
            for (; previousPrimeIndex < searchBound; previousPrimeIndex++) {
               int previousPrime = result[previousPrimeIndex];
               // The number is divisible by a previous prime, so it isn't a prime
               if (num % previousPrime == 0) {
                   return false;
               }
            }
            return true;
        }
        int potentialPrime = lastPrime + 1;
        // Loop until a valid prime is found
        #pragma omp parallel for
        for (; !isPrime(potentialPrime); potentialPrime++) {}
        if ((index + 1) % 100000 == 0) {
            fputs("Found ", stdout);
            fputCommaSeperated(index + 1, stdout);
            fputs("th prime: ", stdout);
            fputCommaSeperated(potentialPrime, stdout);
            fputc('\n', stdout);
            fflush(stdout);
        }
        lastPrime = potentialPrime;
        result[index] = potentialPrime;
    }
    return result;
}

bool isPrime(int num) {
    int i;
    int searchBound = (int) ceil(sqrt((double) num));
    #pragma parallel simd for
    for (i = 3; i <= searchBound; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    int i;
    int amount;
    if (argc > 1) {
        // Retarted C way to safely parse numbers (ignore this)
        errno = 0;
        long full_amount = strtol(argv[1], NULL, 10);
        switch (errno) {
            case 0:
                // Successfully parsed it
                break;
            case ERANGE:
                fprintf(stderr, "Can't handle more than 2^31-1 digits of pi: %s", argv[1]);
                return 1;
            default:
                fprintf(stderr, "Invalid number of digits: %s\n", argv[1]);
                return 1;
        }
        if (full_amount < 0) {
            fprintf(stderr, "Can't handle negative digits of pi: %s\n", argv[1]);
            return 1;
        } else if (((int) full_amount) != full_amount) { // Check our cast
            fprintf(stderr, "Can't handle more than 2^31-1 digits of pi: %s\n", argv[1]);
            return 1;
        } else {
            amount = (int) full_amount;
        }
    } else {
        amount = 10000000; // default to ten million
    }
    fputs("Searching for first ", stdout);
    fputCommaSeperated(amount, stdout);
    fputs(" primes\n", stdout);
    int *result=computePrimes(amount);
    if (result == NULL) {
        fprintf(stderr, "Insufficient memory to calculate %d primes\n", amount);
        return 1;
    }
    int highest = result[amount - 1];
    printf("First 5 primes: %d, %d, %d, %d, %d\n", result[0], result[1], result[2], result[3], result[4]);
    fputs("Highest prime out of ", stdout);
    fputCommaSeperated(amount, stdout);
    fputs(": ", stdout);
    fputCommaSeperated(highest, stdout);
    fputc('\n', stdout);
    fflush(stdout);
    free(result);
    return 0;
}

//
// Utility Implementations 
//

void fputCommaSeperated(const int originalValue, FILE *stream) {
    // NOTE: it's unsigned so we can fit abs(MIN_INT), which can't fit in a signed int
    unsigned int value;
    if (originalValue < 0) {
        /*
         * Casting to 'unsigned int' isn't enough to strip the sign, since it's a no-op.
         * We have to negate the result in order to actually strip the sign.
         */
        value = -((unsigned int) originalValue);
        fputc('-', stream); // Put the minus sign
    } else if (value == 0) {
        // The function can't handle zeros, just hardcode it in :o
        fputc('0', stream);
        return;
    } else {
        value = originalValue;
    }
    /*
     * Split the number into groups of 3 digits.
     * There are at most as many digit groups as there are bytes.
     * Since a byte is at most 256, a byte will always fit into 3 digits.
     * In other words, a number with at most 'x' bytes of information,
     * can never take more than 'x' groups to represent.
     */
    char groups[3][sizeof(unsigned int)];
    int numGroups = 0;
    for (; value > 0; value /= 1000) {
        char* group = groups[numGroups++];
        group[0] = '0' + (value / 100 % 10);
        group[1] = '0' + (value / 10 % 10);
        group[2] = '0' + (value / 1 % 10);
    }
    assert(numGroups > 0);
    // Output the most signifigant group without leading zeros or a comma
    int groupNum = numGroups - 1;
    char* group = groups[groupNum--];
    bool strippedLeading = false;
    int i;
    for (i = 0; i < 3; i++) {
        if (group[i] != '0' || strippedLeading) {
            fputc(group[i], stdout);
            strippedLeading = true;
        }
    }
    while (groupNum >= 0) {
        group = groups[groupNum--];
        fputc(',', stdout);
        fputc(group[0], stdout);
        fputc(group[1], stdout);
        fputc(group[2], stdout);
    }
}


int greatestIndexNotExceeding(int const* data, int size, int limit) {
    if (size < 1) return -1; // We can't find anything in a zero length array......
    int lowerBound = 0;
    int upperBound = size;
    while (true) {
        int midpoint = (((size_t) lowerBound) + ((size_t) upperBound)) >> 1;
        int midpointValue = data[midpoint];
        if (midpointValue <= limit) {
            // The midpoint is to low, try and go higher
            if (midpoint == upperBound || data[midpoint + 1] > limit) {
                // Either we can't go any higher, or the next element > limit
                // Therefore this is the last element <= limit, and we should return it
                return midpoint;
            } else {
                lowerBound = midpoint + 1;
            }
        } else {
            // The midpoint is too high, try and go lower
            if (midpoint == lowerBound) {
                // We can't go lower, so we've failed
                return -1;
            } else {
                upperBound = midpoint;
            }
        }
    }
}

// Math stuff using inline asm

inline double sqrt(double num) {
    double result;
    // Use SIMD sqrt, since it's signifigantly faster and easier
    asm("sqrtsd %[num], %[result];" : [result] "=x"(result) : [num] "xm"(num));
    return result;
}

inline double ceil(double num) {
    int fpuControl, oldFpuControl; // Temporary ASM vars
    /*
     * Seperate output variable, since we have to move from the FPU stack
     * Since we have to move it into a result variable regardless of it's input,
     * we should inform GCC of the potential to put it in a different register.
     */
    double result;
    asm("fldl %[num];\n" // Load `num` onto the FPU's register stack
        /*
         * Load the FPU control flags into memory, then move it into a register (edx).
         * We can't move it directly into a register, because the FPU forbids that.
         * However, we're still must keep the old value, since we need to restore it.
         */
        "fstcw %[oldFpuControl];"
        "movl %[oldFpuControl], %%edx;"
        "andl $0xFFFFFFF3, %%edx;" // Clear rounding mode flags
        "orl $0x0800, %%edx;" // Set rounding flag to round towards positive infinity
        /*
         * Now move the new control mode into memory, and set it in the FPU.
         * The previous value of the fpu's control code is still in `oldControlMode`.
         * We still need the old value, so we need a seperate variable for the new one.
         * Once again, we can't use the existing register, per the FPU's rules.
         */
        "movl %%edx,%[fpuControl];"
        "fldcw %[fpuControl];"
        /*
         * Now that we've set the FPU round towards positive infinity,
         * we simply need to round to an integer to finish it off.
         * We already loaded `num` into the stack above, so we don't need to
         */
        "frndint;"
        "fstpl %[result];" // Pop our result into `result`
        "fldcw %[oldFpuControl];" // Reset the fpu control code to the original value
          /* the vars must be in memory so the FPU can access them (never registers) */
        : [result] "=m"(result), [fpuControl] "=m"(fpuControl), [oldFpuControl] "=m"(oldFpuControl)
        : [num] "m"(num) // Takes 'num' as input, but doesn't consume/clobber it
        : "edx"
    );
    return result;
}
