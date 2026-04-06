#include "StudentInfo.h"
#include <iostream>
#include <string>
using namespace std;

StudentInfo::StudentInfo():Name(""), Age(6), IsReturning(false),
MonthsEnrolled(0), Rank(White), Stripes(zero), NeedsGear(false), ECon("") {

}
StudentInfo::StudentInfo(const string& name, int age, bool isReturning,
	int monthsEnrolled, BeltRank rank, BeltStripes stripes, bool needsGear, const string& contact) 
	: Name(name), Age(age), IsReturning(isReturning),
	MonthsEnrolled(monthsEnrolled), Rank(rank), Stripes(stripes), NeedsGear(needsGear), ECon(contact) {

}

StudentInfo::~StudentInfo() {

}

void StudentInfo::setName(const string& name) {
	Name = name;
}
const string& StudentInfo::getName() const {
	return Name;
}

void StudentInfo::setAge(int age) {
	Age = age;
}
int StudentInfo::getAge() const {
	return Age;
}

void StudentInfo::setMonths(int monthsEnrolled) {
	MonthsEnrolled = monthsEnrolled;
}
int StudentInfo::getMonths() const {
	return MonthsEnrolled;
}

void StudentInfo::setReturning(bool isReturning) {
	IsReturning = isReturning;
}
bool StudentInfo::getReturning() const {
	return IsReturning;
}

void StudentInfo::setRank(BeltRank rank) {
	Rank = rank;
}
StudentInfo::BeltRank StudentInfo::getRank() const {
	return Rank;
}

void StudentInfo::setStripes(BeltStripes stripes) {
	Stripes = stripes;
}
StudentInfo::BeltStripes StudentInfo::getStripes() const {
	return Stripes;
}

void StudentInfo::setGear(bool needGear) {
	NeedsGear = needGear;
}
bool StudentInfo::getGear() const {
	return NeedsGear;
}

void StudentInfo::setContact(const string& econtact) {
	ECon = econtact;
}
const string& StudentInfo::getContact() const {
	return ECon;
}

const char* StudentInfo::BeltRankstring(BeltRank r) {
	if (r == White)
		return "White";
	else if (r == Yellow)
		return "Yellow";
	else if (r == Green)
		return "Green";
	else if (r == Blue)
		return "Blue";
	else if (r == Purple)
		return "Purple";
	else if (r == Brown)
		return "Brown";
	else if (r == Black)
		return "Black";
	else
		return "White";
}

const char* StudentInfo::BeltStripesstring(BeltStripes s) {
	if (s == zero)
		return "Zero";
	else if (s == one)
		return "One";
	else if (s == two)
		return "Two";
	else if (s == three)
		return "Three";
	else if (s == four)
		return "Four";
	else
		return "Zero";
}

void StudentInfo::print() const {
	cout << "Name: " << Name << endl;
	cout << "Age: " << Age << endl;
	cout << "Returning Student? y/n: " << IsReturning << endl;
	cout << "Months Enrolled for: " << MonthsEnrolled << endl;
	cout << "Belt Rank: " << Rank << endl;
	cout << "Belt Stripes: " << Stripes << endl;
	cout << "Need Gear? y/n: " << NeedsGear << endl;
	cout << "Emergency Contact: " << ECon << endl;
}

void StudentInfo::toStream(ostream& output) const {
	output << "Name: " << getName() 
		<< " | Age: " << getAge()
		<< " | Returning Student: " << getReturning()
		<< " | Months Enrolled: " << getMonths()
		<< " | Belt Rank: " << getRank()
		<< " | Belt Stripes: " << getStripes() //could get rid of this one, this is checked by months enrolled and belt rank
		<< " | Needed Gear: " << getGear()
		<< " | Emergency Contact: " << getContact();
}

ostream& operator<<(ostream& output, const StudentInfo& person) {
	person.toStream(output);
	return output;
}