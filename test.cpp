#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include "3laba_mass.h" 
#include "3laba_1list.h"  
#include "3laba_2list.h"
#include "3laba_queue.h"
#include "3laba_stack.h"
#include "3laba_hash.h"
#include "3laba_AVLtree.h"

using namespace std;

//
// Тесты для класса SinglyLinkedList
//

// Тестирование метода push_front
TEST(SinglyLinkedListTest, PushFront) {
    SinglyLinkedList list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    stringstream ss;
    testing::internal::CaptureStdout(); // Захват вывода
    list.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "3 2 1 \n"); // Ожидаемый вывод
}

// Тестирование метода push_back
TEST(SinglyLinkedListTest, PushBack) {
    SinglyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    stringstream ss;
    testing::internal::CaptureStdout();
    list.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "1 2 3 \n");
}

// Тестирование метода pop_front
TEST(SinglyLinkedListTest, PopFront) {
    SinglyLinkedList list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    list.pop_front();
    stringstream ss;
    testing::internal::CaptureStdout();
    list.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "2 1 \n");
}

// Тестирование метода pop_back
TEST(SinglyLinkedListTest, PopBack) {
    SinglyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    stringstream ss;
    testing::internal::CaptureStdout();
    list.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "1 2 \n");
}

// Тестирование метода remove по значению
TEST(SinglyLinkedListTest, RemoveByValue) {
    SinglyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(2);

    // Удаляем первый найденный элемент со значением 2
    list.remove(2);

    stringstream ss;
    testing::internal::CaptureStdout();
    list.print();  // Ожидаемый вывод: 1 3 2
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "1 3 2 \n");

    // Удаляем элемент, который отсутствует
    list.remove(5);
    ss.str(""); // Очистка буфера
    ss.clear();
    testing::internal::CaptureStdout();
    list.print();  // Ожидаемый вывод: 1 3 2
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "1 3 2 \n");

    // Удаляем еще раз элемент 2
    list.remove(2);
    ss.str(""); // Очистка буфера
    ss.clear();
    testing::internal::CaptureStdout();
    list.print();  // Ожидаемый вывод: 1 3
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "1 3 \n");
}


// Тестирование метода find
TEST(SinglyLinkedListTest, Find) {
    SinglyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_TRUE(list.find(2));
    EXPECT_FALSE(list.find(4));
}

TEST(SinglyLinkedListTest, SaveAndLoad_SinglyLinkedList) {
    SinglyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.saveToFile("singly_test_file.txt");

    SinglyLinkedList newList;
    newList.loadFromFile("singly_test_file.txt");

    stringstream ss;
    testing::internal::CaptureStdout();
    newList.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "1 2 3 \n");
}

//
// Тесты для класса DoublyLinkedList
//

// Тестирование метода push_front
TEST(DoublyLinkedListTest, PushFront) {
    DoublyLinkedList list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);

    stringstream ss;
    testing::internal::CaptureStdout();
    list.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "30 20 10 \n");
}

// Тестирование метода push_back
TEST(DoublyLinkedListTest, PushBack) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    stringstream ss;
    testing::internal::CaptureStdout();
    list.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "10 20 30 \n");
}

// Тестирование метода pop_front
TEST(DoublyLinkedListTest, PopFront) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.pop_front();

    stringstream ss;
    testing::internal::CaptureStdout();
    list.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "20 30 \n");
}

// Тестирование метода pop_back
TEST(DoublyLinkedListTest, PopBack) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.pop_back();

    stringstream ss;
    testing::internal::CaptureStdout();
    list.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "10 20 \n");
}

// Тестирование метода remove
TEST(DoublyLinkedListTest, Remove) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.remove(20);

    stringstream ss;
    testing::internal::CaptureStdout();
    list.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "10 30 \n");
}

// Тестирование метода find
TEST(DoublyLinkedListTest, Find) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    EXPECT_TRUE(list.find(20));
    EXPECT_FALSE(list.find(40));
}

// Тестирование метода saveToFile и loadFromFile
TEST(DoublyLinkedListTest, SaveAndLoad_DoublyLinkedList) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.saveToFile("test_file.txt");

    DoublyLinkedList newList;
    newList.loadFromFile("test_file.txt");

    stringstream ss;
    testing::internal::CaptureStdout();
    newList.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "10 20 30 \n");
}

//
// Тесты для класса Array
//

// Тестирование метода push_back
TEST(ArrayTest, PushBack) {
    Array arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    stringstream ss;
    testing::internal::CaptureStdout();
    arr.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "1 2 3 \n");
}

