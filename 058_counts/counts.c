#include "counts.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->numCounts = 0;
  //counts->names = malloc(sizeof(*counts->names));
  counts->names = NULL;
  return counts;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int found = 0;
  if (name == NULL) {
    name = "<unknown>";
  }
  for (int i = 0; i < c->numCounts; i++) {
    if (strcmp(name, c->names[i]->value) == 0) {
      c->names[i]->count++;
      found = 1;
    }
  }
  if (found == 0) {
    c->numCounts++;
    c->names = realloc(c->names, c->numCounts * sizeof(*c->names));
    c->names[c->numCounts - 1] = malloc(sizeof(*c->names[c->numCounts - 1]));
    c->names[c->numCounts - 1]->value = malloc(sizeof(*name) * (strlen(name) + 1));
    c->names[c->numCounts - 1]->value = strcpy(c->names[c->numCounts - 1]->value, name);
    c->names[c->numCounts - 1]->count = 1;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  int numUnknown = 0;
  for (int i = 0; i < c->numCounts; i++) {
    if (strcmp("<unknown>", c->names[i]->value) == 0) {
      numUnknown = c->names[i]->count;
    }
    else {
      fprintf(outFile, "%s: %d\n", c->names[i]->value, c->names[i]->count);
    }
  }
  if (numUnknown != 0) {
    fprintf(outFile, "%s: %d\n", "<unknown>", numUnknown);
  }
  //int close = fclose(outFile);
  //assert(close == 0);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->numCounts; i++) {
    free(c->names[i]->value);
    free(c->names[i]);
  }
  free(c->names);
  free(c);
}
