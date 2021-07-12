#include "TestsCityService.h"
#include<cassert>

TestsCityService::TestsCityService()
{
}

TestsCityService::~TestsCityService()
{
}

void TestsCityService::testAll()
{
	this->testAddCar();
	this->testDeleteCarByID();
	this->testDeleteCarByRegistrationPlate();
	this->testUpdateCar();

	this->testAddParkingLocation();
	this->testUpdateParkingLocation();
	this->testDeleteParkingLocationByID();

	this->testAddReservation();
	this->testDeleteReservationByID();

	this->testAddMoreMinutesToReservation();
	this->testMidday();

	this->testGetAllCars();
	this->testGetAllParkingLocations();
	this->testGetAllReservations();

	this->testGetAllParkingLocationsThatHaveFreeSpots();
	this->testGetAllParkingLocationsThatHaveFreeSpotsInAnParkingArea();
	this->testGetAllReservationsForAParkingLocation();

	this->testFilter();
	this->testSort();
}

void TestsCityService::testAddCar()
{
	int initial_len = this->sample_service.getAllCars().size();
	Car c1(8900, "VS39POP", 2, 3.8, 1.34);
	this->sample_service.addCar(8900, "VS39POP", 2, 3.8, 1.34);
	assert(this->sample_service.getAllCars()[this->sample_service.getAllCars().size() - 1] == c1);

	Car c2(7117, "IF01DFA", 2, 3.8, 1.34);
	this->sample_service.addCar(7117, "IF01DFA", 2, 3.8, 1.34);
	assert(this->sample_service.getAllCars()[this->sample_service.getAllCars().size() - 1] == c2);

	assert(initial_len + 2 == this->sample_service.getAllCars().size());

	try {
		this->sample_service.addCar(9123, "", 2, 3.8, 1.34);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		this->sample_service.addCar(9123, "GH**FF$", 2, 3.8, 1.34);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		this->sample_service.addCar(8900, "GJ96KLU", 2, 3.8, 1.34);
		assert(false);
	}
	catch (UniqueIDException) {
		assert(true);
	}
}

void TestsCityService::testDeleteCarByID()
{
	int initial_len = this->sample_service.getAllCars().size();
	this->sample_service.deleteCarByID(8900);
	assert(this->sample_service.getAllCars().size() == initial_len - 1);

	try {
		this->sample_service.deleteCarByID(8900);
		assert(false);
	}
	catch (RepositoryException) {
		assert(true);
	}
}

void TestsCityService::testDeleteCarByRegistrationPlate()
{
	int initial_len = this->sample_service.getAllCars().size();
	this->sample_service.deleteCarByRegistrationPlate("IF01DFA");
	assert(this->sample_service.getAllCars().size() == initial_len - 1);

	try {
		this->sample_service.deleteCarByRegistrationPlate("IF01DFA");
		assert(false);
	}
	catch (RepositoryException) {
		assert(true);
	}

}

void TestsCityService::testUpdateCar()
{
	Car c1(7777, "CV99YQW", 2, 3.8, 1.34);
	Car c1_new(7777, "DJ99YQW", 2, 3.8, 1.34);
	this->sample_service.updateCar(7777, "DJ99YQW", 2, 3.8, 1.34);
	assert(c1_new == this->sample_service.getAllCars()[4]);
	this->sample_service.updateCar(7777, "CV99YQW", 2, 3.8, 1.34);

	try {
		this->sample_service.updateCar(7777, "HU&*F)Y", 2, 3.8, 1.34);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		this->sample_service.updateCar(998866, "HU44FLY", 2, 3.8, 1.34);
		assert(false);
	}
	catch (RepositoryException) {
		assert(true);
	}
}

