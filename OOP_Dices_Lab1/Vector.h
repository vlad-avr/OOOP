#pragma once
#include <iostream>
#include <vector>
#include "Dice.h"
#include <cassert>

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
		*get(id) = val;
	}

	T* get(unsigned int i) {
		assert(i < arr.size());
		return &arr[i];
	}

	unsigned int size() {
		return arr.size();
	}

	void print() {
		unsigned int size = arr.size();
		for (int i = 0; i < size; i++) {
			std::cout << arr[i];
		}
	}

	void del(unsigned int id) {
		assert(id < arr.size());
		typename std::vector<T>::iterator iter = arr.begin() + id;
		arr.erase(iter);
	}

};

