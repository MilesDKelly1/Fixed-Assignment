#include "DojoManager.h"
#include <iostream>
using namespace std;

DojoManager::DojoManager() : student_arr()
{
}

DojoManager::~DojoManager()
{
	clear();
}

int DojoManager::getsize() const
{
	return static_cast<int>(student_arr.size());
}

int DojoManager::getcapacity() const
{
	return getsize();
}


void DojoManager::add(StudentInfo* ptr) {
	*this += ptr;
}

bool DojoManager::remove(int index) {
	const int oldsize = getsize();
	*this -= index;
	return getsize() != oldsize;
}
void DojoManager::clear() {
	student_arr.clear(true);
}

StudentInfo* DojoManager::getind(int index) const {
	return student_arr.at(index);
}

StudentInfo* DojoManager::operator[](int index) const {
	if (index < 0 || index >= getsize()) {
		throw exceptionhandler("Index out of bounds (DojoManager::operator[])");
	}
	return getind(index);
}

DojoManager& DojoManager::operator+=(StudentInfo* ptr) {
	if (!ptr) {
		return *this;
	}
	student_arr.push_back(ptr);
	return *this;
}

DojoManager& DojoManager::operator-=(int index) {
	if (index < 0 || index >= getsize()) {
		throw exceptionhandler("Index out of bounds (DojoManager::operator-=)");
	}
	if (!student_arr.remove_at(index, true)) {
		throw exceptionhandler("Index out of bounds (DojoManager::operator-=)");
	}
	return *this;
}

void DojoManager::printall() const {
	int i = 0;

	for (StudentList::iterator it = student_arr.begin(); it.hascurrent(); it.next(), ++i) {
		if (it.data()) {
			cout << i << ". Student value: " << it.data()->getvalue() << endl;
			it.data()->print();
		}
	}
}

int DojoManager::seqsearch(const string& name) const {
	for (int i = 0; i < getsize(); ++i) {
		if (student_arr.at(i) && student_arr.at(i)->getName() == name) {
			return i;
		}
	}
	return -1;
}

void DojoManager::bubblesort() {
	const int n = getsize();
	if (n <= 1) {
		return;
	}
	for (int pass = 0; pass < n - 1; ++pass) {
		bool swapped = false;
		for (int i = 0; i < n - 1 - pass; ++i) {
			string left;
			if (student_arr.at(i)) {
				left = student_arr.at(i)->getName();
			}
			else {
				left = "";
			}
			string right;
			if (student_arr.at(i + 1)) {
				right = student_arr.at(i + 1)->getName();
			}
			else {
				right = "";
			}
			if (left > right) {
				StudentList::iterator it = student_arr.begin();
				for (int k = 0; k < i; ++k) it.next();
				StudentInfo*& a = it.data();
				it.next();
				StudentInfo*& b = it.data();

				StudentInfo* tmp = a;
				a = b;
				b = tmp;

				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
	}
}

int DojoManager::binsearch(const string& name) {
	bubblesort();
	int low = 0;
	int high = getsize() - 1;
	while (low <= high) {
		const int mid = low + (high - low) / 2;
		string midname;
		if (student_arr.at(mid)) {
			midname = student_arr.at(mid)->getName();
		}
		else {
			midname = "";
		}
		if (midname == name) {
			return mid;
		}
		if (midname < name) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	return -1;
}

double DojoManager::totalvalue() const {
	return totalvalue_rec(0);
}

double DojoManager::totalvalue_rec(StudentList::iterator it) const
{
	if (!it.hascurrent()) {
		return 0.0;
	}

	StudentInfo* cur = it.data();
	double current = 0.0;
	if (cur) {
		current = cur->getvalue();
	}
	else {
		current = 0.0;
	}

	it.next();
	return current + totalvalue_rec(it);
}