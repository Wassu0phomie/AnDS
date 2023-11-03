#include "Stack.h"
#include <iostream>

Stack::Stack() {

}

void Stack::push(const std::string& element) {
    items.push_front(element);
    size++;
}

void Stack::pop() {
    if (!items.empty()) {
        items.pop_front();
        size--;
    }
    else {
        std::cout << "Stack is empty. Cannot pop." << '\n';
    }
}

std::string* Stack::top() {
    if (!items.empty()) {
        return &items.front();
    }
    return nullptr;
}

size_t Stack::_size() {
    return size;
}

void Stack::print() const {
    for (const auto& item : items) {
        std::cout << item << " ";
    }
    std::cout << '\n';
}


