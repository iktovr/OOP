// Класс, создающий фигуры.

#pragma once

#include <memory>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "figure.hpp"
#include "triangle.hpp"
#include "square.hpp"
#include "rectangle.hpp"

template <class T>
class Factory {
public:
	std::shared_ptr<Figure> create(std::string type, std::istream& is = std::cin) const {
		std::shared_ptr<Figure> figure;
		if (type == "triangle") {
			Triangle<T>* tr = new Triangle<T>;
			is >> *tr;
			figure = std::shared_ptr<Figure>(reinterpret_cast<Figure*>(tr));
		}

		else if (type == "square") {
			Square<T>* sq = new Square<T>;
			is >> *sq;
			figure = std::shared_ptr<Figure>(reinterpret_cast<Figure*>(sq));
		}

		else if (type == "rectangle") {
			Rectangle<T>* rect = new Rectangle<T>;
			is >> *rect;
			figure = std::shared_ptr<Figure>(reinterpret_cast<Figure*>(rect));
		}

		else {
			throw std::runtime_error("Unknown figure type");
		}
		return figure;
	}

	Factory() = default;
	~Factory() = default;
};
