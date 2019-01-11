#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans != expected_ans) {
    printf("fail \n");
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(3, 4, 81);
  run_check(0, 0, 1);
  //run_check(-2, 0, 1);
  //run_check(-3, 2, 9);
  run_check(1, 2, 1);
  //run_check(1, -2, 1);
  run_check(4, 0, 1);
  run_check(10000, 2, 100000000);
  printf("success \n");
  return EXIT_SUCCESS;
}
