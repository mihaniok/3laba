#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

using namespace std;

class DoublyLinkedList {
private:
    // Вложенный класс вместо структуры
    class Node {
    public:
        int data;
        Node* next;
        Node* prev;

        Node(int value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Добавление элемента в начало
    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Добавление элемента в конец
    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Удаление элемента с начала
    void pop_front() {
        if (!head) return;
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
    }

    // Удаление элемента с конца
    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
    }

    // Удаление элемента по значению
    void remove(int value) {
        Node* temp = head;
        while (temp && temp->data != value) {
            temp = temp->next;
        }
        if (!temp) return;

        if (temp == head) {
            pop_front();
        } else if (temp == tail) {
            pop_back();
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
    }

    // Поиск элемента по значению
    bool find(int value) const {
        Node* temp = head;
        while (temp) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }

    // Вывод всех элементов списка
    void print() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Запись списка в файл
    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            Node* temp = head;
            while (temp) {
                outFile << temp->data << " ";
                temp = temp->next;
            }
            outFile.close();
        } else {
            cout << "Не удалось открыть файл для записи!" << endl;
        }
    }

    // Загрузка списка из файла
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            int value;
            while (inFile >> value) {
                push_back(value);
            }
            inFile.close();
        } else {
            cout << "Не удалось открыть файл для чтения!" << endl;
        }
    }

    ~DoublyLinkedList() {
        while (head) {
            pop_front();
        }
    }
};
