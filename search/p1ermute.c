include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool print_permutation(unsigned int n,
                       unsigned int permutation[n],
                       unsigned int count[n]) {
  printf("Permutation: [");
  for (unsigned int i = 0; i < n; i++) {
    printf(" %u", permutation[i]);
  }
  printf(" ]; Factoradic index: (");
  for (unsigned int i = 0; i < n; i++) {
    printf(" %u", count[i]);
  }
  printf(" )\n");
  return false; // hit all the permutations
}

void search_permutations (unsigned int n,
                          bool (*test)(unsigned int,
                                       unsigned int[],
                                       unsigned int[])) {
  // The current permutation, as a list of numbers from 0 to n-1, of
  // length n, where permutation[i] == j indicates that i is sent to j
  // by the permutation.
  unsigned int permutation[n]; // the current permutation
  for (unsigned int i = 0; i < n; i++) {
    permutation[i] = i;
  }

  // The factoradic index of the current permutation (this mimics the
  // list of loop counters in the frames on the stack that you would
  // have in the recursive version of this)
  unsigned int count[n];
  memset(count, 0, sizeof(unsigned int) * n);

  // start at the beginning of the deepest nested loop in the
  // recursion
  for (unsigned int right = 1;;) {

    // loop body (done once per permutation)
    if (test(n, permutation, count)) {
      // do whatever needs to be done when you find what you're
      // looking for
      return;
    }

    // find the next permutation, if any

    // back out however many levels of recursion necessary to find the
    // next loop iteration, if any
    while (count[right] == right) {
      count[right] = 0;
      right++;
    }
    if (right >= n) break;

    // perform the swap that generates the next permutation
    unsigned int left = (right % 2) * count[right];
    unsigned int tmp = permutation[left];
    permutation[left] = permutation[right];
    permutation[right] = tmp;

    // increment the factoradic index
    count[right]++;
    right = 1;
  }
}

int main (int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: permute <n>\n");
    return 1;
  }
  unsigned int n = atoi(argv[1]);

  search_permutations(n, print_permutation);

  return 0;
}
