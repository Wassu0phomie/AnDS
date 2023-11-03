#pragma once
#include <string>

class doublyLinkedList {
public:
    struct Node {
        int data;
        Node* prev;
        Node* next;
    };

    // Конструктор по умолчанию
    doublyLinkedList();

    // Деструктор
    ~doublyLinkedList();

    // Функции для работы с двусвязным списком
    Node* insertNode(int value, int index = -1);  // Вставка элемента по индексу
    bool deleteNode(int index);                  // Удаление элемента по индексу
    Node* findNode(int value);                   // Поиск элемента по значению
    void swapNodes(int index1, int index2);      // Обмен двух элементов по индексам
    int length();                                // Возвращает длину списка

    // Функции для вывода и управления списком
    void printList();                            // Вывод списка
    void createList(std::string);

private:
    Node* head;
};