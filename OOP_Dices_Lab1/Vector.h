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

	void append(T item) {
		arr.push_back(item);
	}

	void set(T val, unsigned int id) {
		*get(id) = val;
	}

	T* get(unsigned int i) {
	//	std::cout << i << " ; ";
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

	void insert_sort(bool (*comp)(T*, T*)) {
		T temp = NULL;
		int j;
		unsigned int len = size();
		for (int i = 1; i < len; i++) {
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
		qsort_rec(comp, arr[0], arr[size() - 1]);
	}
};

