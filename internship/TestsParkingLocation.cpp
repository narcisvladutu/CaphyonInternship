#include "TestsParkingLocation.h"
#include <cassert>

TestsParkingLocation::TestsParkingLocation()
{
}

TestsParkingLocation::~TestsParkingLocation()
{
}

void TestsParkingLocation::testAll()
{
	this->test_validator();

	this->testImplicitConstructor();
	this->testConstructorWithParameters();
	this->testCopyConstrcutor();
	this->testConstructorFromString();

	this->testSetType();
	this->testSetArea();
	this->testSetCapacity();

	this->testAddReservation();
	this->testDeleteReservation();
	this->testGetAll();

	this->testAssigmnetOperator();
	this->testEqualityOperator();

	this->testToString();
}

void TestsParkingLocation::test_validator()
{
	ParkingLocationValidator validator;
	vector<Reservation> reservations;
	Reservation r(1010, 1000, 3333, 2, 30, time(NULL));
	reservations.push_back(r);
	ParkingLocation p(3333, "Blue", "Central", 50, reservations);
	try {
		validator.validate(p);
	}
	catch (ValidationException) {
		assert(false);
	}
	catch (...) {
		assert(false);
	}

	vector<Reservation> reservations1;
	ParkingLocation p1(3030, "Dark", "Residential", 35, reservations1);
	try {
		validator.validate(p1);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	catch (...) {
		assert(false);
	}

	ParkingLocation p2(3030, "Blue", "Nearby", 35, reservations1);
	try {
		validator.validate(p2);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	catch (...) {
		assert(false);
	}

	ParkingLocation p3(3030, "Dark", "Nearby", 35, reservations1);
	try {
		validator.validate(p3);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	catch (...) {
		assert(false);
	}

	ParkingLocation p4(3030, "Purple", "Central", -2, reservations1);
	try {
		validator.validate(p4);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	catch (...) {
		assert(false);
	}

	vector<Reservation> many_reservations;
	Reservation r1(1010, 1000, 3333, 2, 30, 1621098035);
	Reservation r2(1111, 1111, 3333, 1, 45, 1621099000);
	Reservation r3(1100, 1212, 3333, 0, 45, 1621100000);
	many_reservations.push_back(r1);
	many_reservations.push_back(r2);
	many_reservations.push_back(r3);
	ParkingLocation p5(3333, "Blue", "Central", 2, many_reservations);
	try {
		validator.validate(p5);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	catch (...) {
		assert(false);
	}

	vector<Reservation> reservations3;
	Reservation r4(1010, 1000, 3333, 2, 30, 1621098035);
	Reservation r5(1111, 1111, 3300, 1, 45, 1621099000);
	reservations3.push_back(r4);
	reservations3.push_back(r5);
	ParkingLocation p6(3333, "Blue", "Central", 2, reservations3);
	try {
		validator.validate(p6);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	catch (...) {
		assert(false);
	}
}

void TestsParkingLocation::testImplicitConstructor()
{
	ParkingLocation p;
	assert(p.getID() == 0);
	assert(p.getType() == "");
	assert(p.getArea() == "");
	assert(p.getCapacity() == 0);
	assert(p.getSize() == 0);
}

void TestsParkingLocation::testConstructorWithParameters()
{
	vector<Reservation> reservations;
	Reservation r(1010, 1000, 3333, 2, 30, time(NULL));
	reservations.push_back(r);
	ParkingLocation p(3333, "Blue", "Central", 50, reservations);
	assert(p.getID() == 3333);
	assert(p.getType() == "Blue");
	assert(p.getArea() == "Central");
	assert(p.getCapacity() == 50);
	assert(p.getSize() == 1);
}

void TestsParkingLocation::testCopyConstrcutor()
{
	vector<Reservation> reservations;
	Reservation r(1010, 1000, 3333, 2, 30, time(NULL));
	reservations.push_back(r);
	ParkingLocation p(3333, "Blue", "Central", 50, reservations), p1 = p;
	assert(p1.getID() == 3333);
	assert(p1.getType() == "Blue");
	assert(p1.getArea() == "Central");
	assert(p1.getCapacity() == 50);
	assert(p1.getSize() == 1);
}

void TestsParkingLocation::testConstructorFromString()
{
	ParkingLocation p("3333 Blue Central 50 1010 1000 3333 2 30 1621097035 1621106035 2000 1212 3333 2 30 1621098035 1621107035", ' ');
	assert(p.getID() == 3333);
	assert(p.getType() == "Blue");
	assert(p.getArea() == "Central");
	assert(p.getCapacity() == 50);
	assert(p.getSize() == 2);
	ParkingLocation p1("3333,Blue,Central,50,1010,1000,3333,2,30,1621097035,1621106035,2000,1212,3333,2,30,1621098035,1621107035", ',');
	assert(p1.getID() == 3333);
	assert(p1.getType() == "Blue");
	assert(p1.getArea() == "Central");
	assert(p1.getCapacity() == 50);
	assert(p1.getSize() == 2);
	try {
		ParkingLocation p2("3333,Blue,Central,50,1010,1000,3333,2,30,2000,1212,3333,2,30,1621098035,1621107035", ',');
		assert(false);
	}
	catch (BuildFromFileException) {
		assert(true);
	}
}

void TestsParkingLocation::testSetType()
{
	vector<Reservation> reservations;
	Reservation r(1010, 1000, 3333, 2, 30, time(NULL));
	reservations.push_back(r);
	ParkingLocation p(3333, "Blue", "Central", 50, reservations);
	p.setType("Orange");
	assert(p.getType() == "Orange");
}

void TestsParkingLocation::testSetArea()
{
	vector<Reservation> reservations;
	Reservation r(1010, 1000, 3333, 2, 30, time(NULL));
	reservations.push_back(r);
	ParkingLocation p(3333, "Blue", "Central", 50, reservations);
	p.setArea("Residential");
	assert(p.getArea() == "Residential");
}

void TestsParkingLocation::testSetCapacity()
{
	vector<Reservation> reservations;
	Reservation r(1010, 1000, 3333, 2, 30, time(NULL));
	reservations.push_back(r);
	ParkingLocation p(3333, "Blue", "Central", 50, reservations);
	p.setCapacity(40);
	assert(p.getCapacity() == 40);
}

void TestsParkingLocation::testAddReservation()
{
	vector<Reservation> reservations;
	Reservation r1(1010, 1000, 3333, 2, 30, time(NULL));
	reservations.push_back(r1);
	ParkingLocation p(3333, "Blue", "Central", 50, reservations);
	Reservation r2(1000, 2020, 2000, 1, 45, time(NULL));
	p.addReservation(r2);
	assert(p.getSize() == 2);
	assert(p.getAllReservations()[1] == r2);
}


void TestsParkingLocation::testDeleteReservation()
{
	vector<Reservation> reservations;
	Reservation r1(1010, 1000, 3333, 2, 30, time(NULL));
	reservations.push_back(r1);
	ParkingLocation p(3333, "Blue", "Central", 50, reservations);
	Reservation r2(1000, 2020, 2000, 1, 45, time(NULL));
	p.addReservation(r2);
	p.deleteReservation(r1);
	assert(p.getSize() == 1);
	assert(p.getAllReservations()[0] == r2);
}

void TestsParkingLocation::testGetAll()
{
	vector<Reservation> reservations;
	Reservation r1(1010, 1000, 3333, 2, 30, time(NULL));
	reservations.push_back(r1);
	ParkingLocation p(3333, "Blue", "Central", 50, reservations);
	Reservation r2(1000, 2020, 2000, 1, 45, time(NULL));
	p.addReservation(r2);
	assert(p.getAllReservations()[0] == r1);
	assert(p.getAllReservations()[1] == r2);
	assert(p.getAllReservations().size() == 2);
}

void TestsParkingLocation::testAssigmnetOperator()
{
	vector<Reservation> reservations;
	Reservation r1(1010, 1000, 3333, 2, 30, time(NULL));
	reservations.push_back(r1);
	ParkingLocation p(3333, "Blue", "Central", 50, reservations), p1;
	p1 = p;
	assert(p1.getID() == 3333);
	assert(p1.getType() == "Blue");
	assert(p1.getArea() == "Central");
	assert(p1.getCapacity() == 50);
	assert(p1.getSize() == 1);
}

void TestsParkingLocation::testEqualityOperator()
{
	vector<Reservation> reservations;
	Reservation r1(1010, 1000, 3333, 2, 30, time(NULL));
	reservations.push_back(r1);
	ParkingLocation p(3333, "Blue", "Central", 50, reservations), p1(3333, "Blue", "Central", 50, reservations), p2(3333, "Orange", "Central", 50, reservations);
	assert(p == p1);
	assert(!(p == p2));
}

void TestsParkingLocation::testToString()
{
	vector<Reservation> reservations;
	Reservation r1(1010, 1000, 3333, 2, 30, 1621097035);
	Reservation r2(2000, 1212, 3333, 2, 30, 1621098035);
	reservations.push_back(r1);
	reservations.push_back(r2);
	ParkingLocation p(3333, "Blue", "Central", 50, reservations);
	assert(p.toStringDelimiter(' ') == "3333 Blue Central 50 1010 1000 3333 2 30 1621097035 1621106035 2000 1212 3333 2 30 1621098035 1621107035");
	assert(p.toStringDelimiter(',') == "3333,Blue,Central,50,1010,1000,3333,2,30,1621097035,1621106035,2000,1212,3333,2,30,1621098035,1621107035");
}
