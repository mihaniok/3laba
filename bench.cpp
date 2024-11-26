#include <iostream>
#include <fstream>
#include <iomanip>
#include <benchmark/benchmark.h>
#include "3laba_mass.h"
#include "3laba_1list.h"
#include "3laba_2list.h"
#include "3laba_queue.h"
#include "3laba_stack.h"
#include "3laba_hash.h"
#include "3laba_AVLtree.h"

using namespace std;

//
// array
//

// Бенчмарк для метода push_back
static void BM_Array_PushBack(benchmark::State& state) {
    Array arr;  // Инициализация массива
    for (auto _ : state) {
        arr.push_back(10);  // Добавляем элемент в конец массива
    }
}
BENCHMARK(BM_Array_PushBack);

// Бенчмарк для метода remove
static void BM_Array_Remove(benchmark::State& state) {
    Array arr;
    // Заполняем массив, чтобы было что удалять
    for (int i = 0; i < 1000; ++i) {
        arr.push_back(i);
    }

    for (auto _ : state) {
        arr.remove(0);  // Удаляем первый элемент
    }
}
BENCHMARK(BM_Array_Remove);

// Бенчмарк для метода replace
static void BM_Array_Replace(benchmark::State& state) {
    Array arr;
    // Заполняем массив для теста
    for (int i = 0; i < 1000; ++i) {
        arr.push_back(i);
    }

    for (auto _ : state) {
        arr.replace(500, 999);  // Заменяем элемент в середине
    }
}
BENCHMARK(BM_Array_Replace);

// Бенчмарк для метода get
static void BM_Array_Get(benchmark::State& state) {
    Array arr;
    // Заполняем массив для теста
    for (int i = 0; i < 1000; ++i) {
        arr.push_back(i);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(arr.get(500));  // Доступ к элементу в середине
    }
}
BENCHMARK(BM_Array_Get);

// Бенчмарк для метода saveToFile
static void BM_Array_SaveToFile(benchmark::State& state) {
    Array arr;
    // Заполняем массив
    for (int i = 0; i < 1000; ++i) {
        arr.push_back(i);
    }

    for (auto _ : state) {
        arr.saveToFile("array_output.txt");  // Записываем массив в файл
    }
}
BENCHMARK(BM_Array_SaveToFile);

// Бенчмарк для метода loadFromFile
static void BM_Array_LoadFromFile(benchmark::State& state) {
    Array arr;
    arr.saveToFile("array_output.txt");  // Сначала создаём файл для теста

    for (auto _ : state) {
        arr.loadFromFile("array_output.txt");  // Читаем массив из файла
    }
}
BENCHMARK(BM_Array_LoadFromFile);

//
// 1list
//

// Бенчмарк для добавления в голову
static void BM_SinglyList_PushFront(benchmark::State& state) {
    SinglyLinkedList list;
    for (auto _ : state) {
        list.push_front(state.range(0));
    }
}
BENCHMARK(BM_SinglyList_PushFront)->Arg(10);

// Бенчмарк для добавления в хвост
static void BM_SinglyList_PushBack(benchmark::State& state) {
    SinglyLinkedList list;
    for (auto _ : state) {
        list.push_back(state.range(0));
    }
}
BENCHMARK(BM_SinglyList_PushBack)->Arg(10);

// Бенчмарк для удаления с головы
static void BM_SinglyList_PopFront(benchmark::State& state) {
    SinglyLinkedList list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i);
    }
    for (auto _ : state) {
        list.pop_front();
    }
}
BENCHMARK(BM_SinglyList_PopFront)->Arg(1000);

// Бенчмарк для удаления с хвоста
static void BM_SinglyList_PopBack(benchmark::State& state) {
    SinglyLinkedList list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i);
    }
    for (auto _ : state) {
        list.pop_back();
    }
}
BENCHMARK(BM_SinglyList_PopBack)->Arg(1000);

// Бенчмарк для поиска элемента
static void BM_SinglyList_Find(benchmark::State& state) {
    SinglyLinkedList list;
    for (int i = 0; i < 1000; ++i) {
        list.push_back(i);
    }
    for (auto _ : state) {
        list.find(500); // Ищем элемент
    }
}
BENCHMARK(BM_SinglyList_Find);

