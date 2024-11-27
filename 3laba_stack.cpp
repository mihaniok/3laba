#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

// Класс для узла стека
class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Класс для стека
class Stack {
private:
    Node* top;  // Указатель на вершину стека

public:
    // Конструктор стека
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
            cout << "Стек пуст, нечего удалять!" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    // Вывод всех элементов стека
    void print() const {
        if (top == nullptr) {
            cout << "Стек пуст!" << endl;
            return;
        }
        Node* temp = top;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Сериализация стека в файл (запись в бинарном формате)
    void serialize(const string& filename) const {
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open()) {
            Node* temp = top;
            while (temp != nullptr) {
                outFile.write(reinterpret_cast<const char*>(&temp->data), sizeof(temp->data));
                temp = temp->next;
            }
            outFile.close();
            cout << "Стек сохранён в файл " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для записи!" << endl;
        }
    }

    // Десериализация стека из файла (чтение из бинарного формата)
    void deserialize(const string& filename) {
        ifstream inFile(filename, ios::binary);
        if (inFile.is_open()) {
            // Используем очередь для сохранения порядка элементов
            queue<int> tempQueue;
            int value;
            while (inFile.read(reinterpret_cast<char*>(&value), sizeof(value))) {
                tempQueue.push(value);  // Добавляем элементы в очередь
            }
            inFile.close();

            // Восстанавливаем стек в правильном порядке
            while (!tempQueue.empty()) {
                push(tempQueue.front());
                tempQueue.pop();
            }

            cout << "Стек загружен из файла " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для чтения!" << endl;
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

// Функция обработки команд
void processCommand(Stack& stack, const string& commandLine) {
    stringstream ss(commandLine);
    string command;
    ss >> command;

    if (command == "PUSH") {
        int value;
        ss >> value;
        stack.push(value);

    } else if (command == "POP") {
        stack.pop();

    } else if (command == "PRINT") {
        stack.print();

    } else if (command == "SAVE") {
        string filename;
        ss >> filename;
        stack.serialize(filename);

    } else if (command == "LOAD") {
        string filename;
        ss >> filename;
        stack.deserialize(filename);
    }
}

int main() {
    Stack stack;
    string commandLine;

    while (true) {
        getline(cin, commandLine);

        if (commandLine == "EXIT") {
            break;  // выход из программы
        }

        processCommand(stack, commandLine);  // обработка команды
    }

    return 0;
}
