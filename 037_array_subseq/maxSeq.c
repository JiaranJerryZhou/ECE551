#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  size_t max = 1;
  size_t count = 1;
  int current = array[0];
  for (size_t i = 1; i < n; i++) {
    if (array[i] > current) {
      count = count + 1;
      if (count > max) {
        max = count;
      }
    }
    else {
      count = 1;
    }
    current = array[i];
  }
  return max;
}
