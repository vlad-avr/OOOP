#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include "Container.h"

template <typename T>
class Vector: public Container<T>
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
			qsort_rec(comp, beg, r_pointer - 1);
			qsort_rec(comp, r_pointer + 1, end);
		}
	}


	void merge(std::vector<T> array, int const left, int const mid, int const right, bool (*comp)(T*, T*))
	{
		auto const sub_arr1 = mid - left + 1;
		auto const sub_arr2 = right - mid;

		auto* left_p = new T[sub_arr1], * right_p = new T[sub_arr2];

		for (auto i = 0; i < sub_arr1; i++)
			left_p[i] = array[left + i];
		for (auto j = 0; j < sub_arr2; j++)
			right_p[j] = array[mid + 1 + j];

		auto sub_arr1_id = 0, sub_arr2_id = 0;
		int merged_id = left;

		while (sub_arr1_id < sub_arr1 && sub_arr2_id < sub_arr2) {
			if (comp(&(left_p[sub_arr1_id]), &(right_p[sub_arr2_id]))) {
				array[merged_id] = left_p[sub_arr1_id];
				sub_arr1_id++;
			}
			else {
				array[merged_id] = right_p[sub_arr2_id];
				sub_arr2_id++;
			}
			merged_id++;
		}

		while (sub_arr1_id < sub_arr1) {
			array[merged_id] = left_p[sub_arr1_id];
			sub_arr1_id++;
			merged_id++;
		}

		while (sub_arr2_id < sub_arr2) {
			array[merged_id] = right_p[sub_arr2_id];
			sub_arr2_id++;
			merged_id++;
		}
		delete[] left_p;
		delete[] right_p;
	}

	void mergeSort(std::vector<T> array, int const begin, int const end, bool (*comp)(T*, T*))
	{
		if (begin >= end)
			return;

		auto mid = begin + (end - begin) / 2;
		mergeSort(array, begin, mid, comp);
		mergeSort(array, mid + 1, end, comp);
		merge(array, begin, mid, end, comp);
	}

public:

	void add(T item) {
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
		qsort_rec(comp, &arr[0], &arr[size() - 1]);
	}

	void msort(bool (*comp)(T*, T*)) {
		mergeSort(arr, 0,arr.size()-1, comp);
	}

	void custom_sort(void (*sort)(std::vector<T>*, int, bool (*)(T*, T*)), bool (*comp)(T*, T*)) {
		sort(&arr, arr.size(), comp);
	}

};

