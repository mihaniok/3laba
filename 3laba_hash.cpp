#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Класс для хранения пары ключ-значение
class KeyValuePair {
public:
    string key;
    string value;
    KeyValuePair* next;

    KeyValuePair(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

// Размер хеш-таблицы
const int capacity = 10;

// Класс для хеш-таблицы
class HashTable {
private:
    KeyValuePair* table[capacity];  // Массив цепочек

public:
    // Конструктор, инициализирующий массив пустыми цепочками
    HashTable() {
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    // Деструктор для освобождения памяти
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

    // Хеш-функция: вычисляет индекс по сумме ASCII-кодов символов ключа
    int hashFunction(const string& key) const {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return sum % capacity;
    }

    // Добавление элемента (ключ-значение) в хеш-таблицу
    void insert(const string& key, const string& value) {
        int index = hashFunction(key);
        KeyValuePair* newNode = new KeyValuePair(key, value);
        KeyValuePair* current = table[index];

        // Проверяем, существует ли элемент с таким же ключом
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;  // Обновляем значение, если ключ уже существует
                delete newNode;
                return;
            }
            current = current->next;
        }

        // Вставляем новый элемент в начало цепочки
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
        return "key is not found";
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
        cout << "key is not found" << endl;
    }

    // Вывод всей хеш-таблицы
    void print() const {
        for (int i = 0; i < capacity; i++) {
            cout << "[" << i << "]: ";
            KeyValuePair* current = table[i];
            while (current != nullptr) {
                cout << "{" << current->key << ": " << current->value << "} ";
                current = current->next;
            }
            cout << endl;
        }
    }

    // Сериализация хеш-таблицы в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cout << "Ошибка при открытии файла для записи!" << endl;
            return;
        }
        for (int i = 0; i < capacity; i++) {
            KeyValuePair* current = table[i];
            while (current != nullptr) {
                file << current->key << " " << current->value << endl;
                current = current->next;
            }
        }
        file.close();
        cout << "Хеш-таблица сохранена в файл." << endl;
    }

    // Загрузка хеш-таблицы из файла
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Ошибка при открытии файла для чтения!" << endl;
            return;
        }
        string key, value;
        while (file >> key >> value) {
            insert(key, value);
        }
        file.close();
        cout << "Хеш-таблица загружена из файла." << endl;
    }
};

// Функция обработки команд
void processCommand(HashTable& hashTable, const string& commandLine) {
    stringstream ss(commandLine);
    string command, key, value;
    ss >> command;

    if (command == "INSERT") {
        ss >> key >> value;
        hashTable.insert(key, value);
    } else if (command == "GET") {
        ss >> key;
        cout << "Значение: " << hashTable.get(key) << endl;
    } else if (command == "REMOVE") {
        ss >> key;
        hashTable.remove(key);
    } else if (command == "PRINT") {
        hashTable.print();
    } else if (command == "SAVE") {
        string filename;
        ss >> filename;
        hashTable.saveToFile(filename);
    } else if (command == "LOAD") {
        string filename;
        ss >> filename;
        hashTable.loadFromFile(filename);
    }
}

int main() {
    HashTable hashTable;
    string commandLine;

    while (true) {
        getline(cin, commandLine);
        if (commandLine == "EXIT") {
            break;
        }
        processCommand(hashTable, commandLine);
    }

    return 0;
}
