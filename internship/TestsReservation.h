#pragma once
#include"Reservation.h"
#include"ReservationValidator.h"

class TestsReservation
{
public:
	TestsReservation();
	~TestsReservation();

	void testAll();

private:
	void test_validator();

	void testImplicitConstructor();
	void testConstructorWithParameters();
	void testCopyConstrcutor();
	void testConstructorFromString();

	void testSetIDCar();
	void testSetIDParkingPlace();
	void testSetHoursOfStaying();
	void testSetMinutesOfStaying();
	void testSetArrivaltime();

	void testAssigmnetOperator();
	void testEqualityOperator();

	void testToString();
};

