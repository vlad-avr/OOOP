

#include <iostream>
#include "L_List.h"
#include "Dice.h"
#include "C_Array.h"
#include "Vector.h"
#include <time.h>
#include "Container.h"

struct Sum {
	double sum;
	double possib;
	Sum(double sum = 0, double possib = 0) {
		this->sum = sum;
		this->possib = possib;
	}


};

std::ostream& operator<<(std::ostream& os, Vector<Sum>*& vec) {
	vec->print();
	os << "\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, Sum& s) {
	os << s.sum << " : " << s.possib;
	os << "\n";
	return os;
}


int findMax(int arr[], int n, bool (*cmp)(int*, int*))
{
	int i, max = arr[0], cnt = 0;
	for (i = 1; i < n; i++)
	{
		if (cmp(&arr[i], &max))
			max = arr[i];
	}
	while (max > 0)
	{
		cnt++;
		max = max / 10;
	}

	return cnt;
}

void bucketSort(int arr[], int** bucket, int n, bool (*cmp)(int*, int*))
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
			k = (arr[i] / d) % 10;
			bucket[k][j[k]] = arr[i];
			j[k]++;
		}

		l = 0;
		for (i = 0; i < 10; i++)
		{
			for (k = 0; k < j[i]; k++)
			{
				arr[l] = bucket[i][k];
				l++;
			}
		}
		d *= 10;
	}
}

void b_sort(int arr[], int size, bool(*cmp)(int*, int*)) {
	int* bucket[10];
	for (int i = 0; i < 10; i++)
		bucket[i] = new int[size];
	bucketSort(arr, bucket, size, cmp);
}

bool num_cmp(int* num1, int* num2) {
	if (*num1 > *num2) {
		return true;
	}
	else {
		return false;
	}
}

Vector<Vector<Sum>*>* get_sums(Container<Container<Dice>*>*);
Vector<Sum>* get_sums_rec(Container<Dice>*, unsigned int);
void norm(Vector<Sum>*);

bool d_comp(Dice*, Dice*);

template<typename T> 
void in_sort(T* arr, int _size, bool(*comp)(T*, T*)) {
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


bool comp(Dice::Face** f1, Dice::Face** f2) {
	if ((*f1)->val > (*f2)->val) {
		return true;
	}
	else {
		return false;
	}
}


int main(int argc, char** argv)
{
	
	srand(time(0));
	
	Vector<Dice> d_vec;
	Container<Dice>& dice = d_vec;
	dice.add(Dice(4));
	dice.get(0)->auto_gen(1, 4);
	dice.add(Dice(2));
	dice.get(1)->auto_gen(1, 2);
	dice.add(Dice(12));
	dice.get(2)->auto_gen(1, 12);
	dice.add(Dice(6));
	dice.get(3)->auto_gen(1, 6);
	dice.print();
	dice.qsort(d_comp);
	dice.print();

	C_Array<Dice> d_arr(4);
	Container<Dice>& dice_arr = d_arr;
	dice_arr.set(Dice(12), 0);
	dice_arr.get(0)->auto_gen(1, 12);
	dice_arr.set(Dice(8), 1);
	dice_arr.get(1)->auto_gen(1, 8);
	dice_arr.set(Dice(6), 2);
	dice_arr.get(2)->auto_gen(1, 6);
	dice_arr.set(Dice(4), 3);
	dice_arr.get(3)->auto_gen(1, 4);
	dice_arr.print();
	dice_arr.custom_sort(in_sort, d_comp);
	dice_arr.print();

	L_List<Dice> list;
	Container<Dice>& dice_list = list;
	dice_list.add(Dice(4));
	dice_list.get(0)->auto_gen(1, 4);
	dice_list.add(Dice(2));
	dice_list.get(1)->auto_gen(1, 2);
	dice_list.add(Dice(12));
	dice_list.get(2)->auto_gen(1, 12);
	dice_list.add(Dice(6));
	dice_list.get(3)->auto_gen(1, 6);
	dice_list.print();
	dice_list.qsort(d_comp);
	dice_list.print();
	
	Vector<Container<Dice>*> t;
	Container<Container<Dice>*>& container = t;
	container.add(&dice);
	container.add(&dice_arr);
	container.add(&dice_list);
	std::cout << "\nBALLS1\n";
	(*container.get(0))->print();
	std::cout << "\nBALLS2\n";
	(*container.get(1))->print();
	std::cout << "\nBALLS3\n";
	(*container.get(2))->print();
	get_sums(&container)->print();
}


bool d_comp(Dice* d1, Dice* d2) {
	if (d1->face_count() > d2->face_count()) {
		return false;
	}
	else {
		return true;
	}
}


Vector<Vector<Sum>*>* get_sums(Container<Container<Dice>*> * vector) {
	Vector<Vector<Sum>*>* res = new Vector<Vector<Sum>*>;
	unsigned int len = vector->size();
	Vector<Sum>* temp = NULL;
	for (int i = 0; i < len; i++) {
		temp = get_sums_rec(*vector->get(i), 0);
		norm(temp);
		res->add(temp);
	}
	return res;
}

Vector<Sum>* get_sums_rec( Container<Dice>* vec, unsigned int step) {
	assert(step < vec->size());
	Vector<Sum>* cur_sum = new Vector<Sum>;
	unsigned int size = vec->get(step)->face_count();
	if (step < vec->size() - 1) {
		Vector<Sum>* this_sum = new Vector<Sum>;
		for (int i = 0; i < size; i++) {
			this_sum->add(Sum(vec->get(step)->get_face(i)->val, vec->get(step)->get_face(i)->possib));
		}
		norm(this_sum);
		Vector<Sum>* prev_sum = get_sums_rec(vec, step + 1);
		unsigned int prev_size = prev_sum->size();
		size = this_sum->size();
		for(int i = 0; i < size; i++){
			for (int j = 0; j < prev_size; j++) {
				cur_sum->add(Sum(this_sum->get(i)->sum + prev_sum->get(j)->sum, this_sum->get(i)->possib * prev_sum->get(j)->possib));
			}
		}
		delete this_sum;
		delete prev_sum;
	}
	else{
		for (int i = 0; i < size; i++) {
			cur_sum->add(Sum(vec->get(step)->get_face(i)->val, vec->get(step)->get_face(i)->possib));
		}
	}
	norm(cur_sum);
	return cur_sum;
}

void norm(Vector<Sum>* sums) {
	unsigned int size = sums->size();
	for (int i = 0; i < size-1; i++) {
		for (int j = i+1; j < size; j++) {
			if (sums->get(i)->sum == sums->get(j)->sum) {
				sums->set(Sum(sums->get(i)->sum, sums->get(i)->possib + sums->get(j)->possib), i);
				sums->del(j);
				size = sums->size();
			}
		}
	}
}
