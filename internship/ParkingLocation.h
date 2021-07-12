#pragma once
#include<iostream>
#include<string>
#include"Reservation.h"
#include"BuildFromFileException.h"

using namespace std;

class ParkingLocation
{
private:
	unsigned long int _id;
	string _type;
	string _area;
	int _capacity;
	vector<Reservation> _reservations;
public:
	ParkingLocation();
	ParkingLocation(unsigned long int, string, string, int, vector<Reservation>);
	ParkingLocation(string, char);
	ParkingLocation(const ParkingLocation&);
	~ParkingLocation();

	int getID();

	string getType() const;
	void setType(const string);

	string getArea() const;
	void setArea(const string);;

	int getCapacity() const;
	void setCapacity(int);

	int getSize() const;
	vector<Reservation> getAllReservations() const;

	void addReservation(Reservation&);
	void deleteReservation(Reservation&);

	ParkingLocation& operator=(const ParkingLocation&);

	bool operator==(const ParkingLocation&);

	friend ostream& operator<<(ostream&, ParkingLocation&);

	void loadFromString(string args, char sep);

	string toStringDelimiter(char sep);
};

