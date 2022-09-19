#pragma once
#include <iostream>
#include <vector>
#include "Dice.h"

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

	T* get(unsigned int i) {
		if (i >= arr.size()) {
			return NULL;
		}
		else {
			return &arr[i];
		}
	}

	unsigned int size() {
		return arr.size();
	}

};

