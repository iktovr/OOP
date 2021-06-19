// Бирюков В.В. М8О-107Б-19
// Создать шаблон динамической коллекцию, согласно варианту задания:
//    1. Коллекция должна быть реализована с помощью умных указателей (std::shared_ptr, std::weak_ptr). Опционально использование std::unique_ptr.
//    2. В качестве параметра шаблона коллекция должна принимать тип данных - фигуры.
//    3. Реализовать forward_iterator по коллекции.
//    4. Коллекция должны возвращать итераторы begin() и  end().
//    5. Коллекция должна содержать метод вставки на позицию итератора insert(iterator).
//    6. Коллекция должна содержать метод удаления из позиции итератора erase(iterator).
//    7. При выполнении недопустимых операций (например выход аз границы коллекции или удаление несуществующего элемента) необходимо генерировать исключения.
//    8. Итератор должен быть совместим со стандартными алгоритмами (например, std::count_if).
//    9. Коллекция должна содержать метод доступа:
//        стек – pop, push, top.
//        очередь – pop, push, top.
//        список, Динамический массив – доступ к элементу по оператору [].
//    10. Реализовать программу, которая:
//        позволяет вводить с клавиатуры фигуры (с типом int в качестве параметра шаблона фигуры) и добавлять в коллекцию.
//        позволяет удалять элемент из коллекции по номеру элемента.
//        выводит на экран введенные фигуры c помощью std::for_each.
//        выводит на экран количество объектов, у которых площадь меньше   заданной (с помощью  std::count_if).
// Вариант 17: треугольник, очередь.

#include <iostream>
#include <algorithm>

#include "queue.hpp"
#include "triangle.hpp"

int main() {
	Queue<Triangle<int>> queue;

	std::cout << "a TRIANGLE - Push" << std::endl
			<< "d - Pop" << std::endl
			<< "t - Top" << std::endl
			<< "i INDEX TRIANGLE - Insert" << std::endl
			<< "e INDEX - Erase" << std::endl
			<< "p - Print" << std::endl
			<< "f SQUARE - Filter" << std::endl
			<< "q - Exit" << std::endl;

	char command;
	std::cout << "> ";
	while (std::cin >> command && command != 'q') {
		try {
			if (command == 'a') {
				Triangle<int> tr;
				std::cin >> tr;
				queue.push(tr);

			} else if (command == 'd') {
				queue.pop();

			} else if (command == 't') {
				std::cout << queue.top() << std::endl;
			
			} else if (command == 'i') {
				int index;
				std::cin >> index;
				Triangle<int> tr;
				std::cin >> tr;
				if (index < 0) {
					throw std::runtime_error("Error: Out of bounds");
				}
				auto iter = queue.begin();
				while (index--) {
					++iter;
				}
				queue.insert(iter, tr);

			} else if (command == 'e') {
				int index;
				std::cin >> index;
				if (index < 0) {
					throw std::runtime_error("Error: Out of bounds");
				}
				auto iter = queue.begin();
				while (index--) {
					++iter;
				}
				queue.erase(iter);

			} else if (command == 'p') {
				std::for_each(queue.begin(), queue.end(), [](const Triangle<int>& tr) { std::cout << tr << std::endl; });

			} else if (command == 'f') {
				int square;
				std::cin >> square;
				std::cout << std::count_if(queue.begin(), queue.end(), [&square](const Triangle<int>& tr) { return tr.square() < square; }) << std::endl;
			}
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		std::cout << "> ";
	}
}