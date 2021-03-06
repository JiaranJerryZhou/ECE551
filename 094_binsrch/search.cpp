#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int mid = low + (high - low) / 2;
  if (low >= high - 1) {
    return low;
  }
  int key = f->invoke(mid);
  /*
  if (f->invoke(low) > 0) {
    return low;
  }
  else if (f->invoke(high - 1) < 0) {
    return high - 1;
  }
  */
  if (key == 0) {
    return mid;
  }
  else if (key < 0) {
    return binarySearchForZero(f, mid, high);
  }
  else {
    return binarySearchForZero(f, low, mid);
  }
}

class SinFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class LinearFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 10 * (arg - 0.5); }
};

class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  unsigned n = 1;
  if (high > low) {
    n = log2(high - low) + 1;
  }
  Function<int, int> * count = new CountedIntFn(n, f, mesg);
  int ans = binarySearchForZero(count, low, high);
  std::cout << ans << std::endl;
  assert(ans == expected_ans);
  std::cout << "test passed\n";
  delete count;
}

int main() {
  //check for an ordinary case in 094
  SinFunction * f1 = new SinFunction;
  check(f1, 0, 150000, 52359, "SinFunction");
  //check for all positive f(x)
  check(f1, 52359, 150000, 52359, "Sinfunction with all positive f(x)");
  //check for all negative f(x)
  check(f1, 0, 52359, 52358, "Sinfunction with all negative f(x)");
  //check for low = high - 1
  check(f1, 0, 1, 0, "low = high - 1");
  //check for low = high
  check(f1, 0, 0, 0, "low = high");
  //check for off-by-one error
  LinearFunction * f2 = new LinearFunction;
  check(f2, -2, 4, 0, "off-by-one");
  delete f1;
  delete f2;
  return EXIT_SUCCESS;
}
