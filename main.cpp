#include <iostream>
#include <tuple>
#include <type_traits>
#include <cmath>

template <class... Ts>
struct is_tuple : std::false_type {};

template <class... Ts>
struct is_tuple<std::tuple<Ts...>> : std::true_type {};

template <typename T>
class Triangle {
public:
	using type = T;
	// левая вершина и длина стороны
	std::pair<T,T> x;
	T a;
	Triangle(T x1, T x2, T a) : x(x1,x2), a(a) {
		if (a <= 0) {
			throw std::invalid_argument("Invalid triangle parameters");
		}
	}
};

template <typename T>
class Square {
public:
	using type = T;
	// левая нижняя грань и длина стороны
	std::pair<T,T> x;
	T a;
	Square(T x1, T x2, T a) : x(x1,x2), a(a) {
		if (a <= 0) {
			throw std::invalid_argument("Invalid square parameters");
		}
	}
};

template <typename T>
class Rectangle {
public:
	using type = T;
	// левая нижняя грань и длины сторон
	std::pair<T,T> x;
	T a;
	T b;
	Rectangle(T x1, T x2, T a, T b) : x(x1,x2), a(a), b(b) {
		if (a <= 0 || b <= 0) {
			throw std::invalid_argument("Invalid rectangle parameters");
		}
	}
};


template <class T, size_t index = 0>
typename std::enable_if<is_tuple<T>::value, void>::type print(T &tup) {
	if constexpr (index < std::tuple_size<T>::value) {
		print(std::get<index>(tup));
		print<T, index+1>(tup);
	} else {
		return;
	}
}

template <class T>
typename std::enable_if<std::is_same<T, Triangle<typename T::type>>::value, void>::type print(T &tr) {
	std::cout << "(" << tr.x.first << ", " << tr.x.second << ") " <<
				"(" << tr.x.first + 1.0 / 2 * tr.a << ", " << 
				tr.x.second + sqrt(3) / 2 * tr.a << ") " <<
				"(" << tr.x.first + tr.a << ", " << tr.x.second << ")" << std::endl;

}

template <class T>
typename std::enable_if<std::is_same<T, Square<typename T::type>>::value, void>::type print(T &sq) {
	std::cout << "(" << sq.x.first << ", " << sq.x.second << ") " << 
				"(" << sq.x.first << ", " << sq.x.second + sq.a << ") " << 
				"(" << sq.x.first + sq.a << ", " << sq.x.second + sq.a << ") " <<
				"(" << sq.x.first + sq.a << ", " << sq.x.second << ")" << std::endl;
}

template <class T>
typename std::enable_if<std::is_same<T, Rectangle<typename T::type>>::value, void>::type print(T &rect) {
	std::cout << "(" << rect.x.first << ", " << rect.x.second << ") " << 
				"(" << rect.x.first << ", " << rect.x.second + rect.b << ") " << 
				"(" << rect.x.first + rect.a << ", " << rect.x.second + rect.b << ") " <<
				"(" << rect.x.first + rect.a << ", " << rect.x.second << ")" << std::endl;
}

template <class T, size_t index = 0>
typename std::enable_if<is_tuple<T>::value, double>::type square(T &tup) {
	if constexpr (index < std::tuple_size<T>::value) {
		double value = square(std::get<index>(tup));
		value += square<T, index+1>(tup);
		return value;
	} else {
		return 0;
	}
}

template <class T>
typename std::enable_if<std::is_same<T, Triangle<typename T::type>>::value, double>::type square(const T &tr) {
	return sqrt(3) / 4 * tr.a * tr.a;
}

template <class T>
typename std::enable_if<std::is_same<T, Square<typename T::type>>::value, typename T::type>::type square(const T &sq) {
	return sq.a * sq.a;
}

template <class T>
typename std::enable_if<std::is_same<T, Rectangle<typename T::type>>::value, typename T::type>::type square(const T &rect) {
	return rect.a * rect.b;
}

int main() {
}