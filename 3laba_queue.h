#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

using namespace std;

class Queue {
private:
    // Вложенный класс узла
    class Node {
    public:
        int data;
        Node* next;

        Node(int value) : data(value), next(nullptr) {}
    };

    Node* front;  // Указатель на голову очереди
    Node* rear;   // Указатель на хвост очереди

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Добавление элемента в конец очереди
    void push(int value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Удаление элемента с головы очереди
    void pop() {
        if (front == nullptr) {
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;  // Если очередь стала пустой
        }
        delete temp;
    }

    // Просмотр элемента на голове очереди
    void peek() const {
        if (front == nullptr) {
            cout << "Queue is empty" << endl;
        } else {
            cout << "Front element: " << front->data << endl;
        }
    }

    // Запись очереди в файл
    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            Node* temp = front;
            while (temp != nullptr) {
                outFile << temp->data;
                if (temp->next != nullptr) {
                    outFile << " "; // Пробел только между элементами
                }
                temp = temp->next;
            }
            outFile.close();
        }
    }

    // Загрузка очереди из файла
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            int value;
            while (inFile >> value) {
                push(value);
            }
            inFile.close();
        } 
    }

    // Вывод содержимого очереди
    void print() const {
        if (front == nullptr) {
            cout << "Queue is empty" << endl;
        } else {
            Node* temp = front;
            cout << "Queue elements:";
            while (temp != nullptr) {
                cout << " " << temp->data; // Между элементами добавляем пробел
                temp = temp->next;
            }
            cout << endl;
        }
    }

    // Очистка очереди
    void clear() {
        while (front != nullptr) {
            pop();
        }
    }

    // Деструктор для освобождения памяти
    ~Queue() {
        clear();
    }
};
