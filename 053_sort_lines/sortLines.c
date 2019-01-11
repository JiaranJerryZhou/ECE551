#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

size_t readData(char ** lines, FILE * f, size_t count) {
  char * current = NULL;
  size_t sz = 0;
  size_t i = 0;
  while (getline(&current, &sz, f) >= 0) {
    lines = realloc(lines, (i + count + 1) * sizeof(*lines));
    lines[i] = current;
    current = NULL;
    i++;
  }
  free(current);
  return i;
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  char ** lines = NULL;
  size_t count = 0;
  if (argc == 1) {
    //count = readData(lines, stdin, count);
    char * current = NULL;
    size_t sz = 0;
    while (getline(&current, &sz, stdin) >= 0) {
      lines = realloc(lines, (count + 1) * sizeof(*lines));
      lines[count] = current;
      current = NULL;
      count++;
    }
    free(current);
    sortData(lines, count);
    for (size_t j = 0; j < count; j++) {
      printf("%s", lines[j]);
      free(lines[j]);
    }
    free(lines);
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }
      lines = NULL;
      count = 0;
      size_t sz = 0;
      char * current = NULL;
      while (getline(&current, &sz, f) >= 0) {
        lines = realloc(lines, (count + 1) * sizeof(*lines));
        lines[count] = current;
        current = NULL;
        count++;
      }
      free(current);
      sortData(lines, count);
      for (size_t j = 0; j < count; j++) {
        printf("%s", lines[j]);
        free(lines[j]);
      }
      free(lines);
      if (fclose(f) != 0) {
        perror("failed to close the input file");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
