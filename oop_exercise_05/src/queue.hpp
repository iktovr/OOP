#pragma once

#include <memory>
#include <stdexcept>

template <class T>
class Queue {
private:
	class Node {
	public:
		std::unique_ptr<T> data;
		std::shared_ptr<Node> next;
		std::weak_ptr<Node> prev;

		Node(const T& value) : data(new T(value)), next(), prev() {}
	};

public:
	class Forward_iterator {
	private:
		std::shared_ptr<Node> ptr;
	
	public:
		using iterator_category = std::forward_iterator_tag;
			using value_type = T;
			using difference_type = size_t;
			using pointer = T*;
			using reference = T&;
		T& operator*() {
			return *(ptr->data);
		}
		Forward_iterator& operator++() {
			if (ptr == nullptr) {
				throw std::runtime_error("Error: Out of bounds");
			}
			ptr = ptr->next;
			return *this;
		}
		bool operator!=(const Forward_iterator& other) {
			return ptr != other.ptr;
		}
		bool operator==(const Forward_iterator& other) {
			return ptr == other.ptr;
		}
		Forward_iterator(std::shared_ptr<Node> ptr) : ptr(ptr){}

		friend class Queue<T>;
	};

private:
	std::shared_ptr<Node> head;
	std::shared_ptr<Node> tail;

public:
	Forward_iterator begin();
	Forward_iterator end();
	void insert(Forward_iterator&, const T&);
	void erase(Forward_iterator&);
	const T& top();
	void pop();
	void push(const T&);

	Queue();
};

template <class T>
Queue<T>::Queue() : tail(new Node(T())) {
	head = tail;
}

template <class T>
const T& Queue<T>::top() {
	if (tail->prev.lock() == nullptr) {
		throw std::runtime_error("Error: Queue is empty");
	}
	return *(tail->prev.lock()->data);
}

template <class T>
void Queue<T>::pop() {
	if (tail->prev.lock() == nullptr) {
		throw std::runtime_error("Error: Queue is empty");
	}
	tail = tail->prev.lock();
}

template <class T>
void Queue<T>::push(const T &value) {
	std::shared_ptr<Node> node(new Node(value));
	node->next = head;
	head->prev = node;
	head = node;
}

template <class T>
typename Queue<T>::Forward_iterator Queue<T>::begin() {
	return Forward_iterator(head);
}

template <class T>
typename Queue<T>::Forward_iterator Queue<T>::end() {
	return Forward_iterator(tail);
}

template <class T>
void Queue<T>::insert(typename Queue<T>::Forward_iterator& iter, const T& value) {
	if (iter.ptr == nullptr) {
		throw std::runtime_error("Error: Out of bounds");
	}
	if (iter == begin()) {
		push(value);
	} else {  
		std::shared_ptr<Node> node(new Node(value));
		node->next = iter.ptr;
		node->prev = iter.ptr->prev;
		iter.ptr->prev.lock()->next = node;
		iter.ptr->prev = node;
	}
}

template <class T>
void Queue<T>::erase(typename Queue<T>::Forward_iterator& iter) {
	if (iter.ptr == nullptr || iter == end()) {
		throw std::runtime_error("Error: Out of bounds");
	}
	if (iter == begin()) {
		head = head->next;
	} else {
		iter.ptr->prev.lock()->next = iter.ptr->next;
	}
}
