#include "UI.h"
#include<conio.h>

UI::UI(CityService* cs)
{
	this->service = cs;
}

UI::~UI()
{
}

void UI::runMenu()
{
	int cmd;
	bool ok = true;
	while (ok) {
		this->service->maintainReservations();
		this->uiShowMainMenu();
		cout << "\033[96m Choose your option:  \033[0m";
		cin >> cmd;
		while (!cin.good()) {
			cin.clear();
			cin.ignore();
			cout << "Choose your option(1 or 2): ";
			cin >> cmd;
		}
		switch (cmd) {
		case 1:
			this->uiAdmin();
			break;
		case 2:
			this->uiDriver();
			break;
		case 0:
			ok = false;
			break;
		default:
			cout << endl << "\033[35m Invalid option! \033[0m" << endl << endl;
		}
	}
}


void UI::uiShowMainMenu()
{
	cout << endl << "1. Login administrator" << endl;
	cout << "2. Park cars" << endl;
	cout << "0. QUIT" << endl;
}

void UI::uiShowAdminMenu()
{
	cout << endl << "MANAGE Parking Location" << endl;
	cout << "1. Add parking location" << endl;
	cout << "2. Update parking location"<<endl;
	cout << "3. Delete parking location" << endl;
	cout << "MANAGE CARS" << endl;
	cout << "4. Add car" << endl;
	cout << "5. Update car" << endl;
	cout << "6. Delete car by ID" << endl;
	cout << "7. Delete car by registration plate " << endl;
	cout << "SHOW" << endl;
	cout << "8. Show all cars" << endl;
	cout << "9. Show all parking locations" << endl;
	cout << "10. Show all reservations" << endl;
	cout << "11. Show all reservations for a parking place" << endl;
	cout << "FILTER" << endl;
	cout << "12. Delete the reservations from an interval" << endl;
	cout << "SORTING" << endl;
	cout << "13. Sort the parking locations by capacity" << endl;
	cout << "MANAGE BUS" << endl;
	cout << "14. Show all busses" << endl;
	cout << "15. Add bus" << endl;
	cout << "0. BACK" << endl;
}

void UI::uiAdmin()
{
	this->uiLoginAdministrator();
	int cmd;
	bool ok = true;
	while (ok) {
		cout << endl;
		system("PAUSE");
		system("CLS");
		this->service->maintainReservations();
		this->uiShowAdminMenu();
		cout << "\033[96m Choose your option:  \033[0m";
		cin >> cmd;
		while (!cin.good()) {
			cin.clear();
			cin.ignore();
			cout << "Choose your option(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11): ";
			cin >> cmd;
		}
		switch (cmd) {
		case 1:
			this->uiAddParkingLocation();
			break;
		case 2:
			this->uiUpdateParkingLocation();
			break;
		case 3:
			this->uiDeleteParkingLocation();
			break;
		case 4:
			this-> uiAddCar();
			break;
		case 5:
			this->uiUpdateCar();
			break;
		case 6:
			this->uiDeleteCarByID();
			break;
		case 7:
			this->uiDeleteCarByRegitrationPlate();
			break;
		case 8:
			this->uiShowAllCars();
			break;
		case 9:
			this->uiShowAllParkingPlaces();
			break;
		case 10:
			this->uiSowAllReservations();
			break;
		case 11:
			this->uiShowAllReservationsForAParkingLocation();
			break;
		case 12:
			this->uiFilter();
			break;
		case 13:
			this->uiSortParkingLocations();
			break;
		case 14: 
			this->uiShowAllBusses();
			break;
		case 15:
			this->uiAddBus();
			break;
		case 0:
			ok = false;
			break;
		default:
			cout << endl << "\033[35m Invalid option! \033[0m" << endl << endl;
		}
	}
}

void UI::uiShowDriverMenu()
{
	cout << endl << "1. Park a car (You will have to pay the sum that will appear on the screen!) " << endl;
	cout << "2. Delete a reservation " << endl;
	cout << "3. Add time to your reservation(update it) " << endl;
	cout << "4. Show all parking places that has free spots in the city " << endl;
	cout << "5. Show all parking places that has free spots in a certain area " << endl;
	cout << "6. Add car in system (You will ave to keep in mind the ID that you'll choose)" << endl;
	cout << "BUS" << endl;
	cout << "7. Park a bus" << endl;
	cout << "8. Add a bus in system (You will ave to keep in mind the ID that you'll choose)" << endl;
	cout << "0. BACK" << endl;

}

