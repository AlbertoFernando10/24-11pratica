#include "IntArray.h"
#include <stdexcept>

void IntArray::resize() {
    capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
    int* new_data = new int[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
}

IntArray::IntArray(int capacity) : data_(nullptr), size_(0), capacity_(capacity) {
    if (capacity_ > 0) {
        data_ = new int[capacity_];
    }
}

IntArray::~IntArray() {
    delete[] data_;
}

IntArray::IntArray(const IntArray& other) : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
    if (capacity_ > 0) {
        data_ = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
}

IntArray& IntArray::operator=(const IntArray& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        if (capacity_ > 0) {
            data_ = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        } else {
            data_ = nullptr;
        }
    }
    return *this;
}

size_t IntArray::size() const noexcept {
    return size_;
}

void IntArray::add(int value) {
    if (size_ >= capacity_) {
        resize();
    }
    data_[size_++] = value;
}

int IntArray::get(size_t index) const noexcept {
    if (index >= size_) {
        return 0;
    }
    return data_[index];
}

int IntArray::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Índice fora do intervalo");
    }
    return data_[index];
}

int IntArray::last() const {
    if (size_ == 0) {
        throw std::out_of_range("Array vazio");
    }
    return data_[size_ - 1];
}

void IntArray::insert(size_t index, int value) {
    if (index > size_) {
        throw std::out_of_range("Índice de inserção fora do intervalo");
    }
    if (size_ >= capacity_) {
        resize();
    }
    for (size_t i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }
    data_[index] = value;
    size_++;
}
