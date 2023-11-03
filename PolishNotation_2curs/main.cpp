#include "Dl_List.h"
#include "RPN.h"
#include "Stack.h"
#include "dynamicArray.h"
#include <iostream>

using namespace std;

int main()
{
    while (true) {
        std::system("cls");
        cout <<
            "Choose the command:\n"
            "(1) - Doubly-linked liste\n"
            "(2) - Dynamic array\n"
            "(3) - Stack\n"
            "(4) - Reverse Polish Notation\n"
            "(0) - Exit\n\n";
        cout << "Action >> ";

        char choice;
        cin >> choice;
        switch (choice) {
        case '0': {
            exit(0);
        }
        case '1': {
            bool innerLoop = true;
            doublyLinkedList myLinkedList;
            char choice;
            while (innerLoop) {
                std::system("cls");
                cout <<
                    "Choose the command:\n"
                    "(1) - Create new list\n"
                    "(2) - Insert node\n"
                    "(3) - Delete node\n"
                    "(4) - Find node\n"
                    "(5) - Swap nodes\n"
                    "(6) - Print list\n"
                    "(0) - Exit\n\n";
                cout << "Action >> ";
                std::cin >> choice;
                switch (choice) {
                case '0': {
                    innerLoop = false;
                    break;
                }

                case '1': {

                    std::cout << "Enter a space-separated list of numbers: ";
                    std::cin.ignore(); // Очистите буфер ввода
                    std::string input;
                    std::getline(std::cin, input);
                    myLinkedList.createList(input);
                    std::cout << "New list created.\n";
                    break;
                }
                case '2': {
                    int value, index;
                    std::cout << "Enter the value to insert: ";
                    std::cin >> value;
                    std::cout << "Enter the index to insert at (or -1 for end): ";
                    std::cin >> index;
                    myLinkedList.insertNode(value, index);
                    std::cout << "Node inserted.\n";
                    break;
                }
                case '3': {
                    int index;
                    std::cout << "Enter the index to delete: ";
                    std::cin >> index;
                    if (myLinkedList.deleteNode(index)) {
                        std::cout << "Node deleted.\n";
                    }
                    else {
                        std::cout << "Invalid index or list is empty.\n";
                    }
                    break;
                }
                case '4': {
                    int value;
                    std::cout << "Enter the value to find: ";
                    std::cin >> value;
                    doublyLinkedList::Node* foundNode = myLinkedList.findNode(value);
                    if (foundNode) {
                        std::cout << "Value found in the list.\n";
                    }
                    else {
                        std::cout << "Value not found in the list.\n";
                    }
                    break;
                }
                case '5': {
                    int index1, index2;
                    myLinkedList.printList();
                    std::cout << "\nEnter the indices to swap: ";
                    std::cin >> index1 >> index2;
                    myLinkedList.swapNodes(index1, index2);
                    std::cout << "Nodes swapped.\n";
                    break;
                }
                case '6':
                    std::cout << "List contents: ";
                    myLinkedList.printList();
                    break;

                default:
                    std::cout << "Invalid choice. Try again.\n";
                    break;
                }   
                if (innerLoop) std::system("pause");
            }
            break;
        }
        case '2': {
            bool innerLoop = true;
            DynamicArray dArray;
            char choice;
            int value;
            int index;
            int* customValues = nullptr; // Для хранения пользовательских значений
            int customCount = 0; // Количество пользовательских значений

            while (innerLoop) {
                std::system("cls");
                cout << 
                "Menu:\n"
                "(1) - Create array\n"
                "(2) - Fill array with custom values\n"
                "(3) - Print array\n"
                "(4) - Add element\n"
                "(5) - Delete element by value\n"
                "(6) - Delete element by index\n"
                "(0) - Exit\n\n";
                cout << "Action >> ";
                std::cin >> choice;

                switch (choice) {
                case '0':
                    innerLoop = false;
                    break;

                case '1':
                    int size;
                    std::cout << "Input array size: ";
                    std::cin >> size;
                    dArray.createArray(size);
                    break;
                case '2':
                    std::cout << "Enter the number of custom values (0 ... " << size << "): ";
                    std::cin >> customCount;
                    customValues = new int[customCount];
                    std::cout << "Enter " << customCount << " custom values: ";
                    for (int i = 0; i < customCount; i++) {
                        std::cin >> customValues[i];
                    }
                    dArray.fillArray(customValues, customCount);
                    delete[] customValues; // Очистить выделенную память
                    break;
                case '3':
                    dArray.printArray();
                    break;

                case '4':
                    std::cout << "Enter value to add: ";
                    std::cin >> value;
                    dArray.addElement(value);
                    break;

                case '5':
                    std::cout << "Enter value to delete: ";
                    std::cin >> value;
                    dArray.deleteElementByValue(value);
                    break;

                case '6':
                    std::cout << "Enter index to delete: ";
                    std::cin >> index;
                    dArray.deleteElementByIndex(index);
                    break;

                default: {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
                }
                }
                if (innerLoop) std::system("pause");
            }
            break;
        }
        case '3': {
            Stack stack;
            bool innerLoop = true;
            while (innerLoop) {
                std::system("cls");
                std::cout << "Menu:" << std::endl;
                cout << 
                     "(1) - Push element\n"
                     "(2) - Pop element\n"
                     "(3) - Return top\n"
                     "(4) - Return stack size\n"
                     "(5) - Print stack\n"
                     "(0) - Quit\n\n";
                cout << "Action >> ";
                char choice;
                std::cin >> choice;
                switch (choice) {
                case '0': {
                    innerLoop = false;
                    break;
                }
                case '1': {
                    std::string element;
                    std::cout << "Enter element to push: ";
                    std::cin >> element;
                    stack.push(element);
                    break;
                }
                case '2': {
                    stack.pop();
                    break;
                }
                case '3': {
                    std::string* top = stack.top();
                    if (top != nullptr)
                        std::cout << "Top element: " << *top << std::endl;
                    else
                        std::cout << "The Stack is empty" << std::endl;
                    break;
                }
                case '4': {
                    std::cout << "Stack size: " << stack._size() << std::endl;
                    break;
                }
                case '5': {
                    std::cout << "Stack: ";
                    stack.print();
                    break;
                }
                default: {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
                }
                }
                if (innerLoop) std::system("pause");
            }
            break;
        }           
        case '4':
            mainRPN();
            break;
        default:
            cout << "\nProject with number " << choice << " does not exist." << endl;
            std::system("pause");
            break;
        }
    }
}


