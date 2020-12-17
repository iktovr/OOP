// Класс обработчиков

#pragma once

#include <vector>
#include <queue>
#include <list>
#include <functional>
#include <memory>
#include <mutex>
#include <stdexcept>

#include "figure.hpp"

using buffer_type = std::vector<std::shared_ptr<Figure>>;
using processor_type = std::function<void(const buffer_type&)>;

class Processor {
private:
	bool work;
	std::mutex mutex;
	std::queue<buffer_type> message_queue;
	std::list<processor_type> processors;

public:
	Processor() : work(false), mutex(), message_queue(), processors() {}

	void add(const processor_type &pr) {
		processors.push_back(pr);
	}

	void operator() () {
		work = true;

		while (work) {
			if (!message_queue.empty()) {
				mutex.lock();
				for (auto &processor: processors) {
					try {
						processor(message_queue.front());
					} catch (const std::exception& ex) {
						std::cerr << "Error in processor " << ex.what() << std::endl;
					}
				}
				message_queue.pop();
				mutex.unlock();
			} else {
				std::this_thread::yield();
			}
		}
	}

	void publish(buffer_type& buffer) {
		mutex.lock();
		message_queue.push(buffer);
		mutex.unlock();
	}

	void stop() {
		work = false;
	}

	bool is_over() {
		return message_queue.empty();
	}

};