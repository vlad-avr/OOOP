#pragma once

#include <iostream>
#include <cassert>

template<typename T>
class C_Array
{
private:
	unsigned int _size;
	T* arr = NULL;
public:
	C_Array(unsigned int size) {
		_size = size;
		arr = new T[_size];
	}
	void set(T val, unsigned int id) {
		assert(id < _size);
		arr[id] = val;
	}

	unsigned int size() {
		return _size;
	}

	T* get(unsigned int index) {
		assert(index < _size);
		return &arr[index];
	}

	void del(unsigned int ID) {
		assert(ID < _size);
		T* new_arr = new T[_size - 1];
		for (int i = 0; i < ID; i++) {
			new_arr[i] = arr[i];
		}
//		delete arr[ID];
		for (int i = ID + 1; i < _size; i++) {
			new_arr[i - 1] = arr[i];
		}
		arr = new_arr;
		_size--;
	}

	void print() {
		for (int i = 0; i < _size; i++) {
			std::cout << arr[i] << "\n";
		}
	}
};