// Бенчмарк для записи в файл
static void BM_SinglyList_SaveToFile(benchmark::State& state) {
    SinglyLinkedList list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i);
    }
    for (auto _ : state) {
        list.saveToFile("benchmark_list.txt");
    }
}
BENCHMARK(BM_SinglyList_SaveToFile)->Arg(1000);

// Бенчмарк для загрузки из файла
static void BM_SinglyList_LoadFromFile(benchmark::State& state) {
    SinglyLinkedList list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i);
    }
    list.saveToFile("benchmark_list.txt");

    SinglyLinkedList loadedList;
    for (auto _ : state) {
        loadedList.loadFromFile("benchmark_list.txt");
    }
}
BENCHMARK(BM_SinglyList_LoadFromFile)->Arg(1000);

//
// 2list
//

// Бенчмарк для добавления в начало
static void BM_DoublyList_PushFront(benchmark::State& state) {
    DoublyLinkedList list;
    for (auto _ : state) {
        list.push_front(state.range(0));
    }
}
BENCHMARK(BM_DoublyList_PushFront)->Arg(10);

// Бенчмарк для добавления в конец
static void BM_DoublyList_PushBack(benchmark::State& state) {
    DoublyLinkedList list;
    for (auto _ : state) {
        list.push_back(state.range(0));
    }
}
BENCHMARK(BM_DoublyList_PushBack)->Arg(10);

// Бенчмарк для удаления с начала
static void BM_DoublyList_PopFront(benchmark::State& state) {
    DoublyLinkedList list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i);
    }
    for (auto _ : state) {
        list.pop_front();
    }
}
BENCHMARK(BM_DoublyList_PopFront)->Arg(1000);

// Бенчмарк для удаления с конца
static void BM_DoublyList_PopBack(benchmark::State& state) {
    DoublyLinkedList list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i);
    }
    for (auto _ : state) {
        list.pop_back();
    }
}
BENCHMARK(BM_DoublyList_PopBack)->Arg(1000);

// Бенчмарк для поиска элемента
static void BM_DoublyList_Find(benchmark::State& state) {
    DoublyLinkedList list;
    for (int i = 0; i < 1000; ++i) {
        list.push_back(i);
    }
    for (auto _ : state) {
        list.find(500); // Ищем элемент
    }
}
BENCHMARK(BM_DoublyList_Find);

// Бенчмарк для записи в файл
static void BM_DoublyList_SaveToFile(benchmark::State& state) {
    DoublyLinkedList list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i);
    }
    for (auto _ : state) {
        list.saveToFile("benchmark_doubly_list.txt");
    }
}
BENCHMARK(BM_DoublyList_SaveToFile)->Arg(1000);

// Бенчмарк для загрузки из файла
static void BM_DoublyList_LoadFromFile(benchmark::State& state) {
    DoublyLinkedList list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i);
    }
    list.saveToFile("benchmark_doubly_list.txt");

    DoublyLinkedList loadedList;
    for (auto _ : state) {
        loadedList.loadFromFile("benchmark_doubly_list.txt");
    }
}
BENCHMARK(BM_DoublyList_LoadFromFile)->Arg(1000);

//
// queue
//

// Бенчмарк для добавления в очередь
static void BM_QueueAdd(benchmark::State& state) {
    Queue queue;
    for (auto _ : state) {
        queue.push(state.range(0));
    }
}
BENCHMARK(BM_QueueAdd)->Arg(10);

// Бенчмарк для удаления из очереди
static void BM_QueueRemove(benchmark::State& state) {
    Queue queue;
    for (int i = 0; i < state.range(0); ++i) {
        queue.push(i);
    }
    for (auto _ : state) {
        queue.pop();
    }
}
BENCHMARK(BM_QueueRemove)->Arg(1000);

// Бенчмарк для просмотра элемента на голове
static void BM_QueueFront(benchmark::State& state) {
    Queue queue;
    for (int i = 0; i < 1000; ++i) {
        queue.push(i);
    }
    for (auto _ : state) {
        queue.peek();
    }
}
BENCHMARK(BM_QueueFront);

