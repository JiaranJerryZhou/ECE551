#include <cmath>
#include <cstdio>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int mid = low + (high - low) / 2;
  if (f->invoke(mid) == 0) {
    return mid;
  }
  else if (f->invoke(mid) < 0) {
    return binarySearchForZero(f, mid, high);
  }
  else {
    return binarySearchForZero(f, low, mid - 1);
  }
}
