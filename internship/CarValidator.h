#pragma once
#include"Car.h"
#include"ValidationException.h"

//allows validation for the entity Car
//-a Car shouldn't have am empty registration plate
//-the registration plate should contain only digits and letters

class CarValidator
{
public:
	CarValidator() {};
	~CarValidator() {};

	void validate(Car& c)  throw(ValidationException) {
		string errorMessage = "";
		if (c.getRegistrationPlate().empty()) {
			errorMessage += "The registration plate can not be empty!\n";
		}
		for (char symbol : c.getRegistrationPlate()) {
			if (!isalpha(symbol) && !isdigit(symbol)) {
				errorMessage += "The registration plate can not contain other symbols than letters and digits!\n";
				break;
			}
		}
		if (errorMessage.length() > 0) throw ValidationException(errorMessage);
	};
};