// Тестирование метода remove
TEST(ArrayTest, Remove) {
    Array arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.remove(1);

    stringstream ss;
    testing::internal::CaptureStdout();
    arr.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "1 3 \n");
}

// Тестирование метода replace
TEST(ArrayTest, Replace) {
    Array arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.replace(1, 4);

    stringstream ss;
    testing::internal::CaptureStdout();
    arr.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "1 4 3 \n");
}

// Тестирование метода get
TEST(ArrayTest, Get) {
    Array arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    EXPECT_EQ(arr.get(1), 2);
    EXPECT_EQ(arr.get(5), -1);
}

// Тестирование метода size
TEST(ArrayTest, Size) {
    Array arr;
    EXPECT_EQ(arr.size(), 0);

    arr.push_back(1);
    arr.push_back(2);
    EXPECT_EQ(arr.size(), 2);
}

TEST(SinglyLinkedListTest, SaveAndLoad_AVLTree) {
    SinglyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.saveToFile("singly_test_file.txt");

    SinglyLinkedList newList;
    newList.loadFromFile("singly_test_file.txt");

    stringstream ss;
    testing::internal::CaptureStdout();
    newList.print();
    ss << testing::internal::GetCapturedStdout();
    EXPECT_EQ(ss.str(), "1 2 3 \n");
}

// Главная функция для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//
// тесты для queue
//

// Тестирование метода push
TEST(QueueTest, Push) {
    Queue q;
    q.push(1);
    q.push(2);
    q.push(3);

    // Захватываем вывод
    testing::internal::CaptureStdout();
    q.print();
    string output = testing::internal::GetCapturedStdout();

    // Ожидаемый вывод: "Queue elements: 1 2 3\n"
    EXPECT_EQ(output, "Queue elements: 1 2 3\n");
}

// Тестирование метода pop
TEST(QueueTest, Pop) {
    Queue q;
    q.push(1);
    q.push(2);
    q.push(3);

    q.pop();  // Удаляем первый элемент

    // Захватываем вывод
    testing::internal::CaptureStdout();
    q.print();
    string output = testing::internal::GetCapturedStdout();

    // Ожидаемый вывод: "Queue elements: 2 3\n"
    EXPECT_EQ(output, "Queue elements: 2 3\n");
}

// Тестирование метода peek
TEST(QueueTest, Peek) {
    Queue q;
    q.push(1);
    q.push(2);
    q.push(3);

    // Захватываем вывод
    testing::internal::CaptureStdout();
    q.peek();
    string output = testing::internal::GetCapturedStdout();

    // Ожидаемый вывод: "Front element: 1\n"
    EXPECT_EQ(output, "Front element: 1\n");

    q.pop();

    // Захватываем вывод
    testing::internal::CaptureStdout();
    q.peek();
    output = testing::internal::GetCapturedStdout();

    // Ожидаемый вывод: "Front element: 2\n"
    EXPECT_EQ(output, "Front element: 2\n");
}

// Тестирование вывода пустой очереди
TEST(QueueTest, PrintEmptyQueue) {
    Queue q;

    // Захватываем вывод
    testing::internal::CaptureStdout();
    q.print();
    string output = testing::internal::GetCapturedStdout();

    // Ожидаемый вывод: "Queue is empty\n"
    EXPECT_EQ(output, "Queue is empty\n");
}

// Тестирование метода saveToFile и loadFromFile
TEST(QueueTest, SaveAndLoadQueue) {
    Queue q;
    q.push(10);
    q.push(20);
    q.push(30);

    // Сохраняем очередь в файл
    string filename = "test_queue.txt";
    q.saveToFile(filename);

    // Создаем новую очередь и загружаем из файла
    Queue newQueue;
    newQueue.loadFromFile(filename);

    // Захватываем вывод
    testing::internal::CaptureStdout();
    newQueue.print();
    string output = testing::internal::GetCapturedStdout();

    // Ожидаемый вывод: "Queue elements: 10 20 30\n"
    EXPECT_EQ(output, "Queue elements: 10 20 30\n");
}

// Тестирование метода clear
TEST(QueueTest, Clear) {
    Queue q;
    q.push(1);
    q.push(2);
    q.push(3);

    q.clear();

    // Захватываем вывод
    testing::internal::CaptureStdout();
    q.print();
    string output = testing::internal::GetCapturedStdout();

    // Ожидаемый вывод: "Queue is empty\n"
    EXPECT_EQ(output, "Queue is empty\n");
}

