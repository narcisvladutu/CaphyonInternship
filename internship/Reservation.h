#pragma once
#include<iostream>
#include <vector>
#include <sstream>
#include<time.h>
#include"BuildFromFileException.h"

using namespace std;

class Reservation
{
private:
	unsigned long int _id;
	unsigned long int _id_car;
	unsigned long int _id_parking_place;
	int _hours_of_staying;
	int _minutes_of_staying;
	time_t _arrival_time;
	time_t _departure_time;
public:
	Reservation();
	Reservation(unsigned long int, unsigned long int, unsigned long int, int, int, time_t);
	Reservation(const Reservation&);
	Reservation(string args, char sep);
	~Reservation();

	void setIDCar(int);
	int getIDCar() const;

	void setIDParkingPlace(int);
	int getIDParkingPlace() const;

	void setHoursOfStaying(int);
	int getHoursOfStaying() const;

	void setMinutesOfStaying(int);
	int getMinutesOfStaying() const;

	void setArrivalTime(time_t);
	time_t getArrivalTime()const;

	int getID() const;

	time_t getDepartureTime() const;

	Reservation& operator=(const Reservation&);

	bool operator==(const Reservation&);

	friend ostream& operator<<(ostream&, Reservation&);

	void loadFromString(string args, char sep);
	string toStringDelimiter(char sep);
};
