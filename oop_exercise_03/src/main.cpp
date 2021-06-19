#include <iostream>
#include <vector>
#include <cmath>

class Coord {
public:
	double x;
	double y;
	
	Coord() : x(0.0), y(0.0) {}
	Coord(double _x, double _y) : x(_x), y(_y) {}
	Coord(const Coord &coord) : x(coord.x), y(coord.y) {}

	friend std::ostream& operator<<(std::ostream &, const Coord &);
	friend std::istream& operator>>(std::istream &, Coord &);
	friend double operator*(const Coord &, const Coord &);
	friend Coord operator-(const Coord &, const Coord &);
};

std::ostream& operator<<(std::ostream &os, const Coord &coord) {
	os << "(" << coord.x << ", " << coord.y << ")";
	return os;
}

std::istream& operator>>(std::istream &is, Coord &coord) {
	is >> coord.x >> coord.y;
	return is;
}

double operator*(const Coord &a, const Coord &b) {
	// модуль векторного произведения
	return fabs(a.x * b.y - a.y * b.x);
}

Coord operator-(const Coord &a, const Coord &b) {
	return Coord(a.x - b.x, a.y - b.y);
}

class Figure {
protected:
	virtual std::ostream& print(std::ostream &) const = 0;

public:
	virtual Coord center() = 0;
	virtual double square() = 0;
	virtual ~Figure() = default;

	friend std::ostream& operator<<(std::ostream &, const Figure &);
};

std::ostream& operator<<(std::ostream &os, const Figure &f) {
	return f.print(os);
}

class Triangle : public Figure {
private:
	// Координаты каждой вершины
	Coord a;
	Coord b;
	Coord c;

	std::ostream& print(std::ostream &) const override;

public:
	Triangle() : a(), b(), c() {}
	Triangle(Coord _a, Coord _b, Coord _c) : a(_a), b(_b), c(_c) {
		if (square() == 0) {
			throw std::invalid_argument("Invalid triangle parameters");
		}
	}
	Triangle(const Triangle& tr) : a(tr.a), b(tr.b), c(tr.c) {}
	Coord center() override;
	double square() override;
	friend std::istream& operator>>(std::istream &, Triangle &);
};

double Triangle::square() {
	return (b - a) * (c - a) / 2;
}

Coord Triangle::center() {
	return Coord((a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3);
}

std::ostream& Triangle::print(std::ostream &os) const {
	os << a << " " << b << " " << c;
	return os;
}

std::istream& operator>>(std::istream &is, Triangle &tr) {
	is >> tr.a >> tr.b >> tr.c;
	if (tr.square() == 0) {
		throw std::invalid_argument("Invalid triangle parameters");
	}
	return is;
}

class Square : public Figure {
private:
	// Координаты левого нижнего угла и длина стороны
	Coord x;
	double a;

	std::ostream& print(std::ostream &) const override;

public:
	Square() : x(), a(0.0) {}
	Square(Coord _x, double _a) : x(_x), a(_a) {
		if (a <= 0) {
			throw std::invalid_argument("Invalid square parameters");
		}
	}
	Square(const Square& sq) : x(sq.x), a(sq.a) {}
	Coord center() override;
	double square() override;
	friend std::istream& operator>>(std::istream &, Square &);
};

double Square::square() {
	return a * a;
}

Coord Square::center() {
	return Coord(x.x + a/2, x.y + a/2);
}

std::ostream& Square::print(std::ostream &os) const {
	os << x << " " << Coord(x.x, x.y + a) << " " << Coord(x.x + a, x.y + a) << " " << Coord(x.x + a, x.y);
	return os;
}

std::istream& operator>>(std::istream &is, Square &sq) {
	is >> sq.x >> sq.a;
	if (sq.a <= 0) {
		throw std::invalid_argument("Invalid square parameters");
	}
	return is;
}

class Rectangle : public Figure {
private:
	// Координаты левого нижнего угла и длины сторон
	Coord x;
	double a;
	double b;

	std::ostream& print(std::ostream &) const override;

public:
	Rectangle() : x(), a(), b() {}
	Rectangle(Coord _x, double _a, double _b) : x(_x), a(_a), b(_b) {
		if (a <= 0 || b <= 0) {
			throw std::invalid_argument("Invalid rectangle parameters");
		}
	}
	Rectangle(const Rectangle& rect) : x(rect.x), a(rect.a), b(rect.b) {}
	Coord center() override;
	double square() override;
	friend std::istream& operator>>(std::istream &, Rectangle &);
};

double Rectangle::square() {
	return a * b;
}

Coord Rectangle::center() {
	return Coord(x.x + a/2, x.y + b/2);
}

std::ostream& Rectangle::print(std::ostream &os) const {
	os << x << " " << Coord(x.x, x.y + b) << " " << Coord(x.x + a, x.y + b) << " " << Coord(x.x + a, x.y);
	return os;
}

std::istream& operator>>(std::istream &is, Rectangle &rect) {
	is >> rect.x >> rect.a >> rect.b;
	if (rect.a <= 0 || rect.b <= 0) {
		throw std::invalid_argument("Invalid rectangle parameters");
	}
	return is;
}

int main() {
	Triangle *tr = nullptr;
	Square *sq = nullptr;
	Rectangle *rect = nullptr;
	char s;
	unsigned int del = -1;
	size_t n;

	std::cin >> n;

	std::vector<Figure*> figures(n);

	try {
		for (size_t i = 0; i < n; i++) {
			std::cin >> s; 
			if (s == 't') {
				tr = new Triangle();
				std::cin >> *tr;
				figures[i] = (Figure *)tr;
			} else if (s == 's') {
				sq = new Square();
				std::cin >> *sq;
				figures[i] = (Figure *)sq;
			} else if (s == 'r') {
				rect = new Rectangle();
				std::cin >> *rect;
				figures[i] = (Figure *)rect;
			}
		}
	} catch (const std::invalid_argument &ex) {
		std::cout << ex.what() << '\n';
		return 1;
	}

	std::cin >> del;
	del--;

	if (del < 0 || del >= figures.size()) {
		std::cout << "Invalid index for deletion" << '\n';
		return 1;
	}

	std::cout << "Coordinates:" << '\n';
	for (Figure* f : figures) {
		std::cout << *f << '\n';
	}

	std::cout << "Centers:" << '\n';
	for (Figure* f : figures) {
		std::cout << f->center() << '\n';
	}

	std::cout << "Squares:" << '\n';
	double sum = 0;
	for (Figure* f : figures) {
		sum += f->square();
		std::cout << f->square() << '\n';
	}

	std::cout << "Total square: " << sum << '\n';
	
	std::cout << "Deleting figure by index " << del << '\n';

	auto i = figures.begin();
	for (; i != figures.end() && del > 0; ++i, --del);
	figures.erase(i);

	std::cout << "Coordinates again:" << '\n';
	for (Figure* f : figures) {
		std::cout << *f << '\n';
	}

	for (Figure* f : figures) {
		delete f;
	}

}