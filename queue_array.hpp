#pragma once

#include <memory>
#include <stdexcept>

template <class T>
class Queue {
public:
	class Forward_iterator {
	private:
		std::shared_ptr<T[]> data;
		size_t *size;
		size_t index;
	
	public:
		using iterator_category = std::forward_iterator_tag;
    	using value_type = T;
    	using difference_type = size_t;
    	using pointer = T*;
    	using reference = T&;
		T& operator*() {
			return data[index];
		}
		Forward_iterator& operator++() {
			index = (index + 1) % (*size + 1);
			return *this;
		}
		bool operator!=(const Forward_iterator& other) {
			if (data == other.data) {
				return index != other.index;
			} else {
				return true;
			}
		}
		Forward_iterator(std::shared_ptr<T[]> data, size_t* size, size_t index) : data(data), size(size), index(index) {}
	};
	
private:
	std::shared_ptr<T[]> data;
	size_t start;
	size_t size;
	size_t capacity;

public:
	Forward_iterator begin();
	Forward_iterator end();
	void insert(Forward_iterator&, T&);
	void erase(Forward_iterator&);
	const T& top();
	void pop();
	void push(const T&);

	Queue();
};

template <class T>
Queue<T>::Queue() {
	data = std::shared_ptr<T[]>(new T[2]);
	capacity = 1;
	size = 0;
	start = 1;
}

template <class T>
const T& Queue<T>::top() {
	if (size != 0) {
		return data[(start + size - 1) % capacity];
	} else {
		throw std::runtime_error("Queue is empty");
	}
}

template <class T>
void Queue<T>::pop() {
	if (size != 0) {
		--size;
	} else {
		throw std::runtime_error("Queue is empty");
	}
}

template <class T>
void Queue<T>::push(const T &value) {
	if (size == capacity) {
		std::shared_ptr<T[]> new_data(new T[capacity * 2 + 1]);
		size_t i = size;
		for (auto &a: *this) {
			new_data[i] = a;
			++i;
		}
		data = new_data;
		start = size;
		capacity = capacity * 2;
	}
	start = (start + capacity - 1) % capacity;
	data[start] = value;
	++size;
}

template <class T>
typename Queue<T>::Forward_iterator Queue<T>::begin() {
	return Forward_iterator(data, &capacity, start);
}

template <class T>
typename Queue<T>::Forward_iterator Queue<T>::end() {
	return Forward_iterator(data, &capacity, (start + size) % (capacity + 1));
}
