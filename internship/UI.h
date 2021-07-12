#pragma once
#include<iostream>
#include"CityService.h"

using namespace std;

class UI
{
private:
	CityService* service;

	void uiShowMainMenu();
	void uiShowAdminMenu();
	void uiShowDriverMenu();

	void uiAdmin();
	void uiDriver();
	void uiLoginAdministrator();

	void uiAddCar();
	void uiDeleteCarByID();
	void uiDeleteCarByRegitrationPlate();
	void uiUpdateCar();

	void uiAddParkingLocation();
	void uiDeleteParkingLocation();
	void uiUpdateParkingLocation();

	void uiAddReservation();
	void uiDeleteReservation();
	void uiAddExtraTimeToReservation();

	void uiShowAllCars();
	void uiShowAllParkingPlaces();
	void uiSowAllReservations();

	void uiShowAllReservationsForAParkingLocation();
	void uiShowAllParkingLocationsThatHaveAFreeSpot();
	void uiShowAllParkingLocationsThatHaveAFreeSpotInACertainArea();

	void uiSortParkingLocations();
	void uiFilter();

	void uiAddBus();
	void uiParkABus();
	void uiShowAllBusses();
public:
	UI(CityService*);
	~UI();

	void runMenu();
};
