#include "TestsReservation.h"
#include<cassert>

TestsReservation::TestsReservation()
{
}

TestsReservation::~TestsReservation()
{
}

void TestsReservation::testAll()
{
	
	this->test_validator();

	this->testImplicitConstructor();
	this->testConstructorWithParameters();
	this->testCopyConstrcutor();
	this->testConstructorFromString();

	this->testSetIDCar();
	this->testSetIDParkingPlace();
	this->testSetHoursOfStaying();
	this->testSetMinutesOfStaying();
	this->testSetArrivaltime();

	this->testAssigmnetOperator();
	this->testEqualityOperator();

	this->testToString();
}

void TestsReservation::test_validator()
{
	Reservation  r(1111, 1000, 1010, 2, 15, time(NULL));
	ReservationValidator validator;
	try {
		validator.validate(r);
	}
	catch (ValidationException) {
		assert(false);
	}
	catch (...) {
		assert(false);
	}
	Reservation  r1(1111, 1000, 1010, 36, 14, time(NULL));
	try {
		validator.validate(r1);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	catch (...) {
		assert(false);
	}
}

void TestsReservation::testImplicitConstructor()
{
	Reservation r;
	assert(r.getID() == 0);
	assert(r.getIDCar() == 0);
	assert(r.getIDParkingPlace() == 0);
	assert(r.getHoursOfStaying() == 0);
	assert(r.getMinutesOfStaying() == 0);
	assert(r.getArrivalTime() == 0);
	assert(r.getDepartureTime() == 0);
}

void TestsReservation::testConstructorWithParameters()
{
	Reservation r(1111, 1000, 1010, 2, 15, time(NULL));
	time_t current_tine = time(NULL);
	assert(r.getID() == 1111);
	assert(r.getIDCar() == 1000);
	assert(r.getIDParkingPlace() == 1010);
	assert(r.getHoursOfStaying() == 2);
	assert(r.getMinutesOfStaying() == 15);
	assert(r.getArrivalTime() == current_tine);
	assert(r.getDepartureTime() == current_tine + 15 * 60 + 2 * 3600);
}

void TestsReservation::testCopyConstrcutor()
{
	Reservation r(1111, 1000, 1010, 2, 15, time(NULL)), r1 = r;
	time_t current_tine = time(NULL);
	assert(r1.getID() == 1111);
	assert(r1.getIDCar() == 1000);
	assert(r1.getIDParkingPlace() == 1010);
	assert(r1.getHoursOfStaying() == 2);
	assert(r1.getMinutesOfStaying() == 15);
	assert(r1.getArrivalTime() == current_tine);
	assert(r1.getDepartureTime() == current_tine + 15 * 60 + 2 * 3600);
}

void TestsReservation::testConstructorFromString()
{
	Reservation r("1111 1000 1010 2 15 1621097035 1621105135", ' ');
	assert(r.getID() == 1111);
	assert(r.getIDCar() == 1000);
	assert(r.getIDParkingPlace() == 1010);
	assert(r.getHoursOfStaying() == 2);
	assert(r.getMinutesOfStaying() == 15);
	assert(r.getArrivalTime() == 1621097035);
	assert(r.getDepartureTime() == 1621105135);

	Reservation r1("1111,1000,1010,2,15,1621097035,1621105135", ',');
	assert(r1.getID() == 1111);
	assert(r1.getIDCar() == 1000);
	assert(r1.getIDParkingPlace() == 1010);
	assert(r1.getHoursOfStaying() == 2);
	assert(r1.getMinutesOfStaying() == 15);
	assert(r1.getArrivalTime() == 1621097035);
	assert(r1.getDepartureTime() == 1621105135);
}

void TestsReservation::testSetIDCar()
{
	Reservation r(1111, 1000, 1010, 2, 15, time(NULL));
	r.setIDCar(2000);
	assert(r.getIDCar() == 2000);
}

void TestsReservation::testSetIDParkingPlace()
{
	Reservation r(1111, 1000, 1010, 2, 15, time(NULL));
	r.setIDParkingPlace(2000);
	assert(r.getIDParkingPlace() == 2000);
}

void TestsReservation::testSetHoursOfStaying()
{
	Reservation r(1111, 1000, 1010, 2, 15, time(NULL));
	time_t departure_time = r.getDepartureTime();
	r.setHoursOfStaying(20);
	assert(r.getHoursOfStaying() == 20);
}

void TestsReservation::testSetMinutesOfStaying()
{
	Reservation r(1111, 1000, 1010, 2, 15, time(NULL));
	time_t departure_time = r.getDepartureTime();
	r.setMinutesOfStaying(45);
	assert(r.getMinutesOfStaying() == 45);
}

void TestsReservation::testSetArrivaltime()
{
	Reservation r(1111, 1000, 1010, 2, 15, time(NULL));
	r.setArrivalTime(1621098035);
	assert(r.getArrivalTime() == 1621098035);
}

void TestsReservation::testAssigmnetOperator()
{
	Reservation r(1111, 1000, 1010, 2, 15, time(NULL)), r1;
	r1 = r;
	time_t current_tine = time(NULL);
	assert(r1.getID() == 1111);
	assert(r1.getIDCar() == 1000);
	assert(r1.getIDParkingPlace() == 1010);
	assert(r1.getHoursOfStaying() == 2);
	assert(r1.getMinutesOfStaying() == 15);
	assert(r1.getArrivalTime() == current_tine);
	assert(r1.getDepartureTime() == current_tine + 15 * 60 + 2 * 3600);
}

void TestsReservation::testEqualityOperator()
{
	Reservation r(1111, 1000, 1010, 2, 15, time(NULL)), r1(1111, 1000, 1010, 2, 15, time(NULL)), r2(1111, 3333, 3030, 2, 15, time(NULL));
	assert(r == r1);
	assert(!(r == r2));
}

void TestsReservation::testToString()
{
	Reservation r(1111, 1000, 1010, 2, 15, 1621105135);
	assert(r.toStringDelimiter(' ') == "1111 1000 1010 2 15 1621105135 1621113235");
	assert(r.toStringDelimiter(',') == "1111,1000,1010,2,15,1621105135,1621113235");
}