void UI::uiDriver()
{
	int cmd;
	bool ok = true;
	cout << endl << "Pay attention! If your car is not in the system, you have to add it in order to park it" << endl;
	while (ok) {
		cout << endl;
		system("PAUSE");
		system("CLS");
		this->service->maintainReservations();
		if (this->service->notifications().size() > 0) {
			cout << this->service->notifications();
		}
		this->uiShowDriverMenu();
		cout << "\033[96m Choose the option:  \033[0m";
		cin >> cmd;
		while (!cin.good()) {
			cin.clear();
			cin.ignore();
			cout << "Choose your option(1, 2, 3, 4, 5, 6): ";
			cin >> cmd;
		}
		switch (cmd) {
		case 1:
			this->uiAddReservation();
			break;
		case 2:
			this->uiDeleteReservation();
			break;
		case 3:
			this->uiAddExtraTimeToReservation();
			break;
		case 4:
			this->uiShowAllParkingLocationsThatHaveAFreeSpot();
			break;
		case 5:
			this->uiShowAllParkingLocationsThatHaveAFreeSpotInACertainArea();
			break;
		case 6:
			this->uiAddCar();
			break;
		case 7:
			this->uiParkABus();
			break;
		case 8:
			this->uiAddBus();
			break;
		case 0:
			ok = false;
			break;
		default:
			cout << endl << "\033[35m Invalid option! \033[0m" << endl << endl;
		}
	}
}

