#pragma once
#include"RepositoryFileTXT.h"
#include"Car.h"

class TestsRepositoryFileTXTofCars
{
public:
    TestsRepositoryFileTXTofCars();
    ~TestsRepositoryFileTXTofCars();
    void testAll();
private:
    const string fileName = "carsIn.txt";
    const string fileNameOut = "carsOut.txt";
    vector<Car> sample_cars;

    void testAddCar();
    void testUpdateCar();
    void testDeleteCar();

    void testfindCar();
    void getCarByID();
    void testGetAll();

    void testLoadFromFile();
    void testSaveToFile();
};

