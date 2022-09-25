#include "Vector.h"
#include "doctest.h"

TEST_CASE("Create array, add, set, get and delete element") {
	Vector<int> arr;
	arr.add(0);
	arr.add(1);
	arr.add(2);
	CHECK(*(arr.get(0)) == 0);
	CHECK(*(arr.get(1)) == 1);
	arr.set(3,0);
	CHECK(*(arr.get(0)) == 3);
	arr.del(1);
	CHECK(arr.size() == 2);
	CHECK(*(arr.get(1)) == 2);
}

bool comp(int* n1, int* n2) {
	if (*n1 >= *n2) {
		return true;
	}
	else
		return false;
}

int findMax(std::vector<int>* arr, int n, bool (*cmp)(int*, int*))
{
	int i, max = (*arr)[0], cnt = 0;
	for (i = 1; i < n; i++)
	{
		if (cmp(&(*arr)[i], &max))
			max = (*arr)[i];
	}
	while (max > 0)
	{
		cnt++;
		max = max / 10;
	}

	return cnt;
}

void bucketSort(std::vector<int>* arr, int** bucket, int n, bool (*cmp)(int*, int*))
{
	static int i, j[10], k, l, d = 1;
	int c;
	c = findMax(arr, n, cmp);

	for (int m = 0; m < c; m++)
	{
		for (i = 0; i < 10; i++)
			j[i] = 0;
		for (i = 0; i < n; i++)
		{
			k = ((*arr)[i] / d) % 10;
			bucket[k][j[k]] = (*arr)[i];
			j[k]++;
		}

		l = 0;
		for (i = 0; i < 10; i++)
		{
			for (k = 0; k < j[i]; k++)
			{
				(*arr)[l] = bucket[i][k];
				l++;
			}
		}
		d *= 10;
	}
}

void b_sort(std::vector<int>* arr, int size, bool(*cmp)(int*, int*)) {
	int* bucket[10];
	for (int i = 0; i < 10; i++)
		bucket[i] = new int[size];
	bucketSort(arr, bucket, size, cmp);
}

TEST_CASE("Sorting") {
	Vector<int> arr;
	for (int i = 0; i < 10; i++) {
		arr.add(10 - i);
	}
	arr.insert_sort(comp);
	CHECK(*(arr.get(0)) == 10);
	CHECK(*(arr.get(arr.size() - 1)) == 1);
	for (int i = 0; i < 10; i++) {
		arr.set(10 - i, i);
	}
	arr.qsort(comp);
	CHECK(*(arr.get(0)) == 10);
	CHECK(*(arr.get(arr.size() - 1)) == 1);
	for (int i = 0; i < 10; i++) {
		arr.set(10 - i, i);
	}
	arr.msort(comp);
	CHECK(*(arr.get(0)) == 10);
	CHECK(*(arr.get(arr.size() - 1)) == 1);
	for (int i = 0; i < 10; i++) {
		arr.set(i + 1, i);
	}
	arr.custom_sort(b_sort, comp);
	CHECK(*(arr.get(0)) == 1);
	CHECK(*(arr.get(arr.size() - 1)) == 10);

}