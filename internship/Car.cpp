#include "Car.h"

//Descr: create a car 
//In: -
//Out: an instance of Car
Car::Car()
{
	this->_id = 0;
	this->_length = 0;
	this->_width = 0;
	this->_height = 0;
	this->_registraion_plate = "";
}

//Descr: create a flower
//In: an id and a registration plate
//Out: an instance (with info) of Car
Car::Car(unsigned long int id, string registraion_plate, float length, float width, float height)
{
	this->_id = id;
	this->_registraion_plate = registraion_plate;
	this->_length = length;
	this->_width = width;
	this->_height = height;
}

//Descr: create a car using info from another car
//In: a car c
//Out: an instance of Car with info from c
Car::Car(const Car& c)
{
	this->_id = c._id;
	this->_registraion_plate = c._registraion_plate;
	this->_length = c._length;
	this->_width = c._width;
	this->_height = c._height;
}

//Descr: create a car using info from a string, it can be use in reading from files
//In: a string and the separator from that string
//Out: an instance of Car with info from the string
Car::Car(string args, char sep)
{
	this->loadFromString(args, sep);
}


//Descr: distroy a Car 
//In: a car 
//Out: - 
Car::~Car()
{
}

//Descr: change the registration plate of a car 
//In: a car and the new registration plate
//Out: the car have the new registration plate
void Car::setRegistrationPlate(string new_registraion_plate)
{
	this->_registraion_plate = new_registraion_plate;
}

//Descr: access the registration plate of a car 
//In: a car 
//Out: the registration plate 
string Car::getRegistrationPlate() const
{
	return this->_registraion_plate;
}


//Descr: access the id of a car 
//In: a car 
//Out: the id 
int Car::getID() const
{
	return this->_id;
}

float Car::getLenght() const
{
	return this->_length;
}

float Car::getWidth() const
{
	return this->_width;
}

float Car::getHeight() const
{
	return this->_height;
}

//Descr: create a new Car (equal to a given Car c)
//In: a car (c)
//Out: a new car (equal to c)
Car& Car::operator=(const Car& c)
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

//Descr: compare 2 car (the current one and a new one)
//In: two cars 
//Out: true/false
bool Car::operator==(const Car& c)
{
	return c._id == this->_id && c._registraion_plate == this->_registraion_plate && this->_length == c._length && 
		this->_width == c._width && this->_height == c._height;
}

//Descr: create a car from a string
//In: a string and the separator
//Out: the Car with the informations from the string 
void Car::loadFromString(string args, char sep)
{
	vector<string> result;
	stringstream ss(args);
	string item;

	while (getline(ss, item, sep)) {
		result.push_back(item);
	}


	if (result.size() == 5) {
		this->_id = stoi(result[0]);
		this->_registraion_plate = result[1];
		this->_length = stof(result[2]);
		this->_width = stof(result[3]);
		this->_height = stof(result[4]);
	}
	else {
		throw BuildFromFileException("Invalid number of arguments in string");
	}
}

string Car::getInfo()
{
	return "This is a car!";
}

//Descr: convert a Car into a string
//In: a Car and the separator between informations 
//Out: a string with info about the Car 
string Car::toStringDelimiter(char sep)
{
	return to_string(this->_id) + sep + this->_registraion_plate + to_string(this->_length) + to_string(this->_width) + to_string(this->_height);
}

//Descr: allows a pleasant display of a car
//In: a Car and the ostream for displaying
//Out: the ostream in which is uploaded the information
ostream& operator<<(ostream& os, Car& c)
{
	os << "ID: " << c._id << ", Registration Plate: " << c._registraion_plate << ", Lenght: "<< c._length << 
		", Width: " << c._width << ", Height: "<< c._height;
	return os;
}