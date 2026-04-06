#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class exceptionhandler : public runtime_error {
public: 
	explicit exceptionhandler(const string& message) : runtime_error(message) {}
	const char* what() const noexcept override {
		return runtime_error::what();
	}
};