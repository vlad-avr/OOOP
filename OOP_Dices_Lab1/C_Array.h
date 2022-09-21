#pragma once

#include <iostream>
#include <cassert>

template<typename T>
class C_Array
{
private:
	unsigned int _size;
	T* arr = NULL;
	void swap(T* p, T* q) {
		T temp;
		temp = *q; *q = *p; *p = temp;
	}

	void qsort_rec(bool (*comp)(T*, T*), T* beg, T* end) {
		T r_pivot_str, * l_pointer, * r_pointer;
		if ((end - beg == 1) && !comp(beg, end)) {
			swap(beg, end);
		}
		else if (end - beg > 1) {
			l_pointer = beg;
			r_pointer = end - 1;
			r_pivot_str = *end;
			while (l_pointer < r_pointer) {
				if (!comp(r_pointer, &r_pivot_str)) {
					r_pointer--;
				}
				else {
					if (!comp(l_pointer, &r_pivot_str)) {
						swap(l_pointer, r_pointer);
					}
					l_pointer++;
				}
			}
			if (comp(l_pointer, &r_pivot_str)) {
				r_pointer++;
			}
			swap(r_pointer, end);
			qsort_rec(beg, r_pointer - 1);
			qsort_rec(r_pointer + 1, end);
		}
	}
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

	void insert_sort(bool (*comp)(T*, T*)) {
		T temp = NULL;
		int j;
		for (int i = 1; i < _size; i++) {
			temp = arr[i];
			for (j = i - 1; j >= 0; j--) {
				if (comp(&arr[j], &temp)) {
					break;
				}
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		}
	}

	void qsort(bool (*comp)(T*, T*)) {
		qsort_rec(comp, arr[0], arr[_size-1]);
	}

};

