#include <iostream>

#include"TestsCar.h"
#include"TestsReservation.h"
#include"TestsParkingLocation.h"

#include"TestsRepositoryFileTXTofCars.h"
#include"TestsRepositoryFileTXTofReservations.h"
#include"TestsRepositoryFileTXTofParkingLocations.h"

#include"TestsRepositoryFileCSVofCars.h"
#include"TestsRepositoryFileCSVofParkingLocations.h"
#include"TestsRepositoryFileCSVofReservations.h"

#include"TestsCityService.h"

#include"RepositoryFile.h"
#include"RepositoryFileTXT.h"
#include"RepositoryFileCSV.h"
#include"Reservation.h"
#include"ParkingLocation.h"
#include"Car.h"

#include"UI.h"

void tests() {
    TestsCar test_car;
    test_car.testAll();
    /*
    TestsReservation test_reservation;
    test_reservation.testAll();

    TestsParkingLocation test_parking_location;
    test_parking_location.testAll();

    TestsRepositoryFileTXTofCars test_repository_file_txt_of_cars;
    test_repository_file_txt_of_cars.testAll();

    TestsRepositoryFileTXTofReservations test_repository_file_txt_of_reservations;
    test_repository_file_txt_of_reservations.testAll();

    TestsRepositoryFileTXTofParkingLocations test_repository_file_txt_of_parking_locations;
    test_repository_file_txt_of_parking_locations.testAll();

    TestsRepositoryFileCSVofCars test_repository_file_csv_of_cars;
    test_repository_file_csv_of_cars.testAll();

    TestsRepositoryFileCSVofParkingLocations test_repository_file_csv_of_parking_locations;
    test_repository_file_csv_of_parking_locations.testAll();

    TestsRepositoryFileCSVofReservations test_repository_file_csv_of_reservations;
    test_repository_file_csv_of_reservations.testAll();

    TestsCityService test_service;
    test_service.testAll();*/

    std::cout << "The tests have passed!" << endl;
    system("PAUSE");
    system("CLS");
}

int main()
{
    //tests();

    RepoFile<Car>* repository_cars;
    RepoFile<ParkingLocation>* repository_parking_locations;
    RepoFile<Reservation>* repository_reservations;
    RepoFile<Bus>* repository_bus;

    try {
        // if you want to work with txt files, uncomment the lines 74, 75, 76 and comment the lines 78,79,80
        // now, it will work with csv files
         
        //repository_cars = new RepositoryFileTXT<Car>("cars.txt");
        //repository_parking_locations = new RepositoryFileTXT<ParkingLocation>("parking_locations.txt");
        //repository_reservations = new RepositoryFileTXT<Reservation>("reservations.txt");
        //repository_bus = new RepositoryFileCSV<Bus>("bus.txt");

        repository_cars = new RepositoryFileCSV<Car>("cars.csv");
        repository_parking_locations = new RepositoryFileCSV<ParkingLocation>("parking_locations.csv");
        repository_reservations = new RepositoryFileCSV<Reservation>("reservations.csv");
        repository_bus = new RepositoryFileCSV<Bus>("bus.csv");

        CityService* service = new CityService(repository_cars, repository_parking_locations, repository_reservations, repository_bus);
        UI console(service);
        console.runMenu();
    }
    catch (BuildFromFileException bfe) {
        cout << bfe.what();
    }
}