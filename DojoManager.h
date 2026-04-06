#pragma once
#include "StudentInfo.h"
#include"exceptionhandler.h"
#include"StudentList.h"
#include<vector>
#include"dynamic.h"
#include<string>
using namespace std;
class DojoManager
{
public:
	DojoManager();
	~DojoManager();

	int getsize() const;
	int getcapacity() const;

	void add(StudentInfo*);
	bool remove(int);
	void clear();

	StudentInfo* getind(int) const;
	void printall() const;

	StudentInfo* operator[](int) const;
	DojoManager& operator+=(StudentInfo*);
	DojoManager& operator-=(int);

	double totalvalue() const;

	int seqsearch(const string&) const;
	void bubblesort();
	int binsearch(const string&);
private:
	StudentList student_arr;

	double totalvalue_rec(StudentList::iterator) const;
};