#pragma once


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
		if (id >= _size) {
			return;
		}
		else {
			arr[id] = val;
		}
	}
	void print() {
		for (int i = 0; i < _size; i++) {
			std::cout << arr[i] << "\n";
		}
	}
};

