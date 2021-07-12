#pragma once
#include"RepositoryFileCSV.h"
#include"Car.h"

class TestsRepositoryFileCSVofCars
{
public:
    TestsRepositoryFileCSVofCars();
    ~TestsRepositoryFileCSVofCars();
    void testAll();
private:
    const string fileName = "carsIn.csv";
    const string fileNameOut = "carsOut.csv";
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

