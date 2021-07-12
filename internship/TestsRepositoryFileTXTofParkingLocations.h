#pragma once
#include"RepositoryFileTXT.h"
#include"ParkingLocation.h"

class TestsRepositoryFileTXTofParkingLocations
{
public:
    TestsRepositoryFileTXTofParkingLocations();
    ~TestsRepositoryFileTXTofParkingLocations();
    void testAll();
private:
    const string fileName = "parkingLocationsIn.txt";
    const string fileNameOut = "parkingLocationsOut.txt";
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
