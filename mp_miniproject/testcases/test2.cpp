#include <stdio.h>
#include <stdlib.h>

#include <iostream>

int main() {
  int bug[1] = {0};
  bug[1] = bug[1] + 100;
  return EXIT_SUCCESS;
}
