//All input related functions and their validation functions
#include "inputvalidator.h"
#include <iostream>
#include <string>
using namespace std;

//function to mainly input string, int, and bool
string inputvalidator::inputname(const string& prompt) {
	string name;
	bool valid = false;
	while (!valid) {
		cout << prompt;
		cin >> ws;
		getline(cin, name);
		if (validatestring(name)) {
			valid = true;
		}
		else {
			cout << "error, enter a valid name/string" << endl;
		}
	}
	return name;
}

int inputvalidator::inputint(const string& prompt) {
	int value;
	bool valid = false;
	while (!valid) {
		cout << prompt;
		cin >> value;
		if (validateint(value)) {
			valid = true;
		}
		else {
			cout << "error, enter a propr number (must be positive and a whole number)" << endl;
		}
	}
	return value;
}

bool inputvalidator::inputbool(const string& prompt) {
	bool value;
	bool valid = false;
	while (!valid) {
		cout << prompt;
		cin >> value;
		if (validatebool(value)) {
			valid = true;
		}
		else {
			cout << "error, please enter either true or false" << endl;
		}
	}
	return value;
}

bool inputvalidator::validatestring(const string& input) {
	return !input.empty();
}
bool  inputvalidator::validateint(int input) {
	return input >= 0;
}
bool inputvalidator::validatebool(bool input) {
	return true;
}