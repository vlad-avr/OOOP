#pragma once
#include <iostream>
#include <vector>

template <typename T>
class Vector
{
private:
	std::vector<T> arr;

public:

	void append(T item) {
		arr.push_back(item);
	}

	void set(T val, unsigned int id) {
		if (id >= arr.size()) {
			return;
		}
		else {
			arr[id] = val;
		}
	}

	void print() {
		unsigned int N = arr.size();
		for (int i = 0; i < N; i++) {
			std::cout << arr[i] << "\n";
		}
	}
};