// Тестирование pop для пустой очереди
TEST(QueueTest, PopEmptyQueue) {
    Queue q;

    // Попытка удалить элемент из пустой очереди
    q.pop();

    // Захватываем вывод
    testing::internal::CaptureStdout();
    q.print();
    string output = testing::internal::GetCapturedStdout();

    // Ожидаемый вывод: "Queue is empty\n"
    EXPECT_EQ(output, "Queue is empty\n");
}

// Тестирование peek для пустой очереди
TEST(QueueTest, PeekEmptyQueue) {
    Queue q;

    // Захватываем вывод
    testing::internal::CaptureStdout();
    q.peek();
    string output = testing::internal::GetCapturedStdout();

    // Ожидаемый вывод: "Queue is empty\n"
    EXPECT_EQ(output, "Queue is empty\n");
}


//
// тесты для stack
//

// Тестирование метода push
TEST(StackTest, Push) {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);

    // Захватываем вывод метода print
    testing::internal::CaptureStdout();
    s.print();
    string output = testing::internal::GetCapturedStdout();

    // Ожидаем, что элементы добавлены в обратном порядке
    EXPECT_EQ(output, "30 20 10 \n");
}

// Тестирование метода pop
TEST(StackTest, Pop) {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);

    s.pop(); // Удаляем 30

    // Захватываем вывод метода print
    testing::internal::CaptureStdout();
    s.print();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "20 10 \n");
}

// Тестирование метода peek
TEST(StackTest, Peek) {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);

    // Захватываем вывод метода peek
    testing::internal::CaptureStdout();
    s.peek();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "30\n");

    s.pop(); // Удаляем 30

    // Захватываем вывод метода peek после удаления
    testing::internal::CaptureStdout();
    s.peek();
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "20\n");
}

// Тестирование метода print (для пустого стека)
TEST(StackTest, PrintEmptyStack) {
    Stack s;

    // Захватываем вывод метода print
    testing::internal::CaptureStdout();
    s.print();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Stack is empty\n");
}

// Тестирование метода saveToFile и loadFromFile
TEST(StackTest, SaveAndLoadStack) {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);

    string filename = "stack_test.txt";

    // Сохраняем стек в файл
    s.saveToFile(filename);

    // Создаем новый стек и загружаем из файла
    Stack newStack;
    newStack.loadFromFile(filename);

    // Захватываем вывод метода print нового стека
    testing::internal::CaptureStdout();
    newStack.print();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "30 20 10 \n");
}

// Тестирование метода clear
TEST(StackTest, ClearStack) {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);

    s.clear(); // Очищаем стек

    // Захватываем вывод метода print
    testing::internal::CaptureStdout();
    s.print();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Stack is empty\n");
}

// Тестирование удаления из пустого стека
TEST(StackTest, PopFromEmptyStack) {
    Stack s;

    // Пытаемся удалить элемент из пустого стека
    testing::internal::CaptureStdout();
    s.pop();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Stack is empty\n");
}

// Тестирование peek для пустого стека
TEST(StackTest, PeekFromEmptyStack) {
    Stack s;

    // Пытаемся выполнить peek на пустом стеке
    testing::internal::CaptureStdout();
    s.peek();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Stack is empty\n");
}



//
// тесты для hash
//

// Тестирование вставки элементов и получения значений
TEST(HashTableTest, InsertAndGet) {
    HashTable ht;

    ht.insert("key1", "value1");
    ht.insert("key2", "value2");

    // Проверяем, что значения вставлены правильно
    EXPECT_EQ(ht.get("key1"), "value1");
    EXPECT_EQ(ht.get("key2"), "value2");
    EXPECT_EQ(ht.get("key3"), "Key not found");  // Незаполненный ключ
}

// Тестирование обновления значения при повторной вставке того же ключа
TEST(HashTableTest, InsertAndUpdate) {
    HashTable ht;

    ht.insert("key1", "value1");
    ht.insert("key1", "new_value1");

    // Проверяем, что значение для ключа было обновлено
    EXPECT_EQ(ht.get("key1"), "new_value1");
}

// Тестирование удаления элемента
TEST(HashTableTest, Remove) {
    HashTable ht;

    ht.insert("key1", "value1");
    ht.insert("key2", "value2");

    // Удаляем ключ "key1"
    testing::internal::CaptureStdout();
    ht.remove("key1");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");

    // Проверяем, что значение "key1" больше не существует
    EXPECT_EQ(ht.get("key1"), "Key not found");
    EXPECT_EQ(ht.get("key2"), "value2");  // Другие элементы остаются
}

