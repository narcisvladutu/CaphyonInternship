#include "ParkingLocation.h"

//Descr: create a parking location 
//In: -
//Out: an instance of ParkingLocation
ParkingLocation::ParkingLocation() {
	this->_id = 0;
	this->_type = "";
	this->_area = "";
	this->_capacity = 0;
}

//Descr: create a parking place
//In: an id, the type, the area, the capacity, the reservations of cars which already are here
//Out: an instance (with info) of ParkingLocation
ParkingLocation::ParkingLocation(unsigned long int id, string type, string area, int capacity, vector<Reservation> reservations) {
	this->_id = id;
	this->_type = type;
	this->_area = area;
	this->_capacity = capacity;
	this->_reservations = reservations;
}

//Descr: create a ParkingLocation using info from a string, it can be use in reading from files
//In: a string and the separator from that string
//Out: an instance of ParkingLocation with info from the string
ParkingLocation::ParkingLocation(string args, char delim) {
	this->loadFromString(args, delim);
}

//Descr: create a ParkingLocation using info from another ParkingLocation
//In: a parking location p
//Out: an instance of ParkingLocation with info from p
ParkingLocation::ParkingLocation(const ParkingLocation& p) {
	this->_id = p._id;
	this->_type = p._type;
	this->_area = p._area;
	this->_capacity = p._capacity;
	this->_reservations = p._reservations;
}

//Descr: distroy a ParkingLocation 
//In: a ParkingLocation 
//Out: -
ParkingLocation::~ParkingLocation()
{
	this->_reservations.empty();
}

//Descr: access the id of a ParkingLocation 
//In: a ParkingLocation 
//Out: the id 
int ParkingLocation::getID()
{
	return this->_id;
}

//Descr: access the type of a ParkingLocation 
//In: a ParkingLocation 
//Out: the type 
string ParkingLocation::getType() const
{
	return this->_type;
}

//Descr: change the type of a ParkingLocation 
//In: a ParkingLocation and the new type
//Out: the ParkingLocation that have the new type
void ParkingLocation::setType(const string type)
{
	this->_type = type;
}

//Descr: access the area of a ParkingLocation 
//In: a ParkingLocation 
//Out: the area 
string ParkingLocation::getArea() const
{
	return this->_area;
}

//Descr: change the area of a ParkingLocation 
//In: a ParkingLocation and the new area
//Out: the ParkingLocation that have the new area
void ParkingLocation::setArea(const string area)
{
	this->_area = area;
}

//Descr: access the capacity of a ParkingLocation 
//In: a ParkingLocation 
//Out: the capacity 
int ParkingLocation::getCapacity() const
{
	return this->_capacity;
}

//Descr: change the capacity of a ParkingLocation 
//In: a ParkingLocation and the new capacity
//Out: the ParkingLocation that have the new capacity
void ParkingLocation::setCapacity(int capacity)
{
	this->_capacity = capacity;
}

//Descr: access the size of a ParkingLocation 
//In: a ParkingLocation 
//Out: the size 
int ParkingLocation::getSize() const
{
	return this->_reservations.size();
}

//Descr: access the reservations from a ParkingLocation 
//In: a ParkingLocation 
//Out: a vector of Reservations 
vector<Reservation> ParkingLocation::getAllReservations() const
{
	return this->_reservations;
}

//Descr: add a reservation in the ParkingLocation 
//In: the reservation 
//Out: the ParkingLocation which contain the new reservation
void ParkingLocation::addReservation(Reservation& r)
{
	this->_reservations.push_back(r);
}

//Descr: delete a reservation from ParkingLocation 
//In: the reservation 
//Out: the ParkingLocation whithout the reservation
void ParkingLocation::deleteReservation(Reservation& r)
{
	for (int i = 0; i < this->_reservations.size(); i++) {
		if (r == this->_reservations[i]) {
			this->_reservations.erase(this->_reservations.begin() + i);
		}
	}
}

//Descr: create a new ParkingLocation (equal to a given ParkingLocation p)
//In: a ParkingLocation (p)
//Out: a new ParkingLocation (equal to p)
ParkingLocation& ParkingLocation::operator=(const ParkingLocation& p)
{
	if (this != &p) {
		this->_id = p._id;
		this->_type = p._type;
		this->_area = p._area;
		this->_capacity = p._capacity;
		this->_reservations = p._reservations;
	}
	return *this;
}

//Descr: compare 2 ParkingLocations (the current one and a new one)
//In: two cars 
//Out: true/false
bool ParkingLocation::operator==(const ParkingLocation& p)
{
	bool verify = this->_id == p._id && this->_type == p._type && this->_area == p._area && this->_capacity == p._capacity;
	if (verify == true) {
		for (int i = 0; i < this->_reservations.size(); i++) {
			verify = (this->_reservations[i] == p._reservations[i]);
			if (verify == false) return verify;
		}
		return verify;
	}
	if (this->_reservations.size() != p._reservations.size()) verify = false;
	return verify;
}


//Descr: create a ParkingLocation from a string
//In: a string and the separator
//Out: the ParkingLocation with the informations from the string 
void ParkingLocation::loadFromString(string args, char sep)
{
	vector<string> result;
	stringstream ss(args);
	string item;

	while (getline(ss, item, sep)) {
		result.push_back(item);
	}

	if ((result.size() - 4) % 7 == 0) {
		this->_id = stoi(result[0]);
		this->_type = result[1];
		this->_area = result[2];
		this->_capacity = stoi(result[3]);
		for (int i = 4; i < result.size(); i += 7) {
			Reservation r(stoi(result[i]), stoi(result[i + 1]), stoi(result[i + 2]), stoi(result[i + 3]), stoi(result[i + 4]), stoi(result[i + 5]));
			this->addReservation(r);
		}
	}
	else throw BuildFromFileException("Invalid number of arguments in string");
}

//Descr: convert a ParkingLocation into a string
//In: a ParkingLocation and the separator between informations 
//Out: a string with info about the ParkingLocation 
string ParkingLocation::toStringDelimiter(char sep)
{
	string result = "";
	result = result + to_string(this->_id) + sep + this->_type + sep + this->_area + sep + to_string(this->_capacity) + sep;
	for (Reservation r : this->_reservations) {
		result += r.toStringDelimiter(sep) + sep;
	}
	result = result.substr(0, result.size() - 1);
	return result;
}

//Descr: allows a pleasant display of a ParkingLocation
//In: a ParkingLocation and the ostream for displaying
//Out: the ostream in which is uploaded the information
ostream& operator<<(ostream& os, ParkingLocation& p)
{
	os << "ID: " << p._id << ", Type: " << p._type << ", Area: " << p._area << ", Capacity: "<< p._capacity << ", Reservations: "<< endl;
	for (Reservation r : p._reservations) {
		os << r << endl;
	}
	return os;
}
