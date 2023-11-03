#include "Dl_List.h"
#include <iostream>

#include <fstream>
#include <sstream>


using namespace std;

doublyLinkedList::doublyLinkedList() {
    head = nullptr;
}

doublyLinkedList::~doublyLinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

doublyLinkedList::Node* doublyLinkedList::insertNode(int value, int index) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (!head) {
        head = newNode;
        return head;
    }

    if (index < 0 || index >= length()) {
        // Вставка в конец списка
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
    else {
        // Вставка по индексу
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        if (current->prev) {
            current->prev->next = newNode;
            newNode->prev = current->prev;
        }
        newNode->next = current;
        current->prev = newNode;
        if (index == 0) {
            head = newNode;
        }
    }

    return newNode;
}

bool doublyLinkedList::deleteNode(int index) {
    if (!head || index < 0 || index >= length()) {
        return false;
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    if (current->prev) {
        current->prev->next = current->next;
    }
    if (current->next) {
        current->next->prev = current->prev;
    }
    if (index == 0) {
        head = current->next;
    }

    delete current;
    return true;
}

doublyLinkedList::Node* doublyLinkedList::findNode(int value) {
    Node* current = head;
    while (current) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void doublyLinkedList::swapNodes(int index1, int index2) {
    Node* node1 = nullptr;
    Node* node2 = nullptr;

    Node* current = head;
    for (int i = 0; current && (node1 == nullptr || node2 == nullptr); i++) {
        if (i == index1) {
            node1 = current;
        }
        if (i == index2) {
            node2 = current;
        }
        current = current->next;
    }

    if (node1 && node2) {
        int temp = node1->data;
        node1->data = node2->data;
        node2->data = temp;
    }
}

int doublyLinkedList::length() {
    int count = 0;
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

void doublyLinkedList::printList() {
    Node* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void doublyLinkedList::createList(std::string list_numbers) {
    // Разбиваем строку на числа
    if (head) {
        // Очистить память от предыдущего списка, если он существует
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    head = nullptr;  // Обнулить указатель на голову списка
    std::istringstream iss(list_numbers);
    int number;
    while (iss >> number) {
        insertNode(number);
    }
}