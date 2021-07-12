#pragma once
#include<string>
#include<stdexcept>

using namespace std;

//it will be thrown to repository issues

class RepositoryException : public runtime_error
{
private:
	string message;
public:
	RepositoryException(string msg): runtime_error(msg), message(msg) {};
	~RepositoryException() {};

	string what() {
		return this->message;
	}
};
