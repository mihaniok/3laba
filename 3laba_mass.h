#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <gtest/gtest.h>

using namespace std;

class Array {
private:
    static const int capacity = 10000;  // фиксированная вместимость
    int data[capacity];  // массив
    int length;          // текущее количество элементов

public:
    Array() : length(0) {}

    // функция добавления элемента в конец
    void push_back(int value) {
        if (length < capacity) {
            data[length++] = value;  // добавляем элемент в конец
        } 
    }

    // Удаление элемента по индексу
    void remove(int index) {
        if (index >= 0 && index < length) {
            for (int i = index; i < length - 1; i++) {
                data[i] = data[i + 1];  // сдвигаем элементы влево
            }
            length--;
        }
    }

    // Замена элемента по индексу
    void replace(int index, int value) {
        if (index >= 0 && index < length) {
            data[index] = value;  // заменяем элемент
        }
    }

    // Получение элемента по индексу
    int get(int index) const {
        return index >= 0 && index < length ? data[index] : -1;  // возвращает -1 при неверном индексе
    }

    // Получение длины массива
    int size() const {
        return length;
    }

    // Вывод элементов массива
    void print() const {
        for (int i = 0; i < length; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Сериализация в бинарный формат
    void saveToBinaryFile(const string &filename) const {
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open()) {
            outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
            outFile.write(reinterpret_cast<const char*>(data), length * sizeof(int));
            outFile.close();
        }
    }

    // Десериализация из бинарного формата
    void loadFromBinaryFile(const string &filename) {
        ifstream inFile(filename, ios::binary);
        if (inFile.is_open()) {
            inFile.read(reinterpret_cast<char*>(&length), sizeof(length));
            inFile.read(reinterpret_cast<char*>(data), length * sizeof(int));
            inFile.close();
        }
    }
};