void UI::uiLoginAdministrator()
{
	string pass = "";
	char ch;
	cout << "Enter Password: ";
	ch = _getch();
	while (ch != 13) {
		pass.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	if (pass == "pass") {
		cout << endl << "Access Granted! \n\n";
	}
	else {
		cout << endl << "Access Aborted...Please Try Again!!\n";
		this->uiLoginAdministrator();
	}
}

void UI::uiAddCar()
{
	unsigned long int id;
	string registration_plate;
	float length, width, height;
	cout << "ID: ";
	cin >> id;
	cout << "Registration plate: ";
	cin >> registration_plate;
	cout << "Length :";
	cin >> length;
	cout << "Width: ";
	cin >> width;
	cout << "Height: ";
	cin >> height;
	try {
		this->service->addCar(id, registration_plate, length, width, height);
		cout << endl << "The process completed successfully! \2" << endl;
	}
	catch (ValidationException ve) {
		cout << "\033[31m" << ve.what() << "\033[0m";
	}
	catch (RepositoryException re) {
		cout << "\033[31m" << re.what() << "\033[0m";
	}
	catch (UniqueIDException uie) {
		cout << "\033[31m" << uie.what() << "\033[0m";
	}
}

void UI::uiDeleteCarByID()
{
	unsigned long int id;
	cout << "ID: ";
	cin >> id;
	try {
		this->service->deleteCarByID(id);
		cout << endl << "The process completed successfully! \2" << endl;
	}
	catch (RepositoryException re) {
		cout << "\033[31m" << re.what() << "\033[0m";
	}
}

void UI::uiDeleteCarByRegitrationPlate()
{
	string registration_plate;
	cout << "Registration plate: ";
	cin >> registration_plate;
	try {
		this->service->deleteCarByRegistrationPlate(registration_plate);
		cout << endl << "The process completed successfully! \2" << endl;
	}
	catch (RepositoryException re) {
		cout << "\033[31m" << re.what() << "\033[0m";
	}
}

void UI::uiUpdateCar()
{
	unsigned long int id;
	float length, width, height;
	string registration_plate;
	cout << "ID: ";
	cin >> id;
	cout << "New registration plate or 0 to do not modify: ";
	cin >> registration_plate;
	cout << "New ength or 0 to do not modify:";
	cin >> length;
	cout << "New idth or 0 to do not modify: ";
	cin >> width;
	cout << "New weight or 0 to do not modify: ";
	cin >> height;
	try {
		this->service->updateCar(id, registration_plate, length, width, height);
		cout << endl << "The process completed successfully! \2" << endl;
	}
	catch (ValidationException ve) {
		cout << "\033[31m" << ve.what() << "\033[0m";
	}
	catch (RepositoryException re) {
		cout << "\033[31m" << re.what() << "\033[0m";
	}
	catch (UniqueIDException uie) {
		cout << "\033[31m" << uie.what() << "\033[0m";
	}
}

void UI::uiAddParkingLocation()
{
	unsigned long int id;
	int capacity;
	string type, area;
	vector<Reservation> v;
	cout << "ID: ";
	cin >> id;
	cout << "Type(Orange, Blue or Purple): ";
	cin >> type;
	cout << "Area(Central, Residential, Working or Commercial): ";
	cin >> area;
	cout << "Capacity: ";
	cin >> capacity;
	try {
		this->service->addParkingLocation(id, type, area, capacity, v);
		cout << endl << "The process completed successfully! \2" << endl;
	}
	catch (ValidationException ve) {
		cout << "\033[31m" << ve.what() << "\033[0m";
	}
	catch (RepositoryException re) {
		cout << "\033[31m" << re.what() << "\033[0m";
	}
	catch (UniqueIDException uie) {
		cout << "\033[31m" << uie.what() << "\033[0m";
	}
}

void UI::uiDeleteParkingLocation()
{
	unsigned long int id; 
	int	capacity;
	string type, area;
	vector<Reservation> v;
	cout << "ID: ";
	cin >> id;
	try {
		this->service->deleteParkingLocationByID(id);
		cout << endl << "The process completed successfully! \2" << endl;
	}
	catch (RepositoryException re) {
		cout << "\033[31m" << re.what() << "\033[0m";
	}
}

void UI::uiUpdateParkingLocation()
{
	unsigned long int id;
	int	capacity;
	string type, area;
	vector<Reservation> v;
	cout << "Pay attention to the cars that are already in the parking location! Your modifies can not affect them! " << endl;
	cout << "ID: ";
	cin >> id;
	cout << "Type(Orange, Blue or Purple) or 0 to do not modify: ";
	cin >> type;
	cout << "Area(Central, Residential, Working or Commercial)  or 0 to do not modify:";
	cin >> area;
	cout << "Capacity or 0 to do not modify:";
	cin >> capacity;
	try {
		this->service->updateParkingLocation(id, type, area, capacity);
		cout << endl << "The process completed successfully! \2" << endl;
	}
	catch (ValidationException ve) {
		cout << "\033[31m" << ve.what() << "\033[0m";
	}
	catch (RepositoryException re) {
		cout << "\033[31m" << re.what() << "\033[0m";
	}
}

void UI::uiAddReservation()
{
	unsigned long int id, id_car, id_parking_location;
	int hours_of_staying, minutes_of_staying;
	double price;
	cout << "ID Car: ";
	cin >> id_car;
	id = id_car;
	cout << "ID Parking Location: ";
	cin >> id_parking_location;
	cout << "Hours of staying: ";
	cin >> hours_of_staying;
	cout << "Minutes of staying: ";
	cin >> minutes_of_staying;
	try {
		price = this->service->addReservation(id, id_car, id_parking_location, hours_of_staying, minutes_of_staying, time(NULL));
		if (this->service->doubleThePriceInMidday(time(NULL))) {
			price = price * 2;
		}
		cout << "Successful reservation! You have to pay: " << price << " coins";
	}
	catch (ValidationException ve) {
		cout << "\033[31m" << ve.what() << "\033[0m";
	}
	catch (RepositoryException re) {
		cout << "\033[31m" << re.what() << "\033[0m";
	}
	catch (UniqueIDException uie) {
		cout << "\033[31m" << uie.what() << "\033[0m";
	}
}

void UI::uiDeleteReservation()
{
	unsigned long int id;
	cout << "ID: ";
	cin >> id;
	try {
		this->service->deleteReservationByID(id);
		cout << endl << "The process completed successfully! \2" << endl;
	}
	catch (RepositoryException re) {
		cout << "\033[31m" << re.what() << "\033[0m";
	}
}

void UI::uiAddExtraTimeToReservation()
{
	unsigned long int id;
	int extra_hours, extra_minutes;
	double price;
	cout << "ID: ";
	cin >> id;
	cout << "Extra hours: ";
	cin >> extra_hours;
	cout << "Extra minutes(0, 15, 30, 45): ";
	cin >> extra_minutes;
	try {
		price = this->service->addMoreMinutesToReservation(id, extra_hours, extra_minutes);
		if (this->service->doubleThePriceInMidday(time(NULL))) {
			price = price * 2;
			cout << "In the time interval 11 - 16, the prices double! ";
		}
		cout << "Successful procces! You have to pay: " << price << " coins";
	}
	catch (ValidationException ve) {
		cout << "\033[31m" << ve.what() << "\033[0m";
	}
	catch (RepositoryException re) {
		cout << "\033[31m" << re.what() << "\033[0m";
	}
}

void UI::uiShowAllCars()
{
	for (Car c : this->service->getAllCars()) {
		cout << c.getInfo() << c << endl;
	}
}

void UI::uiShowAllParkingPlaces()
{
	for (ParkingLocation p : this->service->getAllParkingLocations()) {
		cout << "*" << p << endl;
	}
}

void UI::uiSowAllReservations()
{
	for (Reservation r : this->service->getAllReservations()) {
		cout << r << endl;
	}
}

void UI::uiShowAllReservationsForAParkingLocation()
{
	unsigned long int id;
	cout << "What's the ID of the parking location? ";
	cin >> id;
	for (Reservation r : this->service->getAllReservationsForAParkingLocation(id)) {
		cout << r << endl;
	}
}

void UI::uiShowAllParkingLocationsThatHaveAFreeSpot()
{
	for (ParkingLocation r : this->service->getAllParkingLocationsThatHaveFreeSpots()) {
		cout << r << endl;
	}
}

void UI::uiShowAllParkingLocationsThatHaveAFreeSpotInACertainArea()
{
	string area;
	cout << "Area: ";
	cin >> area;
	for (ParkingLocation r : this->service->getAllParkingLocationsThatHaveFreeSpotsInAnParkingArea(area)) {
		cout << r << endl;
	}
}

void UI::uiSortParkingLocations()
{
	for (ParkingLocation p : this->service->sortParkingLocationsByCapacity()) {
		cout << "*" << p << endl;
	}
}

void UI::uiFilter()
{
	int min_time;
	int max_time;
	cout << "Min time(hour): ";
	cin >> min_time;
	cout << "Max time(hour): ";
	cin >> max_time;
	this->service->filterReservations(min_time, max_time);
}

void UI::uiAddBus()
{
	unsigned long int id;
	string registration_plate;
	float length, width, height;
	cout << "ID: ";
	cin >> id;
	cout << "Registration plate: ";
	cin >> registration_plate;
	cout << "Length :";
	cin >> length;
	cout << "Width: ";
	cin >> width;
	cout << "Height: ";
	cin >> height;
	try {
		this->service->addBus(id, registration_plate, length, width, height);
		cout << endl << "The process completed successfully! \2" << endl;
	}
	catch (ValidationException ve) {
		cout << "\033[31m" << ve.what() << "\033[0m";
	}
	catch (RepositoryException re) {
		cout << "\033[31m" << re.what() << "\033[0m";
	}
	catch (UniqueIDException uie) {
		cout << "\033[31m" << uie.what() << "\033[0m";
	}
}

void UI::uiParkABus()
{
	unsigned long int id, id_bus, id_parking_location;
	int hours_of_staying, minutes_of_staying;
	double price;
	cout << "ID Bus: ";
	cin >> id_bus;
	id = id_bus;
	cout << "ID Parking Location: ";
	cin >> id_parking_location;
	cout << "Hours of staying: ";
	cin >> hours_of_staying;
	cout << "Minutes of staying: ";
	cin >> minutes_of_staying;
	try {
		price = this->service->parkABus(id, id_bus, id_parking_location, hours_of_staying, minutes_of_staying, time(NULL));
		if (this->service->doubleThePriceInMidday(time(NULL))) {
			price = price * 2;
		}
		cout << "Successful reservation! You have to pay: " << price << " coins";
	}
	catch (ValidationException ve) {
		cout << "\033[31m" << ve.what() << "\033[0m";
	}
	catch (RepositoryException re) {
		cout << "\033[31m" << re.what() << "\033[0m";
	}
	catch (UniqueIDException uie) {
		cout << "\033[31m" << uie.what() << "\033[0m";
	}
}

void UI::uiShowAllBusses()
{
	for (Bus b : this->service->getAllBusss()) {
		cout << b.getInfo() << b << endl;
	}
}
