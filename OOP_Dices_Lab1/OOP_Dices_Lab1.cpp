

#include <iostream>
#include "L_List.h"
#include "Dice.h"
#include "C_Array.h"
#include "Vector.h"
#include <time.h>

void print(Vector<Dice>*);

int main()
{
	srand(time(0));
	Vector<Dice>* dices = new Vector<Dice>;
	dices->append(Dice(4));
	dices->get(0)->auto_gen(0, 10);
	dices->append(Dice(6));
	dices->get(1)->auto_gen(0, 10);
	dices->append(Dice(8));
	dices->get(2)->auto_gen(4, 8);
	dices->append(Dice(20));
	dices->get(3)->auto_gen(0, 5);
	print(dices);
}

void print(Vector<Dice>* Dices) {
	unsigned int size = Dices->size();
	for (int i = 0; i < size; i++) {
		Dices->get(i)->print();
		std::cout << std::endl;
	}
}