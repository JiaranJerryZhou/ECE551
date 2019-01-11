#include "IntMatrix.h"

#include <string.h>

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(new IntArray *[rhs.numRows]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
    for (int j = 0; j < numColumns; j++) {
      (*rows[i])[j] = (*rhs.rows[i])[j];
    }
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray(rhs.numColumns);
      for (int j = 0; j < rhs.numColumns; j++) {
        (*temp[i])[j] = (*rhs.rows[i])[j];
      }
    }
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = temp;
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert((index < numRows) && (index >= 0));
  const IntArray & ref = *rows[index];
  return ref;
}
IntArray & IntMatrix::operator[](int index) {
  assert((index < numRows) && (index >= 0));
  IntArray & ref = *rows[index];
  return ref;
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows) {
    return false;
  }
  if (numColumns != rhs.numColumns) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      if ((*rows[i])[j] != (*rhs.rows[i])[j]) {
        return false;
      }
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      (*rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
    }
  }
  return *this;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s.write("[ ", strlen("[ "));
  for (int i = 0; i < rhs.getRows(); i++) {
    if (i != rhs.getRows() - 1) {
      s << rhs[i];
      s.write(",\n", strlen(",\n"));
    }
    else {
      s << rhs[i];
    }
  }
  s.write(" ]", strlen(" ]"));
  return s;
}
