#include<iostream>
#include "dynamicArray.h"

DynamicArray::DynamicArray() : size(0), data(nullptr) {}
DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::createArray(int newSize) {
    if (data != nullptr)
        delete[] data;

    size = newSize;
    data = new int[size];

    for (int i = 0; i < size; i++)
        data[i] = 0;
}

void DynamicArray::printArray() {
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

bool DynamicArray::findElement(int value) {
    for (int i = 0; i < size; i++) {
        if (data[i] == value)
            return true;
    }
    return false;
}

void DynamicArray::addElement(int value) {
    int* newArray = new int[size + 1];

    for (int i = 0; i < size; i++)
        newArray[i] = data[i];

    newArray[size] = value;

    delete[] data;
    data = newArray;

    size++;
}

void DynamicArray::deleteElementByValue(int value) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (data[i] == value) {
            index = i;
            break;
        }
    }

    if (index == -1)
        return;

    deleteElementByIndex(index);
}

void DynamicArray::deleteElementByIndex(int index) {
    if (index < 0 || index >= size)
        return;

    for (int i = index; i < size - 1; i++)
        data[i] = data[i + 1];

    size--;

    int* newArray = new int[size];
    for (int i = 0; i < size; i++)
        newArray[i] = data[i];

    delete[] data;
    data = newArray;
}

void DynamicArray::fillArray(int* values, int count) {
    if (data == nullptr) {
        std::cout << "Array is not created yet." << std::endl;
        return;
    }

    if (count <= size) {
        for (int i = 0; i < count; i++) {
            data[i] = values[i];
        }
        currentSize = count;
        std::cout << "Array filled with " << count << " values." << std::endl;
    }
    else {
        std::cout << "Not enough space in the array to fill with " << count << " values." << std::endl;
    }
}