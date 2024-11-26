#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <gtest/gtest.h>

using namespace std;

// Узел для хранения пары ключ-значение
class KeyValuePair {
public:
    string key;
    string value;
    KeyValuePair* next;

    KeyValuePair(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

// Класс хеш-таблицы
class HashTable {
private:
    static const int capacity = 10;
    KeyValuePair* table[capacity];

    // Хеш-функция
    int hashFunction(const string& key) const {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return sum % capacity;
    }

public:
    // Конструктор
    HashTable() {
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    // Деструктор
    ~HashTable() {
        for (int i = 0; i < capacity; i++) {
            KeyValuePair* current = table[i];
            while (current != nullptr) {
                KeyValuePair* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }

    // Добавление элемента
    void insert(const string& key, const string& value) {
        int index = hashFunction(key);
        KeyValuePair* newNode = new KeyValuePair(key, value);
        KeyValuePair* current = table[index];

        // Проверяем существование ключа
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value; // Обновляем значение, если ключ существует
                delete newNode;
                return;
            }
            current = current->next;
        }

        // Вставка нового элемента
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Получение значения по ключу
    string get(const string& key) const {
        int index = hashFunction(key);
        KeyValuePair* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return "Key not found";
    }

    // Удаление элемента по ключу
    void remove(const string& key) {
        int index = hashFunction(key);
        KeyValuePair* current = table[index];
        KeyValuePair* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    // Вывод всей хеш-таблицы
    void print() const {
        bool firstElement = true;  // Флаг для правильного форматирования

        for (int i = 0; i < capacity; i++) {
            KeyValuePair* current = table[i];
            while (current != nullptr) {
                if (!firstElement) {
                    cout << " ";  // Добавляем пробел перед следующим элементом
                }
                cout << "{" << current->key << ": " << current->value << "}";
                firstElement = false;
                current = current->next;
            }
        }
        cout << endl;
    }

    // Сохранение в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        for (int i = 0; i < capacity; i++) {
            KeyValuePair* current = table[i];
            while (current != nullptr) {
                file << current->key << " " << current->value << endl;
                current = current->next;
            }
        }
        file.close();
    }

    // Загрузка из файла
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string key, value;
        while (file >> key >> value) {
            insert(key, value);
        }
        file.close();
    }
};

