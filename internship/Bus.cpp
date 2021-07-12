#include "Bus.h"

Bus::Bus() : Car()
{
}

Bus::Bus(unsigned long int id, string registration_plate, float length, float width, float height): Car(id,registration_plate, length,
	width, height)
{
}

Bus::Bus(const Bus& t): Car(t)
{
}

Bus::Bus(string args, char sep): Car(args, sep)
{
}

Bus::~Bus()
{
}

string Bus::getInfo()
{
	return "This is a bus!";
}

Car& Bus::operator=(const Bus& c)
{
	if (this != &c) {
		this->_id = c._id;
		this->_length = c._length;
		this->_width = c._width;
		this->_height = c._height;
		this->_registraion_plate = c._registraion_plate;
	}
	return *this;
}

bool Bus::operator==(const Bus& t)
{
    return Car::operator==(t);
}

ostream& operator<<(ostream& os, Bus& t)
{
	os << "ID: " << t._id << ", Registration Plate: " << t._registraion_plate << ", Lenght: " << t._length <<
		", Width: " << t._width << ", Height: " << t._height;
	return os;
}
