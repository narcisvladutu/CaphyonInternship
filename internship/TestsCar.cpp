#include "TestsCar.h"
#include<cassert>

TestsCar::TestsCar()
{
}

TestsCar::~TestsCar()
{
}

void TestsCar::testAll()
{
	this->test_validator();
	this->testImplicitConstructor();
	this->testConstructorWithParameters();
	this->testCopyConstrcutor();
	this->testConstructorFromString();
	this->testSetRegistrationPlate();
	this->testAssigmnetOperator();
	this->testEqualityOperator();
	this->testToString();
}

void TestsCar::test_validator()
{
	Car c(1111, "VL12DDD", 2, 4.5, 1.89);
	CarValidator validator;
	try {
		validator.validate(c);
	}
	catch (ValidationException) {
		assert(false);
	}
	catch (...) {
		assert(false);
	}
	Car c1(2222, "", 2, 4.5, 1.89);
	try {
		validator.validate(c1);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	catch (...) {
		assert(false);
	}
}

void TestsCar::testImplicitConstructor()
{
	Car c;
	assert(c.getID() == 0);
	assert(c.getRegistrationPlate() == "");
}

void TestsCar::testConstructorWithParameters()
{
	Car c(1111, "VL12DDD", 2, 4.5, 1.89);
	assert(c.getID() == 1111);
	assert(c.getRegistrationPlate() == "VL12DDD");
}

void TestsCar::testCopyConstrcutor()
{
	Car c(1111, "VL12DDD", 2, 4.5, 1.89), c1 = c;
	assert(c1.getID() == 1111);
	assert(c1.getRegistrationPlate() == "VL12DDD");
}

void TestsCar::testConstructorFromString()
{
	Car c("1111 VL12DDD", ' ');
	assert(c.getID() == 1111);
	assert(c.getRegistrationPlate() == "VL12DDD");
	Car c1("1111,VL12DDD", ',');
	assert(c1.getID() == 1111);
	assert(c1.getRegistrationPlate() == "VL12DDD");
}

void TestsCar::testSetRegistrationPlate()
{

	Car c(1111, "VL12DDD", 2, 4.5, 1.89);
	c.setRegistrationPlate("VL22CCC");
	assert(c.getID() == 1111);
	assert(c.getRegistrationPlate() == "VL22CCC");
}

void TestsCar::testAssigmnetOperator()
{
	Car c(1111, "VL12DDD", 2, 4.5, 1.89), c1;
	c1 = c;
	assert(c1.getID() == 1111);
	assert(c1.getRegistrationPlate() == "VL12DDD");
}

void TestsCar::testEqualityOperator()
{
	Car c(1111, "VL12DDD", 2, 4.5, 1.89), c1(1111, "VL12DDD", 2, 4.5, 1.89), c2(1111, "CJ10NPK", 2, 4.5, 1.89);
	assert(c1 == c);
	assert(!(c == c2));
}

void TestsCar::testToString()
{
	Car c(1111, "VL12DDD", 2, 4.5, 1.89);
	assert(c.toStringDelimiter(' ') == "1111 VL12DDD");
	assert(c.toStringDelimiter(',') == "1111,VL12DDD");
}