#pragma once
#include"Car.h"
#include"CarValidator.h"

class TestsCar
{
public:
	TestsCar();
	~TestsCar();

	void testAll();
private:
	void test_validator();

	void testImplicitConstructor();
	void testConstructorWithParameters();
	void testCopyConstrcutor();
	void testConstructorFromString();

	void testSetRegistrationPlate();

	void testAssigmnetOperator();
	void testEqualityOperator();

	void testToString();
};

