#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Stack {
private:
    // Вложенный класс узла
    class Node {
    public:
        int data;
        Node* next;

        Node(int value) : data(value), next(nullptr) {}
    };

    Node* top;  // Указатель на вершину стека

public:
    Stack() : top(nullptr) {}

    // Добавление элемента на вершину стека
    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    // Удаление элемента с вершины стека
    void pop() {
        if (top == nullptr) {
            cout << "Stack is empty" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    // Просмотр верхнего элемента стека
    void peek() const {
        if (top == nullptr) {
            cout << "Stack is empty" << endl;
        } else {
            cout << top->data << endl;
        }
    }

    // Вывод всех элементов стека
    void print() const {
        if (top == nullptr) {
            cout << "Stack is empty" << endl;
            return;
        }
        Node* temp = top;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Запись стека в файл
    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            Node* temp = top;
            while (temp != nullptr) {
                outFile << temp->data << " ";
                temp = temp->next;
            }
            outFile.close();
        } else {
            cout << "Error opening file for writing" << endl;
        }
    }

    // Загрузка стека из файла
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            clear();  // Очистка текущего стека
            Stack tempStack; // Используем временный стек для сохранения порядка
            int value;
            while (inFile >> value) {
                tempStack.push(value);
            }
            while (tempStack.top != nullptr) {
                push(tempStack.top->data);
                tempStack.pop();
            }
            inFile.close();
        } else {
            cout << "Error opening file for reading" << endl;
        }
    }

    // Очистка стека
    void clear() {
        while (top != nullptr) {
            pop();
        }
    }

    // Деструктор
    ~Stack() {
        clear();
    }
};
