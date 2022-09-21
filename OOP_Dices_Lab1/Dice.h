#pragma once

#include <iostream>
#include "C_Array.h"
#include <random>
#include <cassert>


class Dice
{

public:
	struct Face {
		double val;
		double possib;
		Face(double val, double possib) {
			this->val = val;
			this->possib = possib;
		}
	};
private:

	unsigned short _face_count;
	C_Array<Face*>* faces = NULL;


public:

	Dice() {
		
	}

	Dice(unsigned short face_count) {
		_face_count = face_count;
		faces = new C_Array<Face*>(_face_count);
	}

	void set_vals() {
		double possib, v;
		std::cout << "\n For each face enter value\\possibility\n";
		for (int i = 0; i < _face_count; i++) {
			std::cin >> v >> possib;
			faces->set(new Face(v, possib), i);
		}
	}

	void auto_gen(int minv, int maxv) {
		int max_possib = 100/_face_count;
		int last_possib = 100;
		int leftover_possib = 0;
		for (int i = 0; i < _face_count-1; i++) {
			int temp_possib = rand() % (max_possib + leftover_possib) + 1;
			leftover_possib = max_possib + leftover_possib - temp_possib;
			if (leftover_possib < 0) {
				leftover_possib = 0;
			}
			last_possib -= temp_possib;
			faces->set(new Face(rand() % (maxv - minv) + minv, temp_possib / 100.0), i);
		}
		faces->set(new Face(rand() % (maxv - minv) + minv, last_possib/100.0), _face_count-1);
	}

	void print() {
		for (int i = 0; i < _face_count; i++) {
			Face** temp = faces->get(i);
			std::cout << (*temp)->val << " : " << (*temp)->possib << "\n";
		}
	}

	Face* get_face(unsigned int id) {
		assert(id < faces->size());
		return (*faces->get(id));
	}

	C_Array<Face*>* get_faces() {
		return faces;
	}

	unsigned int face_count() {
		return faces->size();
	}

};

