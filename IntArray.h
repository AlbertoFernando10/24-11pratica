#ifndef INTARRAY_H
#define INTARRAY_H

#include <cstddef>

class IntArray {
private:
    int* data_;
    size_t size_;
    size_t capacity_;

    void resize();

public:
    IntArray(int capacity);
    ~IntArray();
    IntArray(const IntArray& other);
    IntArray& operator=(const IntArray& other);

    size_t size() const noexcept;
    void add(int value);
    int get(size_t index) const noexcept;
    int at(size_t index) const;
    int last() const;
    void insert(size_t index, int value);
};

#endif
