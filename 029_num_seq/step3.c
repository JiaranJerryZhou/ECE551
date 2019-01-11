// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  int ans = x * y - 3 * x + 2 * y;
  return ans;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  if (yHi <= yLow) {
    return 0;
  }
  int count = 0;
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      if (seq3(i, j) % 2 == 0) {
        count = count + 1;
      }
    }
  }
  return count;
}

int main() {
  //(0, 0)
  printf("seq3(%d, %d) = %d\n", 0, 0, seq3(0, 0));
  //(0, 3)
  printf("seq3(%d, %d) = %d\n", 0, 3, seq3(0, 3));
  //(-2, 0)
  printf("seq3(%d, %d) = %d\n", -2, 0, seq3(-2, 0));
  //(-4, -5)
  printf("seq3(%d, %d) = %d\n", -4, -5, seq3(-4, -5));
  //(-3, 2)
  printf("seq3(%d, %d) = %d\n", -3, 2, seq3(-3, 2));
  //(5, 4)
  printf("seq3(%d, %d) = %d\n", 5, 4, seq3(5, 4));
  //(2, -3)
  printf("seq3(%d, %d) = %d\n", 2, -3, seq3(2, -3));
  //0, 0, 0, 0
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 0, 0, 0, countEvenInSeq3Range(0, 0, 0, 0));
  //-3, 3, 4, 0
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -3,
         3,
         4,
         0,
         countEvenInSeq3Range(-3, 3, 4, 0));
  //3, -3, 0, 4
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         3,
         -3,
         0,
         4,
         countEvenInSeq3Range(3, -3, 0, 4));
  //-3, 4, -5, 2
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -3,
         4,
         -5,
         2,
         countEvenInSeq3Range(-3, 4, -5, 2));
  //-2, 2, -2, 2
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -2,
         2,
         -2,
         2,
         countEvenInSeq3Range(-2, 2, -2, 2));
  return EXIT_SUCCESS;
}
