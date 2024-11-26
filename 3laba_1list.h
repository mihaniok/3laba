#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <gtest/gtest.h>

using namespace std;

class SinglyLinkedList {
private:
    class Node {
    public:
        int data;
        Node* next;

        Node(int value) : data(value), next(nullptr) {}
    };

    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    // Добавление элемента в голову
    void push_front(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Добавление элемента в хвост
    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Удаление элемента с головы
    void pop_front() {
        if (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Удаление элемента с хвоста
    void pop_back() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* temp = head;
            while (temp->next && temp->next->next) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }

    // Удаление элемента по значению
    void remove(int value) {
        if (!head) return;
        if (head->data == value) {
            pop_front();
            return;
        }
        Node* temp = head;
        while (temp->next && temp->next->data != value) {
            temp = temp->next;
        }
        if (temp->next) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
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

    ~SinglyLinkedList() {
        // Освобождение памяти
        while (head) {
            pop_front();
        }
    }
};
