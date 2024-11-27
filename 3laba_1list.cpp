#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

// Узел односвязного списка
class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Односвязный список
class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList() {
        while (head) {
            pop_front(); // Удаляем элементы, чтобы избежать утечек памяти
        }
    }

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

    // Вывод всех элементов списка
    void print() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Сериализация в бинарный файл
    void saveToBinaryFile(const string& filename) const {
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open()) {
            Node* temp = head;
            while (temp) {
                outFile.write(reinterpret_cast<const char*>(&temp->data), sizeof(temp->data));
                temp = temp->next;
            }
            outFile.close();
            cout << "Список сохранен в бинарный файл: " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для записи!" << endl;
        }
    }

    // Десериализация из бинарного файла
    void loadFromBinaryFile(const string& filename) {
        ifstream inFile(filename, ios::binary);
        if (inFile.is_open()) {
            // Очищаем текущий список
            while (head) {
                pop_front();
            }

            int value;
            while (inFile.read(reinterpret_cast<char*>(&value), sizeof(value))) {
                push_back(value);
            }
            inFile.close();
            cout << "Список загружен из бинарного файла: " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для чтения!" << endl;
        }
    }
};

// Функция обработки команд
void processCommand(SinglyLinkedList& list, const string& commandLine) {
    stringstream ss(commandLine);
    string command;
    ss >> command;

    if (command == "PUSHFRONT") {
        int value;
        ss >> value;
        list.push_front(value);

    } else if (command == "PUSHBACK") {
        int value;
        ss >> value;
        list.push_back(value);

    } else if (command == "POPFRONT") {
        list.pop_front();

    } else if (command == "PRINT") {
        list.print();

    } else if (command == "SAVEBIN") {
        string filename;
        ss >> filename;
        list.saveToBinaryFile(filename);

    } else if (command == "LOADBIN") {
        string filename;
        ss >> filename;
        list.loadFromBinaryFile(filename);
    }
}

int main() {
    SinglyLinkedList list;
    string commandLine;

    while (true) {
        getline(cin, commandLine);

        if (commandLine == "EXIT") {
            break; // выход из программы
        }

        processCommand(list, commandLine); // обработка команды
    }

    return 0;
}
