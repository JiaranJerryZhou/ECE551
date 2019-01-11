
#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL){};
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T> *[r]) {
    for (int i = 0; i < r; i++) {
      rows[i] = new std::vector<T>(c);
    }
  }
  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(new std::vector<T> *[rhs.numRows]) {
    for (int i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(numColumns);
      for (int j = 0; j < numColumns; j++) {
        (*rows[i])[j] = rhs[i][j];
      }
    }
  }
  ~Matrix() {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }
  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      std::vector<T> ** temp = new std::vector<T> *[rhs.numRows];
      for (int i = 0; i < rhs.numRows; i++) {
        temp[i] = new std::vector<T>(rhs.numColumns);
        for (int j = 0; j < rhs.numColumns; j++) {
          (*temp[i])[j] = rhs[i][j];
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
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert((index < numRows) && (index >= 0));
    const std::vector<T> & ref = *rows[index];
    return ref;
  }
  std::vector<T> & operator[](int index) {
    assert((index < numRows) && (index >= 0));
    std::vector<T> & ref = *rows[index];
    return ref;
  }

  bool operator==(const Matrix & rhs) const {
    if (numRows != rhs.numRows) {
      return false;
    }
    if (numColumns != rhs.numColumns) {
      return false;
    }
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        if ((*rows[i])[j] != rhs[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        (*rows[i])[j] = (*rows[i])[j] + rhs[i][j];
      }
    }
    return *this;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    if (i != rhs.getRows() - 1) {
      //for (size_t j = 0; j < rhs[i].size(); j++) {
      // s << rhs[i][j];
      //}
      s << rhs[i] << ",\n";
    }
    else {
      //for (size_t j = 0; j < rhs[i].size(); j++) {
      //  s << rhs[i][j];
      //}
      s << rhs[i];
    }
  }
  s << " ]";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  s << "{";
  for (size_t i = 0; i < rhs.size(); i++) {
    if (i != rhs.size() - 1) {
      s << rhs[i] << ", ";
    }
    else {
      s << rhs[i];
    }
  }
  s << "}";
  return s;
}

#endif
