#pragma once
#ifndef _STACK_H
#define _STACK_H
#include <iostream>

template <typename T> class Stack {
	friend class StackTest;
private:
	T* data;
	int maxSize;
	int top_;

	void resize(int step = 10);
public:
	Stack(int size = 10);
	Stack(const Stack<T>& stack);
	~Stack();
	void pop();
	T top() const;
	void push(const T& element);
	bool isEmpty() const;
	bool isFull() const;
	const Stack<T>& operator=(const Stack<T>& stack);
	bool operator==(const Stack<T>& stack) const;
};

template <typename T> Stack<T>::Stack(int size) {
	if (size <= 0) throw "maxSize must be bigger than 0";
	maxSize = size;
	top_ = -1;
	data = new T[maxSize];
}

template <typename T> Stack<T>::Stack(const Stack<T>& stack) {
	maxSize = stack.maxSize;
	top_ = stack.top_;
	data = new T[maxSize];
	for (int i = 0; i <= top_; i++) {
		data[i] = stack.data[i];
	}
}

template <typename T> Stack<T>::~Stack() {
	if (data != NULL) {
		delete[] data;
		top_ = -1;
		maxSize = 0;
	}
}

template <typename T> void Stack<T>::resize(int step) {
	if (step <= 0) { throw "Step<0 or step=0"; }
	int newSize = maxSize + step;
	T* newData = new T[newSize];
	for (int i = 0; i < maxSize; ++i) {
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	maxSize = newSize;
}

template <typename T> bool Stack<T>::isFull() const {
	return (top_ == maxSize - 1);
}

template <typename T> bool Stack<T>::isEmpty() const {
	return (top_ == -1);
}

template <typename T> T Stack<T>::top() const {
	if (isEmpty()) throw "Stack is empty";
	return data[top_];
}

template <typename T> void Stack<T>::push(const T& element) {
	if (isFull()) { resize(5); }
	data[++top_] = element;
}

template <typename T> void Stack<T>::pop() {
	if (isEmpty()) throw "Stack is empty!";
	top_--;
}

template <typename T> const Stack<T>& Stack<T>::operator=(const Stack<T>& stack) {
	if (this != &stack) {
		delete[] data;
		maxSize = stack.maxSize;
		top_ = stack.top_;
		data = new T[maxSize];
		for (int i = 0; i <= top_; ++i) {
			data[i] = stack.data[i];
		}
	}
	return *this;
}

template <typename T> bool Stack<T>::operator==(const Stack<T>& stack) const {
	if (top_ != stack.top_) {
		return false;
	}

	for (int i = 0; i < top_; ++i) {
		if (data[i] != stack.data[i]) {
			return false;
		}
	}

	return true;
}
#endif // !_STACK_H
