package main

import (
	"os"
	"testing"
)

// TestQueueOperations проверяет операции Push, Pop и Clear.
func TestQueueOperations(t *testing.T) {
	queue := NewQueue()

	// Тест Push
	queue.Push(10)
	queue.Push(20)
	queue.Push(30)

	if queue.front == nil || queue.front.data != 10 {
		t.Errorf("Ожидалось, что первый элемент будет 10, а получили %v", queue.front.data)
	}
	if queue.rear == nil || queue.rear.data != 30 {
		t.Errorf("Ожидалось, что последний элемент будет 30, а получили %v", queue.rear.data)
	}

	// Тест Pop
	queue.Pop()
	if queue.front == nil || queue.front.data != 20 {
		t.Errorf("Ожидалось, что первый элемент после Pop будет 20, а получили %v", queue.front.data)
	}

	// Тест Clear
	queue.Clear()
	if queue.front != nil {
		t.Errorf("Ожидалось, что очередь будет пустой после Clear, но она содержит элементы")
	}
}

// TestSaveAndLoadBinary проверяет сохранение и загрузку очереди из бинарного файла.
func TestSaveAndLoadBinary(t *testing.T) {
	queue := NewQueue()
	queue.Push(100)
	queue.Push(200)

	// Удаление файла для теста (если существует)
	err := os.Remove("test_queue_binary.dat")
	if err != nil && !os.IsNotExist(err) {
		t.Fatalf("Ошибка при удалении тестового файла: %v", err)
	}

	queue.SaveToFileBinary("test_queue_binary.dat")

	// Загрузка очереди из бинарного файла
	newQueue := NewQueue()
	newQueue.LoadFromFileBinary("test_queue_binary.dat")

	// Проверка корректности загрузки
	if newQueue.front == nil || newQueue.front.data != 100 {
		t.Errorf("Ожидалось, что первый элемент будет 100, а получили %v", newQueue.front.data)
	}
	if newQueue.rear == nil || newQueue.rear.data != 200 {
		t.Errorf("Ожидалось, что последний элемент будет 200, а получили %v", newQueue.rear.data)
	}

	// Очистка тестового файла
	err = os.Remove("test_queue_binary.dat")
	if err != nil {
		t.Errorf("Ошибка при удалении бинарного файла: %v", err)
	}
}

// TestSaveAndLoadText проверяет сохранение и загрузку очереди из текстового файла.
func TestSaveAndLoadText(t *testing.T) {
	queue := NewQueue()
	queue.Push(500)
	queue.Push(600)

	// Удаление файла для теста (если существует)
	err := os.Remove("test_queue_text.txt")
	if err != nil && !os.IsNotExist(err) {
		t.Fatalf("Ошибка при удалении тестового файла: %v", err)
	}

	queue.SaveToFileText("test_queue_text.txt")

	// Загрузка очереди из текстового файла
	newQueue := NewQueue()
	newQueue.LoadFromFileText("test_queue_text.txt")

	// Проверка корректности загрузки
	if newQueue.front == nil || newQueue.front.data != 500 {
		t.Errorf("Ожидалось, что первый элемент будет 500, а получили %v", newQueue.front.data)
	}
	if newQueue.rear == nil || newQueue.rear.data != 600 {
		t.Errorf("Ожидалось, что последний элемент будет 600, а получили %v", newQueue.rear.data)
	}

	// Очистка тестового файла
	err = os.Remove("test_queue_text.txt")
	if err != nil {
		t.Errorf("Ошибка при удалении текстового файла: %v", err)
	}
}

// TestPopEmptyQueue проверяет удаление элемента из пустой очереди.
func TestPopEmptyQueue(t *testing.T) {
	queue := NewQueue()
	queue.Pop() // Должно не вызывать ошибок, просто ничего не делать
	if queue.front != nil {
		t.Errorf("Ожидалось, что очередь будет пустой, но она содержит элементы")
	}
}

// TestSaveToFileBinaryError проверяет обработку ошибок при сохранении в бинарный файл.
func TestSaveToFileBinaryError(t *testing.T) {
	queue := NewQueue()
	queue.Push(10)

	// Симуляция ошибки создания файла (например, использование недопустимого пути)
	err := queue.SaveToFileBinary("/invalid/path/test_queue_binary.dat")
	if err == nil {
		t.Errorf("Ожидалась ошибка при сохранении в бинарный файл, но её не произошло")
	}
}

// TestLoadFromFileBinaryError проверяет обработку ошибок при загрузке из бинарного файла.
func TestLoadFromFileBinaryError(t *testing.T) {
	queue := NewQueue()

	// Симуляция ошибки открытия файла (например, файл не существует)
	queue.LoadFromFileBinary("non_existent_file.dat")

	if queue.front != nil {
		t.Errorf("Ожидалось, что очередь будет пустой, но она содержит элементы")
	}
}

// TestSaveToFileTextError проверяет обработку ошибок при сохранении в текстовый файл.
func TestSaveToFileTextError(t *testing.T) {
	queue := NewQueue()
	queue.Push(10)

	// Симуляция ошибки создания файла (например, использование недопустимого пути)
	err := queue.SaveToFileText("/invalid/path/test_queue_text.txt")
	if err == nil {
		t.Errorf("Ожидалась ошибка при сохранении в текстовый файл, но её не произошло")
	}
}

// TestLoadFromFileTextError проверяет обработку ошибок при загрузке из текстового файла.
func TestLoadFromFileTextError(t *testing.T) {
	queue := NewQueue()

	// Симуляция ошибки открытия файла (например, файл не существует)
	queue.LoadFromFileText("non_existent_file.txt")

	if queue.front != nil {
		t.Errorf("Ожидалось, что очередь будет пустой, но она содержит элементы")
	}
}
