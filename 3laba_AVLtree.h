#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <gtest/gtest.h>

using namespace std;

class AVLTree {
private:
    // Вложенный класс узла
    class Node {
    public:
        int key;
        Node* left;
        Node* right;
        int height;

        Node(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Вспомогательные функции
    int height(Node* node) const {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

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

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
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

    void saveTree(Node* root, ofstream& file) const {
        if (root) {
            file << root->key << " ";
            saveTree(root->left, file);
            saveTree(root->right, file);
        }
    }

    Node* loadTree(Node* root, ifstream& file) {
        int key;
        while (file >> key) {
            root = insert(root, key);
        }
        return root;
    }

    void printTree(Node* root) const {
        if (root == nullptr) return;

        printTree(root->left);
        cout << root->key << " ";
        printTree(root->right);
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            saveTree(root, file);
            file.close();
        } 
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            root = nullptr;
            root = loadTree(root, file);
            file.close();
        } 
    }

    void print() const {
        printTree(root);
        cout << endl;  // Добавим новую строку после вывода
    }

    ~AVLTree() {
        clear(root);
    }
};
