#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read(char (*matrix)[10], FILE * f) {
  int c;
  int i = 0;
  int j = 0;
  while ((c = fgetc(f)) != EOF) {
    if ((c - '\n') != 0) {
      matrix[i][j] = c;
      j++;
    }
    else if (j != 10) {
      fprintf(stderr, "column is not equal to 10");
      exit(EXIT_FAILURE);
    }
    else {
      j = 0;
      i++;
    }
  }
  if (i != 10) {
    fprintf(stderr, "row is not equal to 10");
    exit(EXIT_FAILURE);
  }
}

void rotate(char (*input)[10], char (*output)[10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      output[j][9 - i] = input[i][j];
    }
  }
}

void print(char (*matrix)[10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
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
  char matrix[10][10];
  read(matrix, f);
  char output[10][10];
  rotate(matrix, output);
  print(output);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
