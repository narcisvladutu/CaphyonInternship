#pragma once
#include<string>
#include<stdexcept>

using namespace std;

//it will be thrown to unique id issues
//-each element of our aplication should have an unique id

class UniqueIDException : public runtime_error
{
private:
	string message;
public:
	UniqueIDException(string msg) :runtime_error(msg), message(msg) {};
	~UniqueIDException() {};

	string what() {
		return this->message;
	}
};

