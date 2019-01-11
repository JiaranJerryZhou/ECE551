#include <stdio.h>
#include <stdlib.h>

#include <iostream>
int main(int argc, char ** argv) {
  int count = 0;
  while (*argv != NULL) {
    std::cout << *argv << std::endl;
    count++;
    argv++;
  }

  std::cout << "There are total " << count << " arguments" << std::endl;
  return EXIT_SUCCESS;
}
