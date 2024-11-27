package main

import (
	"bufio"
	"encoding/binary"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// Node представляет элемент очереди.
type Node struct {
	data int
	next *Node
}

// Queue представляет очередь с указателями на начало и конец.
type Queue struct {
	front *Node
	rear  *Node
}

// NewQueue создает новую пустую очередь.
func NewQueue() *Queue {
	return &Queue{front: nil, rear: nil}
}

// Push добавляет новый элемент в конец очереди.
func (q *Queue) Push(value int) {
	newNode := &Node{data: value, next: nil}
	if q.rear == nil {
		q.front = newNode
		q.rear = newNode
	} else {
		q.rear.next = newNode
		q.rear = newNode
	}
}

// Pop удаляет элемент из начала очереди.
func (q *Queue) Pop() {
	if q.front == nil {
		return
	}
	q.front = q.front.next
	if q.front == nil {
		q.rear = nil // Если очередь становится пустой
	}
}

// SaveToFileBinary сохраняет элементы очереди в бинарный файл.
func (q *Queue) SaveToFileBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return fmt.Errorf("ошибка создания бинарного файла: %v", err)
	}
	defer file.Close()

	current := q.front
	for current != nil {
		// Запись каждого числа в бинарном формате
		err := binary.Write(file, binary.LittleEndian, int32(current.data))
		if err != nil {
			return fmt.Errorf("ошибка записи в бинарный файл: %v", err)
		}
		current = current.next
	}
	return nil
}

// LoadFromFileBinary загружает элементы очереди из бинарного файла.
func (q *Queue) LoadFromFileBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return fmt.Errorf("ошибка открытия бинарного файла: %v", err)
	}
	defer file.Close()

	var value int32
	for {
		// Чтение данных в бинарном формате
		err := binary.Read(file, binary.LittleEndian, &value)
		if err != nil {
			break
		}
		q.Push(int(value))
	}
	return nil
}

// SaveToFileText сохраняет элементы очереди в текстовый файл.
func (q *Queue) SaveToFileText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return fmt.Errorf("ошибка создания текстового файла: %v", err)
	}
	defer file.Close()

	current := q.front
	for current != nil {
		// Запись каждого числа в текстовом формате
		_, err := file.WriteString(strconv.Itoa(current.data) + " ")
		if err != nil {
			return fmt.Errorf("ошибка записи в текстовый файл: %v", err)
		}
		current = current.next
	}
	return nil
}

// LoadFromFileText загружает элементы очереди из текстового файла.
func (q *Queue) LoadFromFileText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return fmt.Errorf("ошибка открытия текстового файла: %v", err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		values := strings.Fields(line)
		for _, value := range values {
			parsedValue, err := strconv.Atoi(value)
			if err == nil {
				q.Push(parsedValue)
			}
		}
	}
	if err := scanner.Err(); err != nil {
		return fmt.Errorf("ошибка чтения текстового файла: %v", err)
	}
	return nil
}

// Clear очищает очередь, удаляя все элементы.
func (q *Queue) Clear() {
	for q.front != nil {
		q.Pop()
	}
}
