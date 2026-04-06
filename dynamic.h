#pragma once
#include <iostream>
#include <string>
#include "exceptionhandler.h"
using namespace std;

template <typename T>
class DynamicArray {
private:
    T* items;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        T* newItems = new T[capacity];
        for (int i = 0; i < size; i++) newItems[i] = items[i];
        delete[] items;
        this->items = newItems; // REQUIREMENT: Use 'this'
    }

public:
    DynamicArray(int cap = 2) : size(0), capacity(cap) { items = new T[capacity]; }

    ~DynamicArray() {
        for (int i = 0; i < size; i++) delete items[i]; // Cleanup for pointers
        delete[] items;
    }

    // REQUIREMENT: operator[] must throw on invalid index
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw DojoException("Invalid Index: Access out of bounds.");
        }
        return items[index];
    }

    void operator+=(T item) {
        if (size >= capacity) resize();
        items[size++] = item;
    }

    // REQUIREMENT: operator-= must throw on invalid removal
    void operator-=(int index) {
        if (index < 0 || index >= size) {
            throw DojoException("Invalid Removal: Index does not exist.");
        }
        delete items[index]; // Memory cleanup
        for (int i = index; i < size - 1; i++) items[i] = items[i + 1];
        size--;
    }

    int getSize() const { return size; }
};