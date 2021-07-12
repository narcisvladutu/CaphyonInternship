#pragma once
#include"ParkingLocation.h"
#include "ValidationException.h"


//allows validation for the entity ParkingLocation
//-a ParkingLocation shouldn't have more reservations than its capacity
//-the type of a ParkingLocation can be only Blue, Orange or Purple
//-the area of a ParkingLocation can be only Commercial, Working, Central or Residential
//-the capacity of a ParkingLocation should be an positive integer number
//-the reservations should have the id of the parking location suitable

class ParkingLocationValidator
{
public:
	ParkingLocationValidator() {};
	~ParkingLocationValidator() {};

	void validate(ParkingLocation& p)  throw(ValidationException) {
		string errorMessage = "";
		if (p.getCapacity() < p.getSize()) {
			errorMessage += "The maximum numbers of cars that can be parcked here has been exceeded! ";
		}
		if (!(p.getType() == "Blue" || p.getType() == "Orange" || p.getType() == "Purple")) {
			errorMessage += "The type of the parking place can be only Orange, Purple or Blue! ";
		}
		if (!(p.getArea() == "Central" || p.getArea() == "Residential" || p.getArea() == "Working" || p.getArea() == "Commercial")) {
			errorMessage += "The location of the parking place can be only Central, Residential, Commercial or Working! ";
		}
		if (p.getCapacity() <= 0) {
			errorMessage += "The capacity should be an positive integer number! ";
		}
		for (Reservation r : p.getAllReservations()) {
			if (r.getIDParkingPlace() != p.getID()) {
				errorMessage += "There is an incorrect reservation!";
				break;
			}
		}
		if (errorMessage.length() > 0) throw ValidationException(errorMessage);
	}
};

