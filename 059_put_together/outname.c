#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME

  const char * suffix = ".counts";
  unsigned len = strlen(inputName) + strlen(suffix) + 1;
  char * outputName = malloc(len * sizeof(*outputName));
  outputName = strcpy(outputName, inputName);
  outputName = strcat(outputName, suffix);
  return outputName;
}
