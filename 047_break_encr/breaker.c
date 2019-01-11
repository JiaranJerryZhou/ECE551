#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findkey(int * p, int n) {
  int max = 0;
  int key = 4;
  for (int i = 0; i < n; i++) {
    if (p[i] > max) {
      max = p[i];
      key = i;
    }
  }
  return key;
}

int frequency(FILE * f) {
  int c;
  int count[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      int n = c - 'a';
      count[n]++;
    }
  }
  int key = findkey(count, 26);
  int offset = (key + 26 + 'a' - 'e') % 26;
  return offset;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int key = frequency(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  printf("%d\n", key);
  return EXIT_SUCCESS;
}
