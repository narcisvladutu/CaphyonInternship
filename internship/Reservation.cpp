//visual studio code do not allow me to use localtime and asctime functions :))
#pragma warning(disable : 4996)
#include "Reservation.h"
#include <cassert>

//Descr: create a Reservation 
//In: -
//Out: an instance of Reservation
Reservation::Reservation()
{
	this->_id = 0;
	this->_id_car = 0;
	this->_id_parking_place = 0;
	this->_hours_of_staying = 0;
	this->_minutes_of_staying = 0;
	this->_arrival_time = 0;
	this->_departure_time = 0;
}


//Descr: create a Reservation
//In: an id, the id of the car, the id of the parking location, the hours of staying, the minutes of staying, the arrival time
//Out: an instance (with info) of Reservation
Reservation::Reservation(unsigned long int id, unsigned long int id_car, unsigned long int id_parking_place, int hours_of_staying, int minutes_of_staying, time_t arrival_time)
{
	this->_id = id;
	this->_id_car = id_car;
	this->_id_parking_place = id_parking_place;
	this->_hours_of_staying = hours_of_staying;
	this->_minutes_of_staying = minutes_of_staying;
	this->_arrival_time = arrival_time;
	this->_departure_time = this->_arrival_time + this->_minutes_of_staying * 60 + this->_hours_of_staying * 3600;
}


//Descr: create a Reservation using info from another Reservation
//In: a Reservation r
//Out: an instance of Reservation with info from r
Reservation::Reservation(const Reservation& r)
{
	this->_id = r._id;
	this->_id_car = r._id_car;
	this->_id_parking_place = r._id_parking_place;
	this->_hours_of_staying = r._hours_of_staying;
	this->_minutes_of_staying = r._minutes_of_staying;
	this->_arrival_time = r._arrival_time;
	this->_departure_time = r._departure_time;
}

//Descr: create a Reservation using info from a string, it can be use in reading from files
//In: a string and the separator from that string
//Out: an instance of Reservation with info from the string
Reservation::Reservation(string args, char sep)
{
	this->loadFromString(args, sep);
}

//Descr: distroy a Reservation 
//In: a Reservation 
//Out: -
Reservation::~Reservation()
{
}


//Descr: change the id of the car of a Reservation 
//In: a Reservation and the new id
//Out: the Reservation that have the new id_car
void Reservation::setIDCar(int id_car)
{
	this->_id_car = id_car;
}

//Descr: access the id of a the car of a Reservation 
//In: a Reservation 
//Out: the id of the car
int Reservation::getIDCar() const
{
	return this->_id_car;
}

//Descr: change the id of the parking location of a Reservation 
//In: a Reservation and the new id of parking location
//Out: the Reservation that have the new id_parking_place
void Reservation::setIDParkingPlace(int id_parking_place)
{
	this->_id_parking_place = id_parking_place;
}

//Descr: change the number of hours of staying of a Reservation 
//In: a Reservation and the new number of hours of staying
//Out: the Reservation that have the new number of hours of staying
void Reservation::setHoursOfStaying(int hours_of_staying)
{
	this->_hours_of_staying = hours_of_staying;
	this->_departure_time = this->_arrival_time + this->_minutes_of_staying * 60 + this->_hours_of_staying * 3600;
}

//Descr: access the number of hours of staying of a Reservation
//In: a Reservation 
//Out: the number of hours of staying of a Reservation
int Reservation::getHoursOfStaying() const
{
	return this->_hours_of_staying;
}

//Descr: change the number of minutes of staying of a Reservation 
//In: a Reservation and the new number of minutes of staying
//Out: the Reservation that have the new number of minutes of staying
void Reservation::setMinutesOfStaying(int minutes_of_staying)
{
	this->_minutes_of_staying = minutes_of_staying;
	this->_departure_time = this->_arrival_time + this->_minutes_of_staying * 60 + this->_hours_of_staying * 3600;
}

//Descr: access the number of minutes of staying of a Reservation
//In: a Reservation 
//Out: the number of minutes of staying of a Reservation
int Reservation::getMinutesOfStaying() const
{
	return this->_minutes_of_staying;
}

//Descr: access the id of a the ParkingLocation of a Reservation 
//In: a Reservation 
//Out: the id of the ParkingLocation
int Reservation::getIDParkingPlace() const
{
	return this->_id_parking_place;
}

