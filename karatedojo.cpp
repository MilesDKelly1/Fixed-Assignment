//backbone of the code
#include "karatedojo.h"
#include "StudentInfo.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;

karatedojo::karatedojo() {
	registration_size = 0;
	maxvalue = 0.0;
	for (int i = 0; i < 100; ++i) {
		inventory[i] = {};
	}
}
karatedojo::~karatedojo(){}

void karatedojo::introbanner() //Welcome intro banner
{
	cout << "Welcome to the karate dojo!" << endl;
}

void karatedojo::menu() //Menu
{
	int opt;
	do {
		cout << "Menu:" << endl;
		cout << "1. Display Registration" << endl; ///show registration
		cout << "2. Add Student" << endl;
		cout << "3. Save Registration" << endl;
		cout << "4. Track Students" << endl; //search students
		cout << "5. Extra Functions" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> opt;
		switch (opt) {
		case 1:
			displayregistration();
			break;
		case 5:
			extramenu();
			break;
		case 6:
			break;
		default:
			cout << "Invalid option. Please try again." << endl;
			break;
		}
	} while (opt != 6);
}

void karatedojo::extramenu() //can be expanded!
{
	//remove student, balance removal
	int opt;
	do {
		cout << "Extra Menu Function:" << endl;
		cout << "1. Remove Student (index)" << endl;
		cout << "2. Return to main menu" << endl;
		cin >> opt;
		switch (opt) {
		case 1:
			break;
		case 2:
			break;
		default:
			cout << "Invalid option. Please try again." << endl;
			break;
		}
	} while (opt != 2);
}

void karatedojo::addStudent() { //adding new student function
	if (registration_size >= 100) {
		cout << "Registration is full. Cannot add more students." << endl;
		return;
	}
	StudentInf newStudent;
	int opt;
	cout << "Registration Form: " << endl;
	newStudent.name = inputsys.inputname("Enter the student's name: ");
	newStudent.age = inputsys.inputint("Enter the age (6-90): ");
	if (newStudent.age < 6 || newStudent.age > 90) {
		newStudent.age = inputsys.inputint("Enter a different age please: ");
	}
	newStudent.isReturning = inputsys.inputbool("Is a New Student? (true or false): ");
	if (newStudent.isReturning = true) {
		newStudent.monthsEnrolled = 0;
		newStudent.rank = White;
		newStudent.stripes = zero;
	}
	newStudent.monthsEnrolled = inputsys.inputint("Months Enrolled? 1 or greater: ");
	if (newStudent.monthsEnrolled <= 5) {
		newStudent.rank = White;
		//work on stripes system
		newStudent.stripes = two;
	}
	else if (newStudent.monthsEnrolled > 6 && newStudent.monthsEnrolled <= 11) {
		newStudent.rank = Yellow;
		newStudent.stripes = two;
	}
	else if (newStudent.monthsEnrolled > 12 && newStudent.monthsEnrolled <= 17) {
		newStudent.rank = Green;
		newStudent.stripes = two;
	}
	else if (newStudent.monthsEnrolled > 18 && newStudent.monthsEnrolled <= 23) {
		newStudent.rank = Blue;
		newStudent.stripes = two;
	}
	else if (newStudent.monthsEnrolled > 24 && newStudent.monthsEnrolled <= 29) {
		newStudent.rank = Purple;
		newStudent.stripes = two;
	}
	else if (newStudent.monthsEnrolled > 30 && newStudent.monthsEnrolled <= 35) {
		newStudent.rank = Brown;
		newStudent.stripes = two;
	}
	else if (newStudent.monthsEnrolled >= 36) {
		newStudent.rank = Black;
		newStudent.stripes = zero;
	}
	else {
		newStudent.rank = White;
		newStudent.stripes = zero;
	}
	newStudent.needsGear = inputsys.inputbool("Needs? (true or false): ");
	newStudent.Contact = inputsys.inputname("Emergency Contact: ");

	inventory[registration_size] = newStudent;
	registration_size++;
	cout << "Student has been added" << endl;
}

