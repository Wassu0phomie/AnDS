#pragma once
#include <string>

class doublyLinkedList {
public:
    struct Node {
        int data;
        Node* prev;
        Node* next;
    };

    // ����������� �� ���������
    doublyLinkedList();

    // ����������
    ~doublyLinkedList();

    // ������� ��� ������ � ���������� �������
    Node* insertNode(int value, int index = -1);  // ������� �������� �� �������
    bool deleteNode(int index);                  // �������� �������� �� �������
    Node* findNode(int value);                   // ����� �������� �� ��������
    void swapNodes(int index1, int index2);      // ����� ���� ��������� �� ��������
    int length();                                // ���������� ����� ������

    // ������� ��� ������ � ���������� �������
    void printList();                            // ����� ������
    void createList(std::string);

private:
    Node* head;
};