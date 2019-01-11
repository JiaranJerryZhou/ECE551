#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"
/*
void stripNewline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}
*/

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  char ** lines = NULL;
  size_t sz;
  char * curr = NULL;
  size_t j = 0;
  int found = 0;
  counts_t * counts = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    printf("cannot open file\n");
    exit(EXIT_FAILURE);
  }
  while (getline(&curr, &sz, f) >= 0) {
    lines = realloc(lines, (j + 1) * sizeof(*lines));
    lines[j] = curr;
    curr = NULL;
    stripNewline(lines[j]);
    j++;
  }
  free(curr);
  for (size_t k = 0; k < j; k++) {
    for (int i = 0; i < kvPairs->numPairs; i++) {
      if (strcmp(lines[k], kvPairs->pairs[i]->key) == 0) {
        addCount(counts, kvPairs->pairs[i]->value);
        found = 1;
      }
    }
    if (found == 0) {
      addCount(counts, NULL);
    }
    found = 0;
  }
  for (size_t k = 0; k < j; k++) {
    free(lines[k]);
  }
  free(lines);
  if (fclose(f) != 0) {
    printf("cannot close file\n");
    exit(EXIT_FAILURE);
  }
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    perror("not enough command lines\n");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      printf("cannot open file\n");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      printf("cannot close file\n");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
