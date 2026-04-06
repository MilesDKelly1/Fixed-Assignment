#include "StudentList.h"
#include "StudentInfo.h"
#include <iostream>
using namespace std;

StudentList::node::node(StudentInfo* d, node* n) : data(d), next(n)
{
}

StudentList::iterator::iterator(node* start) : current(start)
{
}

bool StudentList::iterator::hascurrent() const
{
	return current != nullptr;
}

void StudentList::iterator::next()
{
	if (current) {
		current = current->next;
	}
}

StudentInfo*& StudentList::iterator::data() const
{
	if (!current) {
		throw exceptionhandler("iterator out of bounds (StudentList::iterator::data)");
	}
	return current->data;
}

StudentList::StudentList() : head(nullptr), tail(nullptr), sized(0)
{
}

StudentList::~StudentList()
{
	clear(false);
}

int StudentList::size() const
{
	return sized;
}

StudentList::iterator StudentList::begin() const
{
	return iterator(head);
}

void StudentList::push_front(StudentInfo* ptr)
{
	if (!ptr) {
		return;
	}

	node* n = new node(ptr, head);
	head = n;

	if (!tail) {
		tail = head;
	}

	++sized;
}

void StudentList::push_back(StudentInfo* ptr)
{
	if (!ptr) {
		return;
	}

	node* n = new node(ptr);

	if (!head) {
		head = tail = n;
	}
	else {
		tail->next = n;
		tail = n;
	}

	++sized;
}

StudentInfo* StudentList::at(int index) const
{
	if (index < 0 || index >= sized) {
		throw exceptionhandler("Index out of bounds (itemslist::at)");
	}

	node* cur = head;
	for (int i = 0; i < index; ++i) {
		cur = cur->next;
	}

	return cur->data;
}

int StudentList::index_of_name(const string& name) const
{
	int i = 0;
	for (iterator it = begin(); it.hascurrent(); it.next(), ++i) {
		if (it.data() && it.data()->getName() == name) {
			return i;
		}
	}
	return -1;
}

bool StudentList::remove_at(int index, bool deleteItem)
{
	if (index < 0 || index >= sized) {
		return false;
	}

	node* prev = nullptr;
	node* cur = head;

	for (int i = 0; i < index; ++i) {
		prev = cur;
		cur = cur->next;
	}

	if (prev) {
		prev->next = cur->next;
	}
	else {
		head = cur->next;
	}

	if (cur == tail) {
		tail = prev;
	}

	if (deleteItem && cur->data) {
		delete cur->data;
		cur->data = nullptr;
	}

	delete cur;
	--sized;

	if (sized == 0) {
		head = tail = nullptr;
	}

	return true;
}

void StudentList::clear(bool deleteItems)
{
	while (head) {
		node* next = head->next;

		if (deleteItems && head->data) {
			delete head->data;
			head->data = nullptr;
		}

		delete head;
		head = next;
	}

	tail = nullptr;
	sized = 0;
}