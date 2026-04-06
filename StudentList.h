#pragma once
#include <string>
#include "exceptionhandler.h"
using namespace std;
class StudentInfo;

class StudentList
{
private:
	struct node
	{
		StudentInfo* data;
		node* next;

		node(StudentInfo*, node* = nullptr);
	};

public:
	class iterator
	{
	public:
		iterator(node* = nullptr);
		bool hascurrent() const;
		void next();

		StudentInfo*& data() const;

	private:
		node* current;
	};

	StudentList();
	~StudentList();

	int size() const;
	iterator begin() const;

	void push_back(StudentInfo*);
	void push_front(StudentInfo*);

	StudentInfo* at(int) const;


	int index_of_name(const string&) const;

	bool remove_at(int, bool);

	void clear(bool);

private:
	node* head;
	node* tail;
	int sized;
};