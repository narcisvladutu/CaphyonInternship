#pragma once
#include<string>
#include<exception>

using namespace std;

//it will be thrown to validation issues

class ValidationException : public runtime_error
{
private:
	string message;
public:
	ValidationException(string msg) :runtime_error(msg), message(msg) {};
	~ValidationException() {};

	string what() {
		return this->message;
	}
};

