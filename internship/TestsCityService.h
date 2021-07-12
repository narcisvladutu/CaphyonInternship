#pragma once
#include"CityService.h"
#include"RepositoryFileCSV.h"
#include"RepositoryFileTXT.h"

#include"Car.h"
#include"ParkingLocation.h"
#include"Reservation.h"

class TestsCityService
{
public:
	TestsCityService();
	~TestsCityService();
	void testAll();
private:
	RepositoryFileCSV<Car> *sample_repository_cars = new RepositoryFileCSV<Car>("sample_cars_for_testing_service.csv");
	RepositoryFileCSV<ParkingLocation> *sample_repository_parking_locations = new RepositoryFileCSV<ParkingLocation>("sample_parking_locations_for_testing_service.csv");
	RepositoryFileCSV<Reservation> *sample_repository_reservations = new RepositoryFileCSV<Reservation>("sample_reservations_for_testing_service.csv");
	RepositoryFileCSV<Bus>* sample_repository_bus = new RepositoryFileCSV<Bus>("sample_bus_for_testing_service.csv");
	CityService sample_service = CityService(sample_repository_cars, sample_repository_parking_locations, sample_repository_reservations, sample_repository_bus);

	void testAddCar();
	void testDeleteCarByID();
	void testDeleteCarByRegistrationPlate();
	void testUpdateCar();

	void testAddParkingLocation();
	void testUpdateParkingLocation();
	void testDeleteParkingLocationByID();

	void testAddReservation();
	void testDeleteReservationByID();

	void testAddMoreMinutesToReservation();
	void testMidday();

	void testGetAllCars();
	void testGetAllParkingLocations();
	void testGetAllReservations();

	void testGetAllParkingLocationsThatHaveFreeSpots();
	void testGetAllParkingLocationsThatHaveFreeSpotsInAnParkingArea();
	void testGetAllReservationsForAParkingLocation();

	void testSort();
	void testFilter();
};

