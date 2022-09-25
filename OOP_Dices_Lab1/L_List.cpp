#include "L_List.h"
#include "doctest.h"

TEST_CASE("Create array, add, set, get and delete element") {
	L_List<int> arr;
	arr.add(0);
	arr.add(1);
	arr.add(2);
	CHECK(*(arr.get(0)) == 0);
	CHECK(*(arr.get(1)) == 1);
	arr.set(3, 0);
	CHECK(*(arr.get(0)) == 3);
	arr.del(1);
	CHECK(arr.size() == 2);
	CHECK(*(arr.get(1)) == 2);
}

bool num_comp(int* n1, int* n2) {
	if (*n1 >= *n2) {
		return true;
	}
	else
		return false;
}

L_List<int>::Node* get_tail(L_List<int>::Node* cur)
{
	while (cur && cur->next) {
		cur = cur->next;
	}
	return cur;
}

L_List<int>::Node* part(L_List<int>::Node* head, L_List<int>::Node* end, L_List<int>::Node** new_head, L_List<int>::Node** new_end, bool (*comp)(int*, int*))
{
	L_List<int>::Node* pivot = end;
	L_List<int>::Node* prev = NULL, * cur = head, * tail = pivot;

	while (cur != pivot) {
		if (comp(&(cur->data), &(pivot->data))) {
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
			L_List<int>::Node* tmp = cur->next;
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

L_List<int>::Node* qsort_rec(L_List<int>::Node* head, L_List<int>::Node* end, bool (*comp)(int*, int*))
{
	if (!head || head == end) {
		return head;
	}

	L_List<int>::Node* new_head = NULL, * new_end = NULL;

	L_List<int>::Node* pivot = part(head, end, &new_head, &new_end, comp);

	if (new_head != pivot) {
		L_List<int>::Node* tmp = new_head;
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

L_List<int>::Node* quicksort(L_List<int>::Node* beg, bool (*cmp)(int*, int*)) {
	L_List<int>::Node* temp = beg;
	while (temp->next) {
		temp = temp->next;
	}
	beg = qsort_rec(beg, temp, cmp);
	return beg;
}

TEST_CASE("Sorting") {
	L_List<int> arr;
	for (int i = 0; i < 10; i++) {
		arr.add(10 - i);
	}
	arr.insert_sort(num_comp);
	CHECK(*(arr.get(0)) == 10);
	CHECK(*(arr.get(arr.size() - 1)) == 1);
	for (int i = 0; i < 10; i++) {
		arr.set(10 - i, i);
	}
	arr.qsort(num_comp);
	CHECK(*(arr.get(0)) == 10);
	CHECK(*(arr.get(arr.size() - 1)) == 1);
	for (int i = 0; i < 10; i++) {
		arr.set(10 - i, i);
	}
	arr.msort(num_comp);
	CHECK(*(arr.get(0)) == 10);
	CHECK(*(arr.get(arr.size() - 1)) == 1);
	for (int i = 0; i < 10; i++) {
		arr.set(10- i, i);
	}
	arr.custom_sort(quicksort, num_comp);
	CHECK(*(arr.get(0)) == 10);
	CHECK(*(arr.get(arr.size() - 1)) == 1);

}