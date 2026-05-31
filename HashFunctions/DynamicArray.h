#pragma once
#include <iostream>

template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int size;

    void resize();
    void resizeDown();

public:
    DynamicArray();
    DynamicArray(int n);
    ~DynamicArray();

    // Copy constructor and assignment operator (essential for correct rehashing/deep copy)
    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other);

    void addFront(T val);
    void addEnd(T val);
    void addAtIndex(int idx, T val);
    void removeFront();
    void removeEnd();
    void removeAtIndex(int idx);

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
    void clear();

    // Operator overloading for convenient element access
    T& operator[](int idx) { return data[idx]; }
    const T& operator[](int idx) const { return data[idx]; }
};

template <typename T>
DynamicArray<T>::DynamicArray() : capacity(2), size(0) {
    data = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(int n) : capacity(n), size(0) {
    if (capacity <= 0) capacity = 1;
    data = new T[capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) {
    capacity = other.capacity;
    size = other.size;
    data = new T[capacity];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
void DynamicArray<T>::resize() {
    int newCapacity = capacity * 2;
    T* newData = new T[newCapacity];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
void DynamicArray<T>::resizeDown() {
    if (capacity / 2 < size) return;
    int newCapacity = capacity / 2;
    if (newCapacity < 1) newCapacity = 1;
    T* newData = new T[newCapacity];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
void DynamicArray<T>::addFront(T val) {
    if (size == capacity) resize();
    for (int i = size; i > 0; --i) {
        data[i] = data[i - 1];
    }
    data[0] = val;
    size++;
}

template <typename T>
void DynamicArray<T>::addEnd(T val) {
    if (size == capacity) resize();
    data[size] = val;
    size++;
}

template <typename T>
void DynamicArray<T>::addAtIndex(int idx, T val) {
    if (idx < 0 || idx > size) return;
    if (size == capacity) resize();
    for (int i = size; i > idx; --i) {
        data[i] = data[i - 1];
    }
    data[idx] = val;
    size++;
}

template <typename T>
void DynamicArray<T>::removeFront() {
    if (size == 0) return;
    for (int i = 0; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
    if (capacity > 1 && size < capacity / 2) resizeDown();
}

template <typename T>
void DynamicArray<T>::removeEnd() {
    if (size == 0) return;
    size--;
    if (capacity > 1 && size < capacity / 2) resizeDown();
}

template <typename T>
void DynamicArray<T>::removeAtIndex(int idx) {
    if (idx < 0 || idx >= size) return;
    for (int i = idx; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
    if (capacity > 1 && size < capacity / 2) resizeDown();
}

template <typename T>
void DynamicArray<T>::clear() {
    delete[] data;
    capacity = 2;
    size = 0;
    data = new T[capacity];
}