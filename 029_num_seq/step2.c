// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  if (x == 0) {
    return 1;
  }
  else if (x > 0) {
    return (seq2(x - 1) + 2 * x + 2);
  }
  //x < 0
  else {
    return (seq2(x + 1) - 2 * x - 4);
  }
}

int sumSeq2(int low, int high) {
  int sum = 0;
  for (int i = low; i < high; i++) {
    sum = sum + seq2(i);
  }
  return sum;
}

int main() {
  int ans;
  int x;
  //x = 0
  x = 0;
  ans = seq2(x);
  printf("seq2(%d) = %d\n", x, ans);
  //x = 5
  x = 5;
  ans = seq2(x);
  printf("seq2(%d) = %d\n", x, ans);
  //x = -5
  x = -5;
  ans = seq2(x);
  printf("seq2(%d) = %d\n", x, ans);
  //x = 100
  x = 100;
  ans = seq2(x);
  printf("seq2(%d) = %d\n", x, ans);
  //sum(0, 2)
  printf("sumSeq2(%d, %d) = %d\n", 0, 2, sumSeq2(0, 2));
  //sum(-2, 0)
  printf("sumSeq2(%d, %d) = %d\n", -2, 0, sumSeq2(-2, 0));
  //sum(-4, 5)
  printf("sumSeq2(%d, %d) = %d\n", -4, 5, sumSeq2(-4, 5));
  //sum(100, 105)
  printf("sumSeq2(%d, %d) = %d\n", 100, 105, sumSeq2(100, 105));
  //sum(5, -4)
  printf("sumSeq2(%d, %d) = %d\n", 5, -4, sumSeq2(5, -4));
  return EXIT_SUCCESS;
}