// Бенчмарк для записи очереди в файл
static void BM_QueueWriteToFile(benchmark::State& state) {
    Queue queue;
    for (int i = 0; i < state.range(0); ++i) {
        queue.push(i);
    }
    for (auto _ : state) {
        queue.saveToFile("benchmark_queue.txt");
    }
}
BENCHMARK(BM_QueueWriteToFile)->Arg(1000);

// Бенчмарк для загрузки очереди из файла
static void BM_QueueReadFromFile(benchmark::State& state) {
    Queue queue;
    for (int i = 0; i < state.range(0); ++i) {
        queue.push(i);
    }
    queue.saveToFile("benchmark_queue.txt");

    Queue loadedQueue;
    for (auto _ : state) {
        loadedQueue.loadFromFile("benchmark_queue.txt");
    }
}
BENCHMARK(BM_QueueReadFromFile)->Arg(1000);

//
// Stack
//

// Бенчмарк для метода push
static void BM_StackInsert(benchmark::State& state) {
    Stack stack;
    for (auto _ : state) {
        stack.push(state.range(0));
    }
}
BENCHMARK(BM_StackInsert)->Arg(10);

// Бенчмарк для метода pop
static void BM_StackRemove(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < state.range(0); ++i) {
        stack.push(i);
    }
    for (auto _ : state) {
        stack.pop();
    }
}
BENCHMARK(BM_StackRemove)->Arg(1000);

// Бенчмарк для метода peek
static void BM_StackTop(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < 1000; ++i) {
        stack.push(i);
    }
    for (auto _ : state) {
        stack.peek();
    }
}
BENCHMARK(BM_StackTop);

// Бенчмарк для метода print
static void BM_StackDisplay(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < state.range(0); ++i) {
        stack.push(i);
    }
    for (auto _ : state) {
        stack.print();
    }
}
BENCHMARK(BM_StackDisplay)->Arg(1000);

// Бенчмарк для записи стека в файл
static void BM_StackWriteToFile(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < state.range(0); ++i) {
        stack.push(i);
    }
    for (auto _ : state) {
        stack.saveToFile("benchmark_stack.txt");
    }
}
BENCHMARK(BM_StackWriteToFile)->Arg(1000);

// Бенчмарк для загрузки стека из файла
static void BM_StackLoadFromFile(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < state.range(0); ++i) {
        stack.push(i);
    }
    stack.saveToFile("benchmark_stack.txt");

    Stack loadedStack;
    for (auto _ : state) {
        loadedStack.loadFromFile("benchmark_stack.txt");
    }
}
BENCHMARK(BM_StackLoadFromFile)->Arg(1000);

//
// Benchmark для класса Stack
//

// Бенчмарк для метода push
static void BM_StackAdd(benchmark::State& state) {
    Stack stack;
    for (auto _ : state) {
        stack.push(state.range(0));
    }
}
BENCHMARK(BM_StackAdd)->Arg(10);

// Бенчмарк для метода pop
static void BM_StackPopOut(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < state.range(0); ++i) {
        stack.push(i);
    }
    for (auto _ : state) {
        stack.pop();
    }
}
BENCHMARK(BM_StackPopOut)->Arg(1000);

// Бенчмарк для метода peek
static void BM_StackView(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < 1000; ++i) {
        stack.push(i);
    }
    for (auto _ : state) {
        stack.peek();
    }
}
BENCHMARK(BM_StackView);

// Бенчмарк для метода print
static void BM_StackShow(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < state.range(0); ++i) {
        stack.push(i);
    }
    for (auto _ : state) {
        stack.print();
    }
}
BENCHMARK(BM_StackShow)->Arg(1000);

// Бенчмарк для записи стека в файл
static void BM_StackExportToFile(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < state.range(0); ++i) {
        stack.push(i);
    }
    for (auto _ : state) {
        stack.saveToFile("benchmark_stack.txt");
    }
}
BENCHMARK(BM_StackExportToFile)->Arg(1000);

// Бенчмарк для загрузки стека из файла
static void BM_StackImportFromFile(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < state.range(0); ++i) {
        stack.push(i);
    }
    stack.saveToFile("benchmark_stack.txt");

    Stack loadedStack;
    for (auto _ : state) {
        loadedStack.loadFromFile("benchmark_stack.txt");
    }
}
BENCHMARK(BM_StackImportFromFile)->Arg(1000);

//
// hash
//

