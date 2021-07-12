#pragma once
#include"Car.h"

class Bus: public Car
{
private:
	int size = 5;
public:
	Bus();
	Bus(unsigned long int, string, float, float,float);
	Bus(const Bus&);
	Bus(string args, char sep);
	~Bus();

	string getInfo();

	Car& operator=(const Bus&);

	bool operator==(const Bus&);

	friend ostream& operator<<(ostream&, Bus&);
};

