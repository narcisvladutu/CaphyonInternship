#pragma once
#include "RepositoryFile.h"

#include "Car.h"
#include "ParkingLocation.h"
#include "Reservation.h"

#include "Bus.h"

#include "CarValidator.h"
#include "ParkingLocationValidator.h"
#include "ReservationValidator.h"

#include "UniqueIDException.h"

// service

class CityService
{
private:
	RepoFile<Car>* repo_cars;
	RepoFile<ParkingLocation>* repo_parking_locations;
	RepoFile<Reservation>* repo_reservations;
	RepoFile<Bus>* repo_bus;

	CarValidator validator_for_car;
	ParkingLocationValidator validator_for_parking_location;
	ReservationValidator validator_for_reservation;
public:
	CityService(RepoFile<Car>*, RepoFile<ParkingLocation>*, RepoFile<Reservation>*, RepoFile<Bus>*);
	~CityService();

	void addBus(int, string, float, float, float);
	double parkABus(int, int, int, int, int, time_t);

	void addCar(int, string, float, float, float);
	void deleteCarByID(int);
	void deleteCarByRegistrationPlate(string);
	void updateCar(int, string, float, float, float);

	void addParkingLocation(int, string, string, int, vector<Reservation>);
	void updateParkingLocation(int, string, string, int);
	void deleteParkingLocationByID(int);

	double addReservation(int, int, int, int, int, time_t);
	void deleteReservationByID(int);

	double addMoreMinutesToReservation(int, int, int);

	void maintainReservations();
	string notifications();

	vector<Car> getAllCars() const;
	vector<ParkingLocation> getAllParkingLocations() const;
	vector<Reservation> getAllReservations() const;

	vector<ParkingLocation> getAllParkingLocationsThatHaveFreeSpots() const;
	vector<ParkingLocation> getAllParkingLocationsThatHaveFreeSpotsInAnParkingArea(string) const;
	vector<Reservation> getAllReservationsForAParkingLocation(int ) const;

	bool doubleThePriceInMidday(time_t);

	void filterReservations(int, int);

	vector<ParkingLocation> sortParkingLocationsByCapacity();
	vector<Bus> getAllBusss() const;
};