// Бенчмарк для вставки элементов
static void BM_HashTableInsert(benchmark::State& state) {
    HashTable hashTable;
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            hashTable.insert("key" + to_string(i), "value" + to_string(i));
        }
    }
}
BENCHMARK(BM_HashTableInsert)->Arg(1000);

// Бенчмарк для получения значения по ключу
static void BM_HashTableGet(benchmark::State& state) {
    HashTable hashTable;
    for (int i = 0; i < 1000; ++i) {
        hashTable.insert("key" + to_string(i), "value" + to_string(i));
    }
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            hashTable.get("key" + to_string(i));
        }
    }
}
BENCHMARK(BM_HashTableGet)->Arg(1000);

// Бенчмарк для удаления элементов
static void BM_HashTableRemove(benchmark::State& state) {
    HashTable hashTable;
    for (int i = 0; i < 1000; ++i) {
        hashTable.insert("key" + to_string(i), "value" + to_string(i));
    }
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            hashTable.remove("key" + to_string(i));
        }
    }
}
BENCHMARK(BM_HashTableRemove)->Arg(1000);

// Бенчмарк для сохранения хеш-таблицы в файл
static void BM_HashTableSaveToFile(benchmark::State& state) {
    HashTable hashTable;
    for (int i = 0; i < 1000; ++i) {
        hashTable.insert("key" + to_string(i), "value" + to_string(i));
    }
    for (auto _ : state) {
        hashTable.saveToFile("benchmark_hash_table.txt");
    }
}
BENCHMARK(BM_HashTableSaveToFile)->Arg(1000);

// Бенчмарк для загрузки хеш-таблицы из файла
static void BM_HashTableLoadFromFile(benchmark::State& state) {
    HashTable hashTable;
    for (int i = 0; i < 1000; ++i) {
        hashTable.insert("key" + to_string(i), "value" + to_string(i));
    }
    hashTable.saveToFile("benchmark_hash_table.txt");

    for (auto _ : state) {
        HashTable loadedHashTable;
        loadedHashTable.loadFromFile("benchmark_hash_table.txt");
    }
}
BENCHMARK(BM_HashTableLoadFromFile)->Arg(1000);

//
// AVLtree
//

// Бенчмарк для вставки элементов в AVL-дерево
static void BM_AVLTreeInsert(benchmark::State& state) {
    AVLTree avlTree;
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            avlTree.insert(i);
        }
    }
}
BENCHMARK(BM_AVLTreeInsert)->Arg(1000);

// Бенчмарк для удаления элементов из AVL-дерева
static void BM_AVLTreeRemove(benchmark::State& state) {
    AVLTree avlTree;
    for (int i = 0; i < 1000; ++i) {
        avlTree.insert(i);
    }
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            avlTree.remove(i);
        }
    }
}
BENCHMARK(BM_AVLTreeRemove)->Arg(1000);

// Бенчмарк для сохранения дерева в файл
static void BM_AVLTreeSaveToFile(benchmark::State& state) {
    AVLTree avlTree;
    for (int i = 0; i < 1000; ++i) {
        avlTree.insert(i);
    }
    for (auto _ : state) {
        avlTree.saveToFile("avltree_benchmark.txt");
    }
}
BENCHMARK(BM_AVLTreeSaveToFile)->Arg(1000);

// Бенчмарк для загрузки дерева из файла
static void BM_AVLTreeLoadFromFile(benchmark::State& state) {
    AVLTree avlTree;
    for (int i = 0; i < 1000; ++i) {
        avlTree.insert(i);
    }
    avlTree.saveToFile("avltree_benchmark.txt");

    for (auto _ : state) {
        AVLTree loadedTree;
        loadedTree.loadFromFile("avltree_benchmark.txt");
    }
}
BENCHMARK(BM_AVLTreeLoadFromFile)->Arg(1000);

// Бенчмарк для вывода дерева
static void BM_AVLTreePrint(benchmark::State& state) {
    AVLTree avlTree;
    for (int i = 0; i < 1000; ++i) {
        avlTree.insert(i);
    }
    for (auto _ : state) {
        avlTree.print();
    }
}
BENCHMARK(BM_AVLTreePrint)->Arg(1000);

// Запуск Google Benchmark
BENCHMARK_MAIN();
