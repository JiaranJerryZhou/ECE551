#include "IntArray.h"

#include <assert.h>
#include <string.h>

#include <cstdio>
#include <ostream>
IntArray::IntArray() : data(NULL), numElements(0) {}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    numElements = rhs.numElements;
    data = temp;
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
  assert((index < numElements) && (index >= 0));
  const int & ref = data[index];
  return ref;
}
int & IntArray::operator[](int index) {
  assert((index < numElements) && (index >= 0));
  int & ref = data[index];
  return ref;
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (numElements == rhs.numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] == rhs.data[i]) {
      return false;
    }
  }
  return true;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  //const char * leftBrace = "{";
  s.write("{", strlen("{"));
  for (int i = 0; i < rhs.size(); i++) {
    if (i != rhs.size() - 1) {
      char asString[16];
      snprintf(asString, 16, "%d", rhs[i]);
      s.write(asString, strlen(asString));
      s.write(", ", strlen(", "));
    }
    else {
      char asString[16];
      snprintf(asString, 16, "%d", rhs[i]);
      s.write(asString, strlen(asString));
    }
  }
  s.write("}", strlen("}"));
  return s;
}
