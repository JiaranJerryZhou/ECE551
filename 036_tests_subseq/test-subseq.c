#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, int n, size_t expected_ans) {
  size_t ans = maxSeq(array, n);
  if (ans != expected_ans) {
    printf("fail \n");
    exit(EXIT_FAILURE);
  }
}

int main() {
  int array1[] = {0, 0, 0, 0, 0, 0};
  run_check(array1, 6, 1);
  int array2[] = {6, 5, 4, 3, 2, 1, 0};
  run_check(array2, 7, 1);
  int array3[] = {-3, -1, -2, -4, 1, 2, 3};
  run_check(array3, 7, 4);
  //check for NULL
  run_check(NULL, 0, 0);
  int array4[1] = {0};
  run_check(array4, 1, 1);
  printf("success \n");
  return EXIT_SUCCESS;
}
