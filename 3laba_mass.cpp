#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct Array {
    static const int capacity = 10000;  // фиксированная вместимость
    int data[capacity];  // массив 
    int length;          // текущее количество элементов
    Array() : length(0) {} 

    // функция добавления эл. в конец
    void push_back(int value) {
        if (length < capacity) {
            data[length++] = value;  // добавляем элемент в конец
        } else {
            cout << "Array is full" << endl;
        }
    }

    // Удаление элемента по индексу
    void remove(int index) {
        if (index >= 0 && index < length) {
            for (int i = index; i < length - 1; i++) {
                data[i] = data[i + 1];  // сдвигаем элементы влево
            }
            length--;
        } else {
            cout << "Invalid index" << endl;
        }
    }

    // Замена элемента по индексу
    void replace(int index, int value) {
        if (index >= 0 && index < length) {
            data[index] = value;  // заменяем элемент
        } else {
            cout << "Invalid index" << endl;
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

     // Сериализация массива в бинарный файл
    void saveToBinaryFile(const string &filename) const {
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open()) {
            // Записываем длину массива
            outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
            // Записываем сами элементы массива
            outFile.write(reinterpret_cast<const char*>(data), length * sizeof(int));
            outFile.close();
            cout << "Array serialized to binary file: " << filename << endl;
        } else {
            cout << "Cannot open file for writing" << endl;
        }
    }

    // Десериализация массива из бинарного файла
    void loadFromBinaryFile(const string &filename) {
        ifstream inFile(filename, ios::binary);
        if (inFile.is_open()) {
            // Считываем длину массива
            inFile.read(reinterpret_cast<char*>(&length), sizeof(length));
            if (length > capacity) {
                cout << "File contains more elements than array capacity" << endl;
                inFile.close();
                return;
            }
            // Считываем сами элементы массива
            inFile.read(reinterpret_cast<char*>(data), length * sizeof(int));
            inFile.close();
            cout << "Array deserialized from binary file: " << filename << endl;
        } else {
            cout << "Cannot open file for reading" << endl;
        }
    }
};

// Функция обработки команд
void processCommand(Array &arr, const string &commandLine) {
    stringstream ss(commandLine);
    string command;
    ss >> command;

    if (command == "PUSH") {
        int value;
        ss >> value;
        arr.push_back(value);

    } else if (command == "PRINT") {
        arr.print();

    } else if (command == "SAVE_BIN") {
        string filename;
        ss >> filename;
        arr.saveToBinaryFile(filename);

    } else if (command == "LOAD_BIN") {
        string filename;
        ss >> filename;
        arr.loadFromBinaryFile(filename);
    }
}

int main() {
    Array arr;
    string commandLine;

    while (true) {
        getline(cin, commandLine);

        if (commandLine == "EXIT") {
            break; // выход из программы
        }

        processCommand(arr, commandLine);
    }

    return 0;
}