//Descr: change the arrival time of a car of a Reservation 
//In: a Reservation and the new arrival time of the car
//Out: the Reservation that have the new arrival time of the car
void Reservation::setArrivalTime(time_t arrival_time)
{
	this->_arrival_time = arrival_time;
	this->_departure_time = this->_arrival_time + this->_minutes_of_staying * 60 + this->_hours_of_staying * 3600;
}

//Descr: access the arrival time of the car of a Reservation 
//In: a Reservation 
//Out: the the arrival time of the car of a Reservation, in seconds from year 1900
time_t Reservation::getArrivalTime() const
{
	return this->_arrival_time;
}

//Descr: access the id of a Reservation 
//In: a Reservation 
//Out: the id of the Reservation
int Reservation::getID() const
{
	return this->_id;
}

//Descr: access the departure time of the car of a Reservation 
//In: a Reservation 
//Out: the the departure time of the car of a Reservation, in seconds from year 1900
time_t Reservation::getDepartureTime() const
{
	return this->_departure_time;
}


//Descr: create a new Reservation (equal to a given Reservation r)
//In: a Reservation (r)
//Out: a new Reservation (equal to r)
Reservation& Reservation::operator=(const Reservation& r)
{
	if (this != &r) {
		this->_id = r._id;
		this->_id_car = r._id_car;
		this->_id_parking_place = r._id_parking_place;
		this->_hours_of_staying = r._hours_of_staying;
		this->_minutes_of_staying = r._minutes_of_staying;
		this->_arrival_time = r._arrival_time;
		this->_departure_time = r._departure_time;
	}
	return *this;
}

//Descr: compare 2 Reservation (the current one and a new one)
//In: two cars 
//Out: true/false
bool Reservation::operator==(const Reservation& r)
{
	return this->_id == r._id && this->_id_car == r._id_car && this->_id_parking_place == r._id_parking_place &&
		this->_hours_of_staying == r._hours_of_staying && this->_minutes_of_staying == r._minutes_of_staying &&
		this->_arrival_time == r._arrival_time && this->_departure_time == r._departure_time;
}


//Descr: create a Reservation from a string
//In: a string and the separator
//Out: the Reservation with the informations from the string 
void Reservation::loadFromString(string args, char sep)
{
	vector<string> result;
	stringstream ss(args);
	string item;

	while (getline(ss, item, sep)) {
		result.push_back(item);
	}

	if (result.size() == 7) {
		this->_id = stoi(result[0]);
		this->_id_car = stoi(result[1]);
		this->_id_parking_place = stoi(result[2]);
		this->_hours_of_staying = stoi(result[3]);
		this->_minutes_of_staying = stoi(result[4]);
		this->_arrival_time = stoi(result[5]);
		this->_departure_time = stoi(result[6]);
	}
	else {
		throw BuildFromFileException("Invalid number of arguments in string");
	}
}

//Descr: convert a Reservation into a string
//In: a Reservation and the separator between informations 
//Out: a string with info about the Reservation 
string Reservation::toStringDelimiter(char sep)
{
	return to_string(this->_id) + sep + to_string(this->_id_car) + sep + to_string(this->_id_parking_place) + sep +
		to_string(this->_hours_of_staying) + sep + to_string(this->_minutes_of_staying) + sep +
		to_string(this->_arrival_time) + sep + to_string(this->_departure_time);
}

//Descr: allows a pleasant display of a Reservation
//In: a Reservation and the ostream for displaying
//Out: the ostream in which is uploaded the information
ostream& operator<<(ostream& os, Reservation& r)
{
	const time_t arr_time = r.getArrivalTime();

	const time_t dprt_time = r.getDepartureTime();

	static struct tm* arrival_time_info = new tm;
	arrival_time_info = localtime(&arr_time);

	struct tm* my_arrival_time_info = arrival_time_info;

	os << "ID: " << r._id << ", Car ID: " << r._id_car << ", Parking place ID: " << r._id_parking_place << ", Hours of staying: " <<
		r._hours_of_staying << ", Minutes of staying: " << r._minutes_of_staying << ", Arrival time: " << asctime(my_arrival_time_info);

	static struct tm* departure_time_info = new tm;
	departure_time_info = localtime(&dprt_time);

	os << ", Departure time: " << asctime(departure_time_info);
	return os;
} 
