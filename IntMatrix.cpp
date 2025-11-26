#include "IntMatrix.h"
#include <stdexcept>

IntMatrix::IntMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
    data_ = new IntArray[rows_];
    for (size_t i = 0; i < rows_; ++i) {
        data_[i] = IntArray(static_cast<int>(cols));
        for (size_t j = 0; j < cols_; ++j) {
            data_[i].add(0);
        }
    }
}

IntMatrix::~IntMatrix() {
    delete[] data_;
}

IntMatrix::IntMatrix(const IntMatrix& other) : rows_(other.rows_), cols_(other.cols_) {
    data_ = new IntArray[rows_];
    for (size_t i = 0; i < rows_; ++i) {
        data_[i] = other.data_[i];
    }
}

IntMatrix& IntMatrix::operator=(const IntMatrix& other) {
    if (this != &other) {
        delete[] data_;
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = new IntArray[rows_];
        for (size_t i = 0; i < rows_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

void IntMatrix::readFromStream(std::istream& in) {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            int value;
            if (!(in >> value)) {
                throw std::runtime_error("Erro ao ler dados da matriz");
            }
            IntArray newRow(cols_);
            for (size_t k = 0; k < cols_; ++k) {
                if (k == j) {
                    newRow.add(value);
                } else {
                    newRow.add(data_[i].get(k));
                }
            }
            data_[i] = newRow;
        }
    }
}

void IntMatrix::print(std::ostream& out) const {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            out << data_[i].get(j);
            if (j < cols_ - 1) out << " ";
        }
        out << "\n";
    }
}

void IntMatrix::addRow(size_t after, int value) {
    if (after > rows_) {
        throw std::invalid_argument("Índice de linha inválido");
    }

    IntArray* newData = new IntArray[rows_ + 1];
    for (size_t i = 0; i < after; ++i) {
        newData[i] = data_[i];
    }
    newData[after] = IntArray(static_cast<int>(cols_));
    for (size_t j = 0; j < cols_; ++j) {
        newData[after].add(value);
    }
    for (size_t i = after; i < rows_; ++i) {
        newData[i + 1] = data_[i];
    }
    delete[] data_;
    data_ = newData;
    rows_++;
}

void IntMatrix::addColumn(size_t after, int value) {
    if (after > cols_) {
        throw std::invalid_argument("Índice de coluna inválido");
    }

    for (size_t i = 0; i < rows_; ++i) {
        IntArray newRow(cols_ + 1);
        for (size_t j = 0; j < after; ++j) {
            newRow.add(data_[i].get(j));
        }
        newRow.add(value);
        for (size_t j = after; j < cols_; ++j) {
            newRow.add(data_[i].get(j));
        }
        data_[i] = newRow;
    }
    cols_++;
}

size_t IntMatrix::getRows() const noexcept { return rows_; }
size_t IntMatrix::getCols() const noexcept { return cols_; }
