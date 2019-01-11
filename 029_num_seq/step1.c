// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  int y;
  y = 4 * x - 3;
  return y;
}

void printSeq1Range(int low, int high) {
  for (int i = low; i < high; i++) {
    printf("%d", seq1(i));
    if (i != (high - 1)) {
      printf(", ");
    }
  }
  printf("\n");
}

int main() {
  int ans;
  int x;
  //x = 0
  x = 0;
  ans = seq1(x);
  printf("seq1(%d) = %d\n", x, ans);
  //x = 1
  x = 1;
  ans = seq1(x);
  printf("seq1(%d) = %d\n", x, ans);
  //x = -5
  x = -5;
  ans = seq1(x);
  printf("seq1(%d) = %d\n", x, ans);
  //x = 100
  x = 100;
  ans = seq1(x);
  printf("seq1(%d) = %d\n", x, ans);
  //range(-5, 5)
  printf("printSeq1Range(%d, %d)\n", -5, 5);
  printSeq1Range(-5, 5);
  //range(10, 9)
  printf("printSeq1Range(%d, %d)\n", 10, 9);
  printSeq1Range(10, 9);
  //range(0, 0)
  printf("printSeq1Range(%d, %d)\n", 0, 0);
  printSeq1Range(0, 0);
  //range(100, 105)
  printf("printSeq1Range(%d, %d)\n", 100, 105);
  printSeq1Range(100, 105);
  //range(-10, -4)
  printf("printSeq1Range(%d, %d)\n", -10, -4);
  printSeq1Range(-10, -4);
  return EXIT_SUCCESS;
}
