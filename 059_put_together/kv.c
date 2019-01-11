#include "kv.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//remove '\n' in value
void stripNewline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}
/*
void printKV(kvpair_t * pair) {
  printf("key = '%s' value = '%s'\n", pair->key, pair->value);
}
*/
kvpair_t * readKV(FILE * f) {
  kvpair_t * pair = malloc(sizeof(*pair));
  size_t sz = 0;
  char * line = NULL;
  if (getline(&line, &sz, f) < 0) {
    free(line);
    free(pair);
    return NULL;
  }
  else {
    char * p = strchr(line, '=');
    //divide line into 2 parts
    if (p != NULL) {
      *p = '\0';
      p++;
    }
    else {
      free(line);
      free(pair);
      printf("invalid input\n");
      return NULL;
    }
    stripNewline(p);
    pair->key = malloc((strlen(line) + 1) * sizeof(*pair->key));  //we need an extra space for '\0'
    pair->value = malloc((strlen(p) + 1) * sizeof(*pair->value));
    pair->key = strcpy(pair->key, line);
    pair->value = strcpy(pair->value, p);
    pair->key[strlen(line)] = '\0';
    pair->value[strlen(p)] = '\0';
  }
  free(line);
  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  //cannot open file
  if (f == NULL) {
    return NULL;
  }
  kvarray_t * answer = malloc(sizeof(*answer));
  answer->numPairs = 0;
  answer->pairs = NULL;
  kvpair_t * ptr = NULL;
  while ((ptr = readKV(f)) != NULL) {
    answer->numPairs++;
    answer->pairs = realloc(answer->pairs, answer->numPairs * sizeof(*answer->pairs));
    answer->pairs[answer->numPairs - 1] = ptr;
  }
  //nothing in file
  /*
  if (answer->pairs == NULL) {
    free(answer);
  }
  */
  int result = fclose(f);
  assert(result == 0);
  return answer;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  kvpair_t * ptr = NULL;
  for (int i = 0; i < pairs->numPairs; i++) {
    //go to each pair, free value and key, then free kvpair_t
    ptr = pairs->pairs[i];
    free(ptr->key);
    free(ptr->value);
    free(ptr);
  }
  //free the array of pointer to pairs, then free kvarray_t itself
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->numPairs; i++) {
    // printKV(pairs->pairs[i]);
    printf("key = '%s' value = '%s'\n", pairs->pairs[i]->key, pairs->pairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->numPairs; i++) {
    if (strcmp(key, pairs->pairs[i]->key) == 0) {
      return pairs->pairs[i]->value;
    }
  }
  return NULL;
}
