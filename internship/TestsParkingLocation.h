#pragma once
#include"ParkingLocation.h"
#include"ParkingLocationValidator.h"

class TestsParkingLocation
{
public:
	TestsParkingLocation();
	~TestsParkingLocation();

	void testAll();
private:
	void test_validator();

	void testImplicitConstructor();
	void testConstructorWithParameters();
	void testCopyConstrcutor();
	void testConstructorFromString();

	void testSetType();
	void testSetArea();
	void testSetCapacity();

	void testAddReservation();
	void testDeleteReservation();

	void testGetAll();

	void testAssigmnetOperator();
	void testEqualityOperator();

	void testToString();
};

