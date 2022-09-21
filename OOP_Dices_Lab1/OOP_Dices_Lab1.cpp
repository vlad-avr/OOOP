

#include <iostream>
#include "L_List.h"
#include "Dice.h"
#include "C_Array.h"
#include "Vector.h"
#include <time.h>

struct Sum {
	double sum;
	double possib;
	Sum(double sum = 0, double possib = 0) {
		this->sum = sum;
		this->possib = possib;
	}

};

std::ostream& operator<<(std::ostream& os, Dice& dice) {
	unsigned int size = dice.face_count();
	for (int i = 0; i < size; i++) {
		os << dice.get_face(i)->val << " : "  << dice.get_face(i)->possib << "\n";
	}
	os << "\n";
	return os;
}

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

Vector<Vector<Sum>*>* get_sums(Vector<Vector<Dice>*>*);
Vector<Sum>* get_sums_rec(Vector<Dice>**, unsigned int);
void norm(Vector<Sum>*);

bool d_comp(Dice*, Dice*);

bool comp(Dice::Face** f1, Dice::Face** f2) {
	if ((*f1)->val > (*f2)->val) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	srand(time(0));
	Vector<Vector<Dice>*>* vec = new Vector<Vector<Dice>*>;
	Vector<Dice>* dices1 = new Vector<Dice>;
	dices1->append(Dice(8));
	dices1->get(0)->auto_gen(0, 10);
	dices1->append(Dice(6));
	dices1->get(1)->auto_gen(2, 7);
	dices1->append(Dice(4));
	dices1->get(2)->auto_gen(1, 4);
	dices1->print();
	dices1->insert_sort(d_comp);
	dices1->print();
	dices1->get(0)->get_faces()->insert_sort(comp);
	dices1->get(1)->get_faces()->insert_sort(comp);
	dices1->get(2)->get_faces()->insert_sort(comp);
	dices1->print();

	/*Vector<Dice>* dices2 = new Vector<Dice>;
	dices2->append(Dice(4));
	dices2->get(0)->auto_gen(0, 3);
	dices2->append(Dice(6));
	dices2->get(1)->auto_gen(2, 7);
	dices2->append(Dice(6));
	dices2->get(2)->auto_gen(1, 6);
	dices2->print();

	Vector<Dice>* dices3 = new Vector<Dice>;
	dices3->append(Dice(4));
	dices3->get(0)->auto_gen(5, 9);
	dices3->append(Dice(8));
	dices3->get(1)->auto_gen(1, 8);
	dices3->print();
	vec->append(dices1);
	vec->append(dices2);
	vec->append(dices3);
	get_sums(vec)->print();*/
	/*L_List<Dice>* list = new L_List<Dice>;
	list->add(Dice(4));
	list->get(0)->data.auto_gen(1, 4);
	list->add(Dice(6));
	list->get(1)->data.auto_gen(1, 6);
	list->add(Dice(12));
	list->get(2)->data.auto_gen(1, 12);
	list->print();
	list->del(2);
	list->print();*/

/*	C_Array<Dice>* arr = new C_Array<Dice>(3);
	arr->set(Dice(4), 0);
	arr->get(0)->auto_gen(1, 4);
	arr->set(Dice(6), 1);
	arr->get(1)->auto_gen(1, 6);
	arr->set(Dice(8), 2);
	arr->get(2)->auto_gen(1, 8);
	arr->print();
	arr->del(1);
	arr->print();*/
}


bool d_comp(Dice* d1, Dice* d2) {
	if (d1->face_count() > d2->face_count()) {
		return false;
	}
	else {
		return true;
	}
}


Vector<Vector<Sum>*>* get_sums(Vector<Vector<Dice>*> * vector) {
	Vector<Vector<Sum>*>* res = new Vector<Vector<Sum>*>;
	unsigned int len = vector->size();
	Vector<Sum>* temp = NULL;
	for (int i = 0; i < len; i++) {
		temp = get_sums_rec(vector->get(i), 0);
		norm(temp);
		res->append(temp);
	}
	return res;
}

Vector<Sum>* get_sums_rec( Vector<Dice>** vec, unsigned int step) {
	assert(step < (*vec)->size());
	Vector<Sum>* cur_sum = new Vector<Sum>;
	unsigned int size = (*vec)->get(step)->face_count();
	if (step < (*vec)->size() - 1) {
		Vector<Sum>* this_sum = new Vector<Sum>;
		for (int i = 0; i < size; i++) {
			this_sum->append(Sum((*vec)->get(step)->get_face(i)->val, (*vec)->get(step)->get_face(i)->possib));
		}
		norm(this_sum);
		Vector<Sum>* prev_sum = get_sums_rec(vec, step + 1);
		unsigned int prev_size = prev_sum->size();
		size = this_sum->size();
		for(int i = 0; i < size; i++){
			for (int j = 0; j < prev_size; j++) {
				cur_sum->append(Sum(this_sum->get(i)->sum + prev_sum->get(j)->sum, this_sum->get(i)->possib * prev_sum->get(j)->possib));
			}
		}
		delete this_sum;
		delete prev_sum;
	}
	else{
		for (int i = 0; i < size; i++) {
			cur_sum->append(Sum((*vec)->get(step)->get_face(i)->val, (*vec)->get(step)->get_face(i)->possib));
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
