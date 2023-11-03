#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

class DynamicArray {
private:
    int* data;
    int size;
    int currentSize;
public:
    DynamicArray();
    ~DynamicArray();

    void createArray(int newSize);
    void printArray();
    bool findElement(int value);
    void addElement(int value);
    void deleteElementByValue(int value);
    void deleteElementByIndex(int index);
    void fillArray(int* values, int count);
};

#endif