#pragma once
#include <iostream>
#include <forward_list>
#include <string>

class Stack {
public:
    Stack();

    void push(const std::string& item);
    void pop();
    std::string* top();
    void print() const;
    size_t _size();
    int mainStack();
private:
    std::forward_list<std::string> items;
    size_t size = 0;

};