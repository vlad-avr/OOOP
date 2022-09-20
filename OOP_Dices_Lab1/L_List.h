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
		Node* temp = get(ID);
		if (temp) {
			temp = val;
		}
	}

	void print() {
		Node* temp = beg;
		while (temp != end) {
			std::cout << temp->data << "\n";
			temp = temp->next;
		}
		std::cout << temp->data << "\n";
	}

	void del(unsigned int id) {
		Node* temp = NULL;
		if (id == 0) {
			if (beg == end) {
				temp = beg;
				beg = NULL;
				delete temp;
			}
			else {
				temp = beg;
				beg = beg->next;
				delete temp;
			}
		}
		else {
			Node* temp = get(id - 1);
			if (temp && temp->next) {
				if (temp->next == end) {
					end = temp;
				}
				Node* t = temp->next;
				temp->next = temp->next->next;
				temp = temp->next;
				delete t;
			}
		}
	}

	Node* get(unsigned int id) {
		Node* temp = beg;
		while (id > 0 && temp) {
			temp = temp->next;
			id--;
		}
		return temp;
	}


};

