// Квадрат. Хранит данные как координаты левой нижней вершины и длину стороны.

#pragma once

#include <utility>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "figure.hpp"

template <typename T>
class Square : public Figure {
public:
	std::pair<T,T> x;
	T a;

	Square() = default;
	Square(T x1, T x2, T a) : x(x1,x2), a(a) {
		if (a <= 0) {
			throw std::invalid_argument("Invalid square parameters");
		}
	}
	~Square() = default;

	void print(std::ostream& os = std::cout) override {
		os << "Square:\n" <<
			"(" << x.first << ", " << x.second << ") " << 
			"(" << x.first << ", " << x.second + a << ") " << 
			"(" << x.first + a << ", " << x.second + a << ") " <<
			"(" << x.first + a << ", " << x.second << ")" << std::endl;
	}


	template <class U>
	friend std::istream& operator>>(std::istream&, Square<U>&);
};

template <class T>
std::istream& operator>>(std::istream& is, Square<T>& sq) {
	is >> sq.x.first >> sq.x.second >> sq.a;
	if (sq.a <= 0) {
		throw std::invalid_argument("Invalid square parameters");
	}
	return is;
}