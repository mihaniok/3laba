#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class AVLTree {
private:
    class Node {
    public:
        int key;
        Node* left;
        Node* right;
        int height;

        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Получение высоты узла
    int height(Node* node) {
        return node ? node->height : 0;
    }

    // Функция для получения максимума двух чисел
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // Получение разности высот дочерних узлов (балансировка)
    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    // Правый поворот
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    // Левый поворот
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    // Вставка узла в AVL-дерево
    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Удаление узла из AVL-дерева
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root) return root;

        root->height = max(height(root->left), height(root->right)) + 1;
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // Префиксный обход для сериализации дерева
    void saveTree(Node* root, ofstream& file) {
        if (root) {
            file << root->key << " ";
            saveTree(root->left, file);
            saveTree(root->right, file);
        }
    }

    // Десериализация дерева
    Node* loadTree(Node* root, ifstream& file) {
        int key;
        while (file >> key) {
            root = insert(root, key);
        }
        return root;
    }

    // Функция для визуализации дерева с отступами
    void printTree(Node* root, int space = 0, int height = 10) {
        if (root == nullptr) return;

        space += height;

        printTree(root->right, space);

        cout << endl;
        for (int i = height; i < space; i++)
            cout << ' ';
        cout << root->key << "\n";

        printTree(root->left, space);
    }

public:
    AVLTree() : root(nullptr) {}

    // Методы для вставки, удаления, печати и логирования
    void insert(int key) {
        root = insert(root, key);
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    void print() {
        printTree(root);
    }

    void save(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            saveTree(root, file);
            file.close();
        }
    }

    void load(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            root = nullptr;  // Очищаем текущее дерево перед загрузкой
            root = loadTree(root, file);
            file.close();
        }
    }
};

// Главная функция для пользовательского интерфейса
int main() {
    AVLTree tree;
    string command;

    while (true) {
        getline(cin, command);

        if (command.find("INSERT") == 0) {
            int key = stoi(command.substr(7));
            tree.insert(key);
        } else if (command.find("DELETE") == 0) {
            int key = stoi(command.substr(7));
            tree.deleteNode(key);
        } else if (command == "PRINT") {
            tree.print();
        } else if (command.find("SAVE") == 0) {
            string filename = command.substr(5);
            tree.save(filename);
        } else if (command.find("LOAD") == 0) {
            string filename = command.substr(5);
            tree.load(filename);
        } else if (command == "EXIT") {
            break;
        }
    }

    return 0;
}