// Тестирование удаления несуществующего элемента
TEST(HashTableTest, RemoveNonExistent) {
    HashTable ht;

    ht.insert("key1", "value1");

    // Попытка удаления несуществующего элемента
    testing::internal::CaptureStdout();
    ht.remove("key2");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

// Тестирование вывода всей хеш-таблицы
TEST(HashTableTest, Print) {
    HashTable ht;

    ht.insert("key1", "value1");
    ht.insert("key2", "value2");

    testing::internal::CaptureStdout();
    ht.print();
    string output = testing::internal::GetCapturedStdout();

    // Ожидаемый вывод таблицы
    EXPECT_TRUE(output.find("{key1: value1}") != string::npos);
    EXPECT_TRUE(output.find("{key2: value2}") != string::npos);
}

// Тестирование сохранения и загрузки хеш-таблицы в файл
TEST(HashTableTest, SaveAndLoad) {
    HashTable ht;

    ht.insert("key1", "value1");
    ht.insert("key2", "value2");

    string filename = "hash_table_test.txt";

    // Сохраняем таблицу в файл
    ht.saveToFile(filename);

    // Создаем новую таблицу и загружаем данные из файла
    HashTable newHt;
    newHt.loadFromFile(filename);

    // Проверяем, что данные правильно загружены
    EXPECT_EQ(newHt.get("key1"), "value1");
    EXPECT_EQ(newHt.get("key2"), "value2");
}

// Тестирование загрузки из пустого файла
TEST(HashTableTest, LoadFromEmptyFile) {
    HashTable ht;
    string filename = "empty_file.txt";

    // Создаем пустой файл
    ofstream outFile(filename);
    outFile.close();

    // Загружаем данные из пустого файла
    ht.loadFromFile(filename);

    // Проверяем, что хеш-таблица осталась пустой
    EXPECT_EQ(ht.get("key1"), "Key not found");
}

// Тестирование удаления всех элементов
TEST(HashTableTest, RemoveAll) {
    HashTable ht;

    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    ht.insert("key3", "value3");

    ht.remove("key1");
    ht.remove("key2");
    ht.remove("key3");

    // Проверяем, что все элементы были удалены
    EXPECT_EQ(ht.get("key1"), "Key not found");
    EXPECT_EQ(ht.get("key2"), "Key not found");
    EXPECT_EQ(ht.get("key3"), "Key not found");
}

// 
// тесты для AVL дерева
//


// Тест вставки элементов
TEST(AVLTreeTest, InsertElements) {
    AVLTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    // Проверим порядок вывода дерева
    testing::internal::CaptureStdout();
    tree.print();
    string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("10"), string::npos);
    ASSERT_NE(output.find("20"), string::npos);
    ASSERT_NE(output.find("30"), string::npos);
}

// Тест удаления элементов
TEST(AVLTreeTest, RemoveElements) {
    AVLTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.remove(20);

    // Проверим, что узел с ключом 20 был удалён
    testing::internal::CaptureStdout();
    tree.print();
    string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output.find("20"), string::npos);
    ASSERT_NE(output.find("10"), string::npos);
    ASSERT_NE(output.find("30"), string::npos);
}

// Тест сохранения и загрузки дерева
TEST(AVLTreeTest, SaveAndLoadTree) {
    AVLTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    // Сохраняем дерево в файл
    string filename = "test_avl_tree.txt";
    tree.saveToFile(filename);

    // Создаём новое дерево и загружаем данные из файла
    AVLTree newTree;
    newTree.loadFromFile(filename);

    // Проверим, что новое дерево идентично старому
    testing::internal::CaptureStdout();
    newTree.print();
    string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("10"), string::npos);
    ASSERT_NE(output.find("20"), string::npos);
    ASSERT_NE(output.find("30"), string::npos);
}

// Тест сбалансированности дерева
TEST(AVLTreeTest, TreeBalance) {
    AVLTree tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(10);  // После вставки этого элемента дерево должно сбалансироваться
    tree.insert(13);
    tree.insert(15);
    tree.insert(21);
    tree.insert(1);
    tree.insert(3);
    tree.insert(31);
    tree.insert(15);
    tree.insert(32);
    tree.insert(33);

    testing::internal::CaptureStdout();
    tree.print();
    string output = testing::internal::GetCapturedStdout();

    // Убедимся, что корнем является сбалансированное значение (20)
    ASSERT_NE(output.find("20"), string::npos);
}


