#pragma once
#include"Reservation.h"
#include"ValidationException.h"

//allows validation for the entity Reservation
//-the numbers of hours of satying and of minutes of staying should be integers and positive
//-the minutes of staying can be only 0,15, 30 or 45
//-yhe maximum number of hours of staying is 24

class ReservationValidator
{
public:
	ReservationValidator() {};
	~ReservationValidator() {};

	void validate(Reservation& r) throw(ValidationException) {
		string errorMessage = "";
		if (r.getHoursOfStaying() < 0 || r.getHoursOfStaying() > 24) {
			errorMessage += "The maximum hours of staying are 24 and it can not be a negative number! ";
		}
		if (r.getMinutesOfStaying() != 0) {
			if (r.getMinutesOfStaying() != 15) {
				if (r.getMinutesOfStaying() != 30) {
					if (r.getMinutesOfStaying() != 45) errorMessage += "The number of minutes of staying can be 0, 15, 30 or 45";
				}
			}
		}
		if (errorMessage.length() > 0) throw ValidationException(errorMessage);
	}
};
