#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

// Узел двусвязного списка
class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

// Двусвязный список
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            pop_front();
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!newNode) {
            cout << "Memory allocation failed for new node" << endl;
            return;
        }
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!newNode) {
            cout << "Memory allocation failed for new node" << endl;
            return;
        }
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

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

    bool find(int value) const {
        Node* temp = head;
        while (temp) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }

    void print() const {
        if (!head) { // Проверка на пустой список
            cout << "List is empty" << endl;
            return;
        }
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void serialize(const string& filename) const {
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open()) {
            Node* temp = head;
            while (temp) {
                outFile.write(reinterpret_cast<const char*>(&temp->data), sizeof(temp->data));
                temp = temp->next;
            }
            outFile.close();
            cout << "List saved to file: " << filename << endl;
        } else {
            cout << "Cannot open file for serialization" << endl;
        }
    }

    void deserialize(const string& filename) {
        ifstream inFile(filename, ios::binary);
        if (inFile.is_open()) {
            int value;
            while (inFile.read(reinterpret_cast<char*>(&value), sizeof(value))) {
                push_back(value);
            }
            inFile.close();
            cout << "List loaded from file: " << filename << endl;
        } else {
            cout << "Cannot open file for deserialization" << endl;
        }
    }
};

// Функция обработки команд
void processCommand(DoublyLinkedList& list, const string& commandLine) {
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

    } else if (command == "POPBACK") {
        list.pop_back();

    } else if (command == "REMOVE") {
        int value;
        ss >> value;
        list.remove(value);

    } else if (command == "FIND") {
        int value;
        ss >> value;
        cout << (list.find(value) ? "Found" : "Not Found") << endl;

    } else if (command == "PRINT") {
        list.print();

    } else if (command == "SAVE") {
        string filename;
        ss >> filename;
        list.serialize(filename);

    } else if (command == "LOAD") {
        string filename;
        ss >> filename;
        list.deserialize(filename);
    }
}

int main() {
    DoublyLinkedList list;
    string commandLine;

    while (true) {
        getline(cin, commandLine);

        if (commandLine == "EXIT") {
            break;
        }

        processCommand(list, commandLine);
    }

    return 0;
}
