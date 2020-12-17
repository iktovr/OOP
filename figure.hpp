// Абстрактный класс фигуры.

#pragma once

#include <fstream>
#include <iostream>

class Figure {
public:
	virtual void print(std::ostream& = std::cout) = 0;
	virtual ~Figure() = default;
};