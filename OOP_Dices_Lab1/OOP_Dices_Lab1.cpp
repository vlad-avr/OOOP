

#include <iostream>
#include "L_List.h"
#include "Dice.h"
#include "C_Array.h"
#include "Vector.h"
#include <time.h>


std::ostream& operator<<(std::ostream& os, Dice& dice) {
	unsigned int size = dice.face_count();
	for (int i = 0; i < size; i++) {
		os << dice.get_face(i)->val << " : "  << dice.get_face(i)->possib << "\n";
	}
	os << "\n";
	return os;
}


struct Sum {
	double sum;
	double possib;
	Sum(double sum = 0, double possib = 0) {
		this->sum = sum;
		this->possib = possib;
	}
};

int main()
{
	srand(time(0));
	/*Vector<Dice>* dices = new Vector<Dice>;
	dices->append(Dice(4));
	dices->get(0)->auto_gen(0, 10);
	dices->append(Dice(6));
	dices->get(1)->auto_gen(0, 10);
	dices->append(Dice(8));
	dices->get(2)->auto_gen(4, 8);
	dices->append(Dice(20));
	dices->get(3)->auto_gen(0, 5);
	dices->print();
	dices->set(Dice(12), 2);
	dices->get(2)->auto_gen(1, 12);
	dices->print();
	dices->del(3);
	dices->print();*/
	L_List<Dice>* list = new L_List<Dice>;
	list->add(Dice(4));
	list->get(0)->data.auto_gen(1, 4);
	list->add(Dice(6));
	list->get(1)->data.auto_gen(1, 6);
	list->add(Dice(12));
	list->get(2)->data.auto_gen(1, 12);
	list->print();
	list->del(2);
	list->print();

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

Vector<Sum>* get_sums(Vector<Vector<Dice>*> * vector) {
	Vector<Sum>* res = new Vector<Sum>;
	
}