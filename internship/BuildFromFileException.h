#pragma once
#include<string>
#include<stdexcept>

using namespace std;

//it will be thrown to building from file issues

class BuildFromFileException : public runtime_error
{
private:
	string message;
public:
	BuildFromFileException(string msg) :runtime_error(msg), message(msg) {};
	~BuildFromFileException() {};

	string what() {
		return this->message;
	}
};

