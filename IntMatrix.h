#ifndef INTMATRIX_H
#define INTMATRIX_H

#include "IntArray.h"
#include <iostream>

class IntMatrix {
private:
    IntArray* data_;
    size_t rows_;
    size_t cols_;

public:
    IntMatrix(size_t rows, size_t cols);
    ~IntMatrix();
    IntMatrix(const IntMatrix& other);
    IntMatrix& operator=(const IntMatrix& other);

    void readFromStream(std::istream& in);
    void print(std::ostream& out) const;
    void addRow(size_t after, int value);
    void addColumn(size_t after, int value);
    size_t getRows() const noexcept;
    size_t getCols() const noexcept;
};

#endif
