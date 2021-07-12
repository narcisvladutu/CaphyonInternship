#include "TestsRepositoryFileTXTofParkingLocations.h"
#include<cassert>

TestsRepositoryFileTXTofParkingLocations::TestsRepositoryFileTXTofParkingLocations()
{
    vector<Reservation> res;
    ParkingLocation p1(1212, "Orange", "Central", 15, res);
    ParkingLocation p2(2324, "Blue", "Working", 45, res);
    ParkingLocation p3(8798, "Purple", "Commercial", 30, res);

    this->sample_parking_locations.push_back(p1);
    this->sample_parking_locations.push_back(p2);
    this->sample_parking_locations.push_back(p3);
}

TestsRepositoryFileTXTofParkingLocations::~TestsRepositoryFileTXTofParkingLocations()
{
}

void TestsRepositoryFileTXTofParkingLocations::testAll()
{
    this->testLoadFromFile();
    this->testSaveToFile();

    this->testAddParkingLocation();
    this->testUpdateParkingLocation();
    this->testDeleteParkingLocation();

    this->testFindParkingLocation();
    this->testgetParkingLocationByID();
    this->testGetAll();
}

void TestsRepositoryFileTXTofParkingLocations::testLoadFromFile()
{
    RepositoryFileTXT<ParkingLocation> repo = RepositoryFileTXT<ParkingLocation>(this->fileName);
    repo.loadFromFile();
    assert(repo.getAll().size() == this->sample_parking_locations.size());

    vector<ParkingLocation> parking_locations = repo.getAll();
    for (int i = 0; i < parking_locations.size(); i++)
    {
        assert(parking_locations[i] == this->sample_parking_locations[i]);
    }
}

void TestsRepositoryFileTXTofParkingLocations::testSaveToFile()
{
    RepositoryFileTXT<ParkingLocation> repo = RepositoryFileTXT<ParkingLocation>(this->fileName);
    repo.setFileName(this->fileNameOut);
    vector<Reservation> res;
    ParkingLocation new_parking_location(3000, "Purple", "Residential", 60, res);
    repo.add(new_parking_location);
    repo.loadFromFile();
    assert(repo.getAll().size() == this->sample_parking_locations.size() + 1);

    vector<ParkingLocation> parking_locations = repo.getAll();
    for (int i = 0; i < parking_locations.size() - 1; i++)
    {
        assert(parking_locations[i] == this->sample_parking_locations[i]);
    }
    assert(parking_locations[parking_locations.size() - 1] == new_parking_location);
}


void TestsRepositoryFileTXTofParkingLocations::testAddParkingLocation()
{
    RepositoryFileTXT<ParkingLocation> repo = RepositoryFileTXT<ParkingLocation>(this->fileName);
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    int initialLen = repo.getAll().size();
    vector<Reservation> res;
    ParkingLocation new_parking_location(3000, "Purple", "Residential", 60, res);
    repo.add(new_parking_location);
    assert(repo.getAll().size() == initialLen + 1);
    assert(repo.getAll()[initialLen] == new_parking_location);
}

void TestsRepositoryFileTXTofParkingLocations::testUpdateParkingLocation()
{
    RepositoryFileTXT<ParkingLocation> repo = RepositoryFileTXT<ParkingLocation>(this->fileName);
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    repo.update(this->sample_parking_locations[0], this->sample_parking_locations[0]);
    vector<ParkingLocation> parking_locations = repo.getAll();
    for (int i = 0; i < repo.getAll().size(); i++)
    {
        assert(parking_locations[i] == this->sample_parking_locations[i]);
    }
    vector<Reservation> res;
    ParkingLocation new_parking_location(3000, "Purple", "Residential", 60, res);
    repo.update(this->sample_parking_locations[1], new_parking_location);
    assert(repo.getAll()[1] == new_parking_location);
}

void TestsRepositoryFileTXTofParkingLocations::testDeleteParkingLocation()
{
    RepositoryFileTXT<ParkingLocation> repo = RepositoryFileTXT<ParkingLocation>(this->fileName);
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    int initialLen = repo.getAll().size();
    repo.deleteElem(this->sample_parking_locations[2]);
    assert(repo.getAll().size() == initialLen - 1);
    vector<Reservation> res;
    ParkingLocation new_parking_location(3000, "Purple", "Residential", 60, res);
    repo.deleteElem(new_parking_location);
    assert(repo.getAll().size() == initialLen - 1);
}

void TestsRepositoryFileTXTofParkingLocations::testFindParkingLocation()
{
    RepositoryFileTXT<ParkingLocation> repo = RepositoryFileTXT<ParkingLocation>(this->fileName);
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    assert(repo.find(this->sample_parking_locations[2]));
    vector<Reservation> res;
    ParkingLocation new_parking_location(3000, "Purple", "Residential", 60, res);
    assert(repo.find(new_parking_location) == false);
}

void TestsRepositoryFileTXTofParkingLocations::testgetParkingLocationByID()
{
    RepositoryFileTXT<ParkingLocation> repo = RepositoryFileTXT<ParkingLocation>(this->fileName);
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    assert(repo.getElementByID(8798) == this->sample_parking_locations[2]);
    try {
        repo.getElementByID(9999);
        assert(false);
    }
    catch (RepositoryException) {
        assert(true);
    }
}

void TestsRepositoryFileTXTofParkingLocations::testGetAll()
{
    RepositoryFileTXT<ParkingLocation> repo = RepositoryFileTXT<ParkingLocation>(this->fileName);
    vector<ParkingLocation> parking_locations = repo.getAll();
    for (int i = 0; i < repo.getAll().size(); i++)
    {
        assert(parking_locations[i] == this->sample_parking_locations[i]);
    }
}