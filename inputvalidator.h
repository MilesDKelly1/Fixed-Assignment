//All input related functions and the validation functions assocaited
#pragma once
#include <string>
using namespace std;

class inputvalidator
{
public:
	string inputname(const string& prompt);
	int inputint(const string& prompt);
	bool inputbool(const string& prompt);

	bool validatestring(const string& input);
	bool validateint(int input);
	bool validatebool(bool input);
};