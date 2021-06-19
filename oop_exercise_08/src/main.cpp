/*
Бирюков В.В. М8О-107Б-19

Создать приложение, которое будет считывать из стандартного ввода данные фигур, 
согласно варианту задания, выводить их характеристики на экран и записывать в файл. 
Фигуры могут задаваться как своими вершинами, так и другими характеристиками 
(например, координата центра, количество точек и радиус).
Программа должна:
	- Осуществлять ввод из стандартного ввода данных фигур, согласно варианту задания.
	- Программа должна создавать классы, соответствующие введенным данных фигур.
	- Программа должна содержать внутренний буфер, в который помещаются фигуры. 
		Для создания буфера допускается использовать стандартные контейнеры STL. 
		Размер буфера задается параметром командной строки.
	- При накоплении буфера они должны запускаться на асинхронную обработку, после 
		чего буфер должен очищаться.
	- Обработка должна производиться в отдельном потоке.
	- Реализовать два обработчика, которые должны обрабатывать данные буфера:
		* Вывод информации о фигурах в буфере на экран.
		* Вывод информации о фигурах в буфере в файл. Для каждого буфера должен 
			создаваться файл с уникальным именем.
	- Оба обработчика должны обрабатывать каждый введенный буфер. 
		Т.е. после каждого заполнения буфера его содержимое должно выводиться 
		как на экран, так и в файл.
	- Обработчики должны быть реализованы в виде лямбда-функций и должны хранится 
		в специальном массиве обработчиков. Откуда и должны последовательно 
		вызываться в потоке – обработчике.
	- В программе должно быть ровно два потока (thread). 
		Один основной (main) и второй для обработчиков;
	- В программе должен явно прослеживаться шаблон Publish-Subscribe. 
		Каждый обработчик должен быть реализован как отдельный подписчик.
	- Реализовать в основном потоке (main) ожидание обработки буфера в 
		потоке-обработчике. Т.е. после отправки буфера на обработку основной 
		поток должен ждать, пока поток обработчик выведет данные на экран и запишет в файл.

Вариант 17: треугольник, квадрат, прямоугольник.
*/

#include <stdexcept>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>

#include "figure.hpp"
#include "factory.hpp"
#include "processor.hpp"

using coord_type = int;

std::string get_filename() {
	static int count{0};
	return "buffer" + std::to_string(count++) + ".txt";
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		throw std::invalid_argument("Buffer size expected");
	}
	unsigned long long buffer_size = std::strtoull(argv[1], nullptr, 10);
	if (buffer_size == 0) {
		throw std::invalid_argument("Invalid buffer size");
	}

	Factory<int> factory;

	buffer_type buffer;
	buffer.reserve(buffer_size);

	Processor processor;
	processor.add([](const buffer_type& buffer) {
		for (const std::shared_ptr<Figure>& figure: buffer) {
			figure->print();
		}
	});
	processor.add([](const buffer_type& buffer) {
		std::ofstream file(get_filename());
		if (file.fail()) {
			throw std::runtime_error("Error opening file");
		}
		for (const std::shared_ptr<Figure>& figure: buffer) {
			figure->print(file);
		}
		file.close();
	});

	std::thread processing_thread(std::ref(processor));

	std::string figure_type;
	std::cout << "> ";
	while (std::cin >> figure_type && figure_type != "exit") {
		try {
			buffer.push_back(factory.create(figure_type));

			if (buffer.size() == buffer_size) {
				std::cout << "Processing..." << std::endl;
				processor.publish(buffer);
				while (!processor.is_over());
				std::cout << "Processing is complete." << std::endl;

				buffer.clear();
			}
		} catch (const std::exception& ex) {
			std::cerr << ex.what() << std::endl;
		}
		std::cout << "> ";
	}

	processor.stop();
	processing_thread.join();
}
