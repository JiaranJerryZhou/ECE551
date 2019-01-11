#include "election.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include any other headers you need here...

/* 
I am sorry! This Function is too long. I haven't read Ch13 before this assignment, so I didn't break down this function into smaller ones. I will do better next time!
*/
state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t state;
  //count the number of':'
  int count = 0;
  const char * ptr = line;
  char population[10];
  char vote[3];
  int i = 0;
  //corner case no input
  if (*ptr == '\0') {
    printf("no input\n");
    exit(EXIT_FAILURE);
  }
  //read line before first ':' into state.name
  while ((*ptr != ':') && (*ptr != '\0')) {
    state.name[i] = *ptr;
    i++;
    ptr++;
  }
  if (i > 63) {
    printf("state name too long!\n");
    exit(EXIT_FAILURE);
  }
  state.name[i] = '\0';
  if (*ptr == ':') {
    count++;
    ptr++;
  }
  i = 0;
  //corner case Alabama::123
  if (*ptr == ':') {
    printf("invalid input\n");
    exit(EXIT_FAILURE);
  }
  while ((*ptr != ':') && (*ptr != '\0')) {
    //population must be number
    if (((*ptr - '0') < 0) || ((*ptr - '0')) > 9) {
      printf("invalid input\n");
      exit(EXIT_FAILURE);
    }
    population[i] = *ptr;
    i++;
    ptr++;
  }
  population[i] = '\0';
  if (*ptr == ':') {
    count++;
    ptr++;
  }
  i = 0;
  state.population = strtol(population, NULL, 10);
  //corner case Alabama:123:
  if (*ptr == '\0') {
    printf("invalid input\n");
    exit(EXIT_FAILURE);
  }
  while (*ptr != '\0') {
    //vote must be number
    if (((*ptr - '0') < 0) || ((*ptr - '0')) > 9) {
      printf("invalid input\n");
      exit(EXIT_FAILURE);
    }
    vote[i] = *ptr;
    i++;
    ptr++;
  }
  vote[i] = '\0';
  state.electoralVotes = strtol(vote, NULL, 10);
  //not enough ':' found
  if (count != 2) {
    printf("not enough input\n");
    exit(EXIT_FAILURE);
  }
  return state;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int count = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (*voteCounts > (*stateData).population) {
      printf("people who vote are more than the total people in some state!\n");
      exit(EXIT_FAILURE);
    }
    else if (*voteCounts > (*stateData).population * 0.5) {
      count = count + (*stateData).electoralVotes;
    }
    voteCounts++;
    stateData++;
  }
  return count;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  double rate = 0;
  for (size_t i = 0; i < nStates; i++) {
    rate = (double)(*voteCounts) / (double)((*stateData).population) * 100;
    //printf("rate: %.2f", rate);
    if (rate > 100) {
      printf("people who vote are more than the total people in some state!\n");
      exit(EXIT_FAILURE);
    }
    else if ((rate < 50.5) && (rate > 49.5)) {
      printf(
          "%s requires a recount (Candidate A has %.2f%% of the vote)\n", (*stateData).name, rate);
    }
    voteCounts++;
    stateData++;
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  double rate = 0;
  double largest = 0;
  char * largestName = NULL;
  for (size_t i = 0; i < nStates; i++) {
    rate = (double)(*voteCounts) / (double)((*stateData).population) * 100;
    if (rate > 100) {
      printf("people who vote are more than the total people in some state!\n");
      exit(EXIT_FAILURE);
    }
    else if (rate > largest) {
      largest = rate;
      largestName = (*stateData).name;
    }
    voteCounts++;
    stateData++;
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", largestName, largest);
}
