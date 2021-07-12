#pragma once
#include"RepositoryFileCSV.h"
#include"ParkingLocation.h"

class TestsRepositoryFileCSVofParkingLocations
{
public:
    TestsRepositoryFileCSVofParkingLocations();
    ~TestsRepositoryFileCSVofParkingLocations();
    void testAll();
private:
    const string fileName = "parkingLocationsIn.csv";
    const string fileNameOut = "parkingLocationsOut.csv";
    vector<ParkingLocation> sample_parking_locations;

    void testAddParkingLocation();
    void testUpdateParkingLocation();
    void testDeleteParkingLocation();

    void testFindParkingLocation();
    void testgetParkingLocationByID();
    void testGetAll();

    void testLoadFromFile();
    void testSaveToFile();
};

