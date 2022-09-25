#pragma once
#include <iostream>
template<typename T>
class Container
{
public:
	friend std::ostream& operator<<(std::ostream& os, Container<T>& cont) {
		cont.print();
		os << "\n";
		return os;
	}
	virtual void del(unsigned int ID) { std::cout << "\nERROR: Abstract class function call, invalid function parameters\n"; }
	virtual void print(){ std::cout << "\nERROR: Abstract class function call, invalid function parameters\n"; }
	virtual T* get(unsigned int ID) { std::cout << "\nERROR: Abstract class function call, invalid function parameters\n"; return NULL; }
	virtual void set(T val, unsigned int id){ std::cout << "\nERROR: Abstract class function call, invalid function parameters\n"; }
	virtual void add(T val){ std::cout << "\nERROR: Abstract class function call, invalid function parameters\n"; }
	virtual void qsort(bool (*comp)(T*, T*)) { std::cout << "\nERROR: Abstract class function call, invalid function parameters\n"; }
	virtual void msort(bool (*comp)(T*, T*)) { std::cout << "\nERROR: Abstract class function call, invalid function parameters\n"; }
	virtual void inserrt_sort(bool (*comp)(T*, T*)) { std::cout << "\nERROR: Abstract class function call, invalid function parameters\n"; }
	virtual void custom_sort(void (*sort)(T*, int, bool (*)(T*, T*)), bool (*comp)(T*, T*)) { std::cout << "\nERROR: Abstract class function call, invalid function parameters\n OR function call in L_List class (impossible to override with L_List custom_sort() functios dur to structure incompatibility\n"; }
	virtual unsigned int size() { std::cout << "\nERROR: Abstract class function call, invalid function parameters\n"; return 0; };

};

