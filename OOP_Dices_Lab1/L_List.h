#pragma once

#include <iostream>
#include "Container.h"

template<typename T>
class L_List : public Container<T>
{
public:
	struct Node {
	public:

		Node* next;
		T data;
		Node(T data, Node* next = NULL) {
			this->data = data;
			this->next = next;
		}
	};


private:


	Node* beg;
	Node* end;
	Node* sort_list;
	unsigned int _size;
	void sorted_insert(bool (*comp)(T*, T*), Node* node) {
		if (!sort_list || !comp(&(sort_list->data), &(node->data))) {
			node->next = sort_list;
			sort_list = node;
		}
		else
		{
			Node* current = sort_list;
			while (current->next && comp(&(current->next->data), &(node->data)))
			{
				current = current->next;
			}
			node->next = current->next;
			current->next = node;
		}
	}

	Node* get_tail(Node* cur)
	{
		while (cur && cur->next) {
			cur = cur->next;
		}
		return cur;
	}

	Node* part(Node* head, Node* end, Node** new_head, Node** new_end, bool (*comp)(T*, T*))
	{
		Node* pivot = end;
		Node* prev = NULL, * cur = head, * tail = pivot;

		while (cur != pivot) {
			if (comp(&(cur->data),&(pivot->data))) {
				if (!(*new_head)) {
					(*new_head) = cur;
				}

				prev = cur;
				cur = cur->next;
			}
			else
			{
				if (prev) {
					prev->next = cur->next;
				}
				Node* tmp = cur->next;
				cur->next = NULL;
				tail->next = cur;
				tail = cur;
				cur = tmp;
			}
		}

		if ((*new_head) == NULL) {
			(*new_head) = pivot;
		}

		(*new_end) = tail;

		return pivot;
	}

	Node* qsort_rec(Node* head, Node* end, bool (*comp)(T*, T*))
	{
		if (!head || head == end) {
			return head;
		}

		Node* new_head = NULL, * new_end = NULL;

		Node* pivot = part(head, end, &new_head, &new_end, comp);

		if (new_head != pivot) {
			Node* tmp = new_head;
			while (tmp->next != pivot) {
				tmp = tmp->next;
			}
			tmp->next = NULL;

			new_head = qsort_rec(new_head, tmp, comp);
			tmp = get_tail(new_head);
			tmp->next = pivot;
		}
		pivot->next = qsort_rec(pivot->next, new_end, comp);

		return new_head;
	}



	void get_end() {
		Node* t = beg;
		while (t->next) {
			t = t->next;
		}
		end = t;
	}

	void split(Node* source, Node** frontRef, Node** backRef)
	{
		Node* fast;
		Node* slow;
		slow = source;
		fast = source->next;

		while (fast) {
			fast = fast->next;
			if (fast) {
				slow = slow->next;
				fast = fast->next;
			}
		}

		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}

	Node* sorted_merge(Node* a, Node* b, bool (*comp)(T*, T*))
	{
		Node* result = NULL;

		if (!a) {
			return b;
		}
		else if (!b) {
			return a;
		}

		if (comp(&(a->data), &(b->data))) {
			result = a;
			result->next = sorted_merge(a->next, b, comp);
		}
		else {
			result = b;
			result->next = sorted_merge(a, b->next,comp);
		}
		return result;
	}

	void merge_sort(Node** headRef, bool (*comp)(T*, T*))
	{
		Node* head = *headRef;
		Node* a;
		Node* b;

		if (!head || !head->next) {
			return;
		}

		split(head, &a, &b);
		merge_sort(&a, comp);
		merge_sort(&b, comp);

		*headRef = sorted_merge(a, b, comp);
	}

	Node* get_node(unsigned int id) {
		Node* temp = beg;
		while (id > 0 && temp) {
			temp = temp->next;
			id--;
		}
		return temp;
	}

public:
	L_List() {
		beg = NULL;
		end = beg;
	}

	unsigned int size() {
		Node* temp = beg;
		int i = 1;
		while (temp != end) {
			temp = temp->next;
			i++;
		}
		return i;
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
	
	void set( T val, unsigned int ID ) {
		Node* temp = get_node(ID);
		if (temp) {
			temp->data = val;
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
			Node* temp = get_node(id - 1);
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

	T* get(unsigned int id) {
		Node* temp = beg;
		while (id > 0 && temp) {
			temp = temp->next;
			id--;
		}
		return &temp->data;
	}

	void insert_sort(bool (*comp)(T*, T*)) {
		sort_list = NULL;
		Node* cur = beg;
		while (cur) {
			Node* next = cur->next;
			sorted_insert(comp, cur);
			cur = next;
		}
		beg = sort_list;
		get_end();
	}

	void qsort(bool (*comp)(T*, T*)) {
		beg = qsort_rec(beg, end, comp);
		get_end();
	}

	void msort(bool (*comp)(T*, T*)) {
		merge_sort(&beg, comp);
		get_end();
	}

	void custom_sort(Node* (*sort)(Node*, bool (*)(T*, T*)), bool (*comp)(T*, T*)) {
		beg = sort(beg, comp);
		get_end(); 
	}

	void gen_rand(unsigned int num, T* get_rand_vals()) {
		unsigned int _size = size();
		if (num < _size) {
			for (int i = 0; i < num; i++) {
				set(*(get_rand_vals()), i);
			}
		}
		else {
			unsigned int extra = num - _size;
			for (int i = 0; i < _size; i++) {
				set(*(get_rand_vals()), i);
			}
			for (int i = 0; i < extra; i++) {
				add(*(get_rand_vals()));
			}
		}
	}


};