void karatedojo::displayregistration() //Displaying the reg with setw functions
{
	if (registration_size == 0) {
		cout << "The registration is empty" << endl;
		return;
	}
	cout << fixed << setprecision(2);
	cout << left << setw(20) << "Name" << setw(15) << "Age"
		<< setw(20) << "Belt Rank" << setw(15) << "Belt Stripes"
		<< setw(10) << "Emergency Contact" << endl;

	for (int i = 0; i < registration_size; ++i) {
		string belt;
		string stripe;

		if (inventory[i].rank == StudentInfo::White) {
			belt = "White";
		}
		else if (inventory[i].rank == StudentInfo::Yellow) {
			belt = "Yellow";
		}
		else if (inventory[i].rank == StudentInfo::Green) {
			belt = "Green";
		}
		else if (inventory[i].rank == StudentInfo::Blue) {
			belt = "Blue";
		}
		else if (inventory[i].rank == StudentInfo::Purple) {
			belt = "Purple";
		}
		else if (inventory[i].rank == StudentInfo::Brown) {
			belt = "Brown";
		}
		else if (inventory[i].rank == StudentInfo::Black) {
			belt = "Black";
		}
		else {
			belt = "Unknown";
		}

		if (inventory[i].stripes == StudentInfo::zero) {
			stripe = "zero";
		}
		else if (inventory[i].stripes == StudentInfo::one) {
			stripe = "one";
		}
		else if (inventory[i].stripes == StudentInfo::two) {
			stripe = "two";
		}
		else if (inventory[i].stripes == StudentInfo::three) {
			stripe = "three";
		}
		else if (inventory[i].stripes == StudentInfo::four) {
			stripe = "four";
		}
		else {
			stripe = "Unknown";
		}
		cout << left << setw(20) << inventory[i].name
			<< setw(15) << inventory[i].age << setw(20) << belt
			<< setw(15) << stripe << setw(10) << inventory[i].Contact;
	}
}

void karatedojo::savereport() { //saving report to text file
	if (registration_size == 0) {
		cout << "The registration is empty. No report to save." << endl;
		return;
	}
	ofstream reportfile("report.txt");
	if (!reportfile) {
		cout << "error creating the file." << endl;
		return;
	}
	reportfile << "Registration Report" << endl;
	reportfile << fixed << setprecision(2);
	reportfile << left << setw(20) << "Name" << setw(15) << "Age"
		<< setw(20) << "Belt Rank" << setw(15) << "Belt Stripes"
		<< setw(10) << "Emergency Contact" << endl;
	for (int i = 0; i < registration_size; ++i) {
		string belt;
		string stripe;

		if (inventory[i].rank == StudentInfo::White) {
			belt = "White";
		}
		else if (inventory[i].rank == StudentInfo::Yellow) {
			belt = "Yellow";
		}
		else if (inventory[i].rank == StudentInfo::Green) {
			belt = "Green";
		}
		else if (inventory[i].rank == StudentInfo::Blue) {
			belt = "Blue";
		}
		else if (inventory[i].rank == StudentInfo::Purple) {
			belt = "Purple";
		}
		else if (inventory[i].rank == StudentInfo::Brown) {
			belt = "Brown";
		}
		else if (inventory[i].rank == StudentInfo::Black) {
			belt = "Black";
		}
		else {
			belt = "Unknown";
		}

		if (inventory[i].stripes == StudentInfo::zero) {
			stripe = "zero";
		}
		else if (inventory[i].stripes == StudentInfo::one) {
			stripe = "one";
		}
		else if (inventory[i].stripes == StudentInfo::two) {
			stripe = "two";
		}
		else if (inventory[i].stripes == StudentInfo::three) {
			stripe = "three";
		}
		else if (inventory[i].stripes == StudentInfo::four) {
			stripe = "four";
		}
		else {
			stripe = "Unknown";
		}
		cout << left << setw(20) << inventory[i].name
			<< setw(15) << inventory[i].age << setw(20) << belt
			<< setw(15) << stripe << setw(10) << inventory[i].Contact;
	}
	reportfile << endl;
	reportfile.close();
	cout << "Report created successfully." << endl;
	cout << "Report saved to report.txt" << endl;
}


void karatedojo::print() const {
	cout << "Karate registration size: " << registration_size << endl;
}

//Unit testing related functions
int karatedojo::getregistrationsize() const {
	return registration_size;
}

void karatedojo::additemtodirect(const StudentInf& newStudent) {
	if (registration_size >= 100) {
		cout << "Inventory is full. Cannot add more items." << endl;
		return;
	}
	inventory[registration_size] = newStudent;
	registration_size++;
}