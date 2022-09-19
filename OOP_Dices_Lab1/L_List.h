#pragma once

#include <iostream>

template<typename T>
class L_List
{
private:
	struct Node {
	public:

		Node* next;
		T data;
		Node(T data, Node* next = NULL) {
			this->data = data;
			this->next = next;
		}
	};

	Node* beg;
	Node* end;

public:
	L_List() {
		beg = NULL;
		end = beg;
	}

	void add(T val) {
		if (!beg) {
			beg = new Node(val);
			end = beg;
		}
		else {
			end->next = new Node(val);
			end = end->next;
		}
	}

	void set(unsigned int ID, T val) {
		Node* temp = beg;
		while (ID >= 0) {
			if (!temp) {
				return;
			}
			else {
				temp = temp->next;
			}
		}
		temp->data = val;
	}


};

