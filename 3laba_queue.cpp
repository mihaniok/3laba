#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Класс узла очереди
class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Класс очереди
class Queue {
private:
    Node* front;  // Указатель на голову очереди
    Node* rear;   // Указатель на хвост очереди

public:
    // Конструктор очереди
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
            cout << "Очередь пуста, нечего удалять!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;  // Если очередь стала пустой
        }
        delete temp;
    }

    // Вывод всех элементов очереди
    void print() const {
        if (front == nullptr) {
            cout << "Очередь пуста!" << endl;
            return;
        }
        Node* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Сериализация очереди в строку
    string serialize() const {
        stringstream ss;
        Node* temp = front;
        while (temp != nullptr) {
            ss << temp->data << " ";
            temp = temp->next;
        }
        return ss.str();
    }

    // Десериализация очереди из строки
    void deserialize(const string& data) {
        clear();  // Очистить текущую очередь
        stringstream ss(data);
        int value;
        while (ss >> value) {
            push(value);
        }
    }

    // Запись очереди в файл
    void saveToFile(const string &filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << serialize();
            outFile.close();
            cout << "Очередь сохранена в файл " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для записи!" << endl;
        }
    }

    // Загрузка очереди из файла
    void loadFromFile(const string &filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            string data((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
            deserialize(data);
            inFile.close();
            cout << "Очередь загружена из файла " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для чтения!" << endl;
        }
    }

    // Очистка очереди
    void clear() {
        while (front != nullptr) {
            pop();
        }
    }

    // Деструктор
    ~Queue() {
        clear();
    }
};

// Функция обработки команд
void processCommand(Queue &queue, const string &commandLine) {
    stringstream ss(commandLine);
    string command;
    ss >> command;

    if (command == "PUSH") {
        int value;
        ss >> value;
        queue.push(value);

    } else if (command == "POP") {
        queue.pop();

    } else if (command == "PRINT") {
        queue.print();

    } else if (command == "SAVE") {
        string filename;
        ss >> filename;
        queue.saveToFile(filename);

    } else if (command == "LOAD") {
        string filename;
        ss >> filename;
        queue.loadFromFile(filename);

    } else if (command == "SERIALIZE") {
        cout << "Сериализованные данные: " << queue.serialize() << endl;

    } else if (command == "DESERIALIZE") {
        string data;
        getline(ss, data);
        queue.deserialize(data);
        cout << "Очередь десериализована из строки." << endl;
    }
}

int main() {
    Queue queue;
    string commandLine;

    while (true) {
        getline(cin, commandLine);

        if (commandLine == "EXIT") {
            break;  // выход из программы
        }

        processCommand(queue, commandLine);  // обработка команды
    }

    return 0;
}
