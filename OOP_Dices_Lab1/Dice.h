#pragma once

#include <iostream>
#include "C_Array.h"
class Dice
{
private:
	struct Face {
		double val;
		double possib;
		Face(double val, double possib) {
			this->val = val;
			this->possib = possib;
		}
	};
	unsigned short _face_count;
	C_Array<Face*>* faces = NULL;


public:
	Dice(unsigned short face_count) {
		_face_count = face_count;
		faces = new C_Array<Face*>(_face_count);
	}

	void set_vals() {
		double pos, v;
		std::cout << "\n For each face enter value\\possibility\n";
		for (int i = 0; i < _face_count; i++) {
			std::cin >> v >> pos;
			faces->set(new Face(v, pos), i);
		}
	}


};

