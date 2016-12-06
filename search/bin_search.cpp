#include "stdint.h"
#include "bin_search.h"

int32_t bin_search(const int32_t* data, const int32_t size, const int32_t k) {
  int32_t lo = 0, hi = size - 1 ;
  while (lo <= hi) {
    int32_t mid = (lo + hi) / 2;
    if (data[mid] == k) return mid;
    else if (data[mid] > k)
      hi = mid - 1;
    else 
      lo = mid + 1;
  }
  return -1;
}