void TestsCityService::testAddParkingLocation()
{
	vector<Reservation> res;
	int initial_len = this->sample_service.getAllParkingLocations().size();
	ParkingLocation p1(9090, "Purple", "Commercial", 50, res);
	ParkingLocation p2(9999, "Orange", "Working", 30, res);

	this->sample_service.addParkingLocation(9090, "Purple", "Commercial", 50, res);
	assert(initial_len + 1 == this->sample_service.getAllParkingLocations().size());
	assert(this->sample_service.getAllParkingLocations()[this->sample_service.getAllParkingLocations().size()-1] == p1);

	this->sample_service.addParkingLocation(9999, "Orange", "Working", 30, res);
	assert(initial_len + 2 == this->sample_service.getAllParkingLocations().size());
	assert(this->sample_service.getAllParkingLocations()[this->sample_service.getAllParkingLocations().size() - 1] == p2);

	try {
		this->sample_service.addParkingLocation(9999, "Blue", "Residential", 25, res);
		assert(false);
	}
	catch (UniqueIDException) {
		assert(true);
	}

	try {
		this->sample_service.addParkingLocation(8888, "Dark", "Residential", 25, res);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		this->sample_service.addParkingLocation(7878, "Blue", "Home", -25, res);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
}

void TestsCityService::testUpdateParkingLocation()
{
	vector<Reservation> res;
	ParkingLocation p2(9999, "Orange", "Working", 30, res);
	ParkingLocation p2_new(9999, "Blue", "Working", 30, res);
	this->sample_service.updateParkingLocation(9999, "Blue", "0", 0);
	assert(this->sample_service.getAllParkingLocations()[this->sample_service.getAllParkingLocations().size() - 1] == p2_new);
	this->sample_service.updateParkingLocation(9999, "Orange", "0", 0);

	try {
		this->sample_service.updateParkingLocation(10000, "0", "Residential", 45);
		assert(false);
	}
	catch (RepositoryException) {
		assert(true);
	}

	try {
		this->sample_service.updateParkingLocation(9999, "0", "Residential", -45);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		this->sample_service.updateParkingLocation(9999, "Dark", "0", 45);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
}

void TestsCityService::testDeleteParkingLocationByID()
{
	vector<Reservation> res;
	ParkingLocation p1(9090, "Purple", "Commercial", 50, res);
	int initial_len = this->sample_service.getAllParkingLocations().size();
	this->sample_service.deleteParkingLocationByID(9090);
	assert(initial_len - 1 == this->sample_service.getAllParkingLocations().size());
	assert(this->sample_repository_parking_locations->find(p1) == false);
	this->sample_service.deleteParkingLocationByID(9999);
	assert(initial_len - 2 == this->sample_service.getAllParkingLocations().size());

	try {
		this->sample_service.deleteParkingLocationByID(9998);
		assert(false);
	}
	catch (RepositoryException) {
		assert(true);
	}
}

void TestsCityService::testAddReservation()
{
	Reservation r(1000, 1000, 3000, 2, 45, time(NULL));
	int initial_len = this->sample_service.getAllReservations().size();
	double price = this->sample_service.addReservation(1000, 1000, 3000, 2, 45, time(NULL));
	assert(price == 82.5);
	assert(initial_len + 1 == this->sample_service.getAllReservations().size());
	assert(this->sample_service.getAllReservations()[this->sample_service.getAllReservations().size() - 1] == r);

	try {
		this->sample_service.addReservation(1000, 1000, 3000, 6, 0, time(NULL));
		assert(false);
	}
	catch (UniqueIDException) {
		assert(true);
	}

	try {
		this->sample_service.addReservation(1111, 1000, 3000, 24, 45, time(NULL));
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		this->sample_service.addReservation(1111, 1000, 3000, 0, 23, time(NULL));
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}


	this->sample_service.addReservation(3131, 2323, 3131, 0, 45, time(NULL));
	try {
		this->sample_service.addReservation(10000, 4540, 3131, 0, 15, time(NULL));
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		this->sample_service.addReservation(2323232, 4546754, 3131, 0, 15, time(NULL));
		assert(false);
	}
	catch (RepositoryException) {
		assert(true);
	}
}

void TestsCityService::testDeleteReservationByID()
{
	Reservation r(1000, 1000, 3000, 2, 45, time(NULL));
	int initial_len = this->sample_service.getAllReservations().size();
	this->sample_service.deleteReservationByID(1000);
	assert(this->sample_repository_reservations->find(r) == false);
	assert(this->sample_service.getAllReservations().size() == initial_len - 1);
	this->sample_service.deleteReservationByID(3131);
	assert(this->sample_service.getAllReservations().size() == initial_len - 2);

	try {
		this->sample_service.deleteReservationByID(97779);
		assert(false);
	}
	catch (RepositoryException) {
		assert(true);
	}
}

void TestsCityService::testAddMoreMinutesToReservation()
{
	Reservation r(1000, 1000, 3000, 2, 45, time(NULL));
	this->sample_service.addReservation(1000, 1000, 3000, 2, 45, time(NULL));

	double extra_menoy = this->sample_service.addMoreMinutesToReservation(1000, 1, 15);
	assert(extra_menoy == 37.5);

	try {
		this->sample_service.addMoreMinutesToReservation(1000, 24, 0);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	this->sample_service.deleteReservationByID(1000);

	try {
		this->sample_service.addMoreMinutesToReservation(10000, 0, 15);
		assert(false);
	}
	catch (RepositoryException) {
		assert(true);
	}
}

void TestsCityService::testMidday()
{
	time_t t1 = 163050305;
	time_t t2 = 163060305;
	time_t t3 = 163090305;
	// t1 -> Mon Mar  3 05:45:05 1975
	// t2 -> Mon Mar  3 08:31:45 1975
	// t3 -> Mon Mar  3 16:51 : 45 1975

	assert(this->sample_service.doubleThePriceInMidday(t3) == true);
	assert(this->sample_service.doubleThePriceInMidday(t1) == false);
}

void TestsCityService::testGetAllCars()
{
	Car c1(1000, "SB10NKX", 2, 3.8, 1.34);
	Car c2(1111, "VL67GHE", 2, 3.8, 1.34);
	Car	c3(2323, "CJ55JJI", 2, 3.8, 1.34);
	Car	c4(4540, "IF90FFF", 2, 3.8, 1.34);
	Car	c5(7777, "CV99YQW", 2, 3.8, 1.34);
	vector<Car> sample_cars;
	sample_cars.push_back(c1);
	sample_cars.push_back(c2);
	sample_cars.push_back(c3);
	sample_cars.push_back(c4);
	sample_cars.push_back(c5);
	vector<Car> all = this->sample_service.getAllCars();
	for (int i = 0; i < all.size(); i++) {
		assert(all[i] == sample_cars[i]);
	}
}

void TestsCityService::testGetAllParkingLocations()
{
	vector<Reservation> res;
	ParkingLocation p1(2000, "Blue", "Residential", 25, res);
	ParkingLocation p2(2342, "Orange", "Central", 20, res);
	ParkingLocation p3(3333, "Purple", "Commercial", 15, res);
	ParkingLocation p4(3000, "Blue", "Working", 5, res);
	ParkingLocation p5(3131, "Orange", "Central", 1, res);

	vector<ParkingLocation> sample_parking_locations;
	sample_parking_locations.push_back(p1);
	sample_parking_locations.push_back(p2);
	sample_parking_locations.push_back(p3);
	sample_parking_locations.push_back(p4);
	sample_parking_locations.push_back(p5);
	vector<ParkingLocation> all = this->sample_service.getAllParkingLocations();
	for (int i = 0; i < all.size(); i++) {
		assert(all[i] == sample_parking_locations[i]);
	}
}

void TestsCityService::testGetAllReservations()
{
	Reservation r(1000, 1000, 3000, 2, 45, time(NULL));
	this->sample_service.addReservation(1000, 1000, 3000, 2, 45, time(NULL));

	Reservation r1(2323, 2323, 3333, 1, 30, time(NULL));
	this->sample_service.addReservation(2323, 2323, 3333, 1, 30, time(NULL));

	vector<Reservation> all = this->sample_service.getAllReservations();
	assert(all[0] == r);
	assert(all[1] == r1);
	
	this->sample_service.deleteReservationByID(1000);
	this->sample_service.deleteReservationByID(2323);
}

void TestsCityService::testGetAllParkingLocationsThatHaveFreeSpots()
{
	Reservation r(1000, 1000, 3131, 0, 15, time(NULL));
	this->sample_service.addReservation(1000, 1000, 3131, 0, 15, time(NULL));

	vector<ParkingLocation> parking_locations_with_free_spots = this->sample_service.getAllParkingLocationsThatHaveFreeSpots();

	assert(parking_locations_with_free_spots.size() == 4);
	for (ParkingLocation p : parking_locations_with_free_spots) {
		assert(!(p == this->sample_repository_parking_locations->getElementByID(3131)));
	}

	this->sample_service.deleteReservationByID(1000);
}

void TestsCityService::testGetAllParkingLocationsThatHaveFreeSpotsInAnParkingArea()
{
	Reservation r(1000, 1000, 3131, 0, 15, time(NULL));
	this->sample_service.addReservation(1000, 1000, 3131, 0, 15, time(NULL));

	vector<ParkingLocation> parking_locations_with_free_spots = this->sample_service.getAllParkingLocationsThatHaveFreeSpotsInAnParkingArea("Central");

	assert(parking_locations_with_free_spots.size() == 1);
	for (ParkingLocation p : parking_locations_with_free_spots) {
		assert(!(p == this->sample_repository_parking_locations->getElementByID(3131)));
	}

	this->sample_service.deleteReservationByID(1000);
}

void TestsCityService::testGetAllReservationsForAParkingLocation()
{
	Reservation r1(1000, 1000, 3333, 0, 15, time(NULL));
	Reservation r2(2323, 2323, 3333, 0, 45, time(NULL));
	Reservation r3(4540, 4540, 3333, 0, 30, time(NULL));

	double price1 = this->sample_service.addReservation(1000, 1000, 3333, 0, 15, time(NULL));
	double price2 = this->sample_service.addReservation(2323, 2323, 3333, 0, 45, time(NULL));
	double price3 = this->sample_service.addReservation(4540, 4540, 3333, 0, 30, time(NULL));

	vector<Reservation> all_reservations_for_a_parking_place = this->sample_service.getAllReservationsForAParkingLocation(3333);
	assert(all_reservations_for_a_parking_place.size() == 3);

	this->sample_service.deleteReservationByID(1000);
	this->sample_service.deleteReservationByID(2323);
	this->sample_service.deleteReservationByID(4540);
}

#pragma warning(disable : 4996)

void TestsCityService::testSort()
{
	vector<Reservation> res;
	ParkingLocation p1(2000, "Blue", "Residential", 25, res);
	ParkingLocation p2(2342, "Orange", "Central", 20, res);
	ParkingLocation p3(3333, "Purple", "Commercial", 15, res);
	ParkingLocation p4(3000, "Blue", "Working", 5, res);
	ParkingLocation p5(3131, "Orange", "Central", 1, res);

	vector<ParkingLocation> all_sorted = this->sample_service.sortParkingLocationsByCapacity();
	assert(all_sorted[0] == p5);
	assert(all_sorted[4] == p1);
}

void TestsCityService::testFilter()
{
	time_t t1 = 163050305;
	time_t t2 = 163060305;
	time_t t3 = 163090305;
	// t1 -> Mon Mar  3 05:45:05 1975
	// t2 -> Mon Mar  3 08:31:45 1975
	// t3 -> Mon Mar  3 16:51 : 45 1975

	Reservation r1(1000, 1000, 3333, 0, 15, t1);
	Reservation r2(2323, 2323, 3333, 0, 45, t2);
	Reservation r3(4540, 4540, 3333, 0, 30, t3);

	this->sample_service.addReservation(1000, 1000, 3333, 0, 15, t1);
	this->sample_service.addReservation(2323, 2323, 3333, 0, 45, t2);
	this->sample_service.addReservation(4540, 4540, 3333, 0, 30, t3);

	this->sample_service.filterReservations(8, 18);

	vector<Reservation> all = this->sample_service.getAllReservations();
	assert(all.size() == 1);

	this->sample_service.deleteReservationByID(1000);
}
