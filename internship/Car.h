#pragma once
#include<iostream>
#include <vector>
#include <sstream>
#include"BuildFromFileException.h"

using namespace std;

class Car
{
protected:
	unsigned long int _id;
	float _length;
	float _width;
	float _height;
	string _registraion_plate;
public:
	Car();
	Car(unsigned long int, string, float, float, float);
	Car(const Car&);
	Car(string args, char sep);
	virtual ~Car();

	void setRegistrationPlate(string);
	string getRegistrationPlate() const;

	int getID() const;

	float getLenght() const;
	float getWidth() const;
	float getHeight() const;

	Car& operator=(const Car&);

	bool operator==(const Car&);

	friend ostream& operator<<(ostream&, Car&);

	void loadFromString(string args, char sep);

	virtual string getInfo();

	string toStringDelimiter(char sep);
};

