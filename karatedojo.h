#pragma once
#include "StudentInfo.h"
#include "FinancialSystem.h"
#include "inputvalidator.h"

#include <string>
using namespace std;

class karatedojo : public StudentInfo {
private:
	int registration_size;
	StudentInfo::StudentInf inventory[100]; //idk man, someone else had this and im trying my best
	int capacity;
	double maxvalue;
	BeltRank belt;
	BeltStripes stripe;
	FinancialSystem finsys;
	inputvalidator inputsys;

public:
	karatedojo();
	~karatedojo();

	void introbanner();
	void menu();
	void displayregistration();
	void extramenu(); //if needed
	//void tracksales(); //could turn into checking balace for the month

	void addStudent();
	void savereport();

	int getregistrationsize() const;
	
	virtual void print() const override;

	void additemtodirect(const StudentInfo::StudentInf& newStudent);
};