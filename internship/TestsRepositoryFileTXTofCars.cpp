#include "TestsRepositoryFileTXTofCars.h"
#include<cassert>

TestsRepositoryFileTXTofCars::TestsRepositoryFileTXTofCars()
{
    Car c1(1212, "VL21SSS", 2, 3.8, 1.34);
    Car c2(2324, "CJ56NIK", 2, 3.8, 1.34);
    Car c3(8798, "TM32GHE", 2, 3.8, 1.34);

    this->sample_cars.push_back(c1);
    this->sample_cars.push_back(c2);
    this->sample_cars.push_back(c3);
}

TestsRepositoryFileTXTofCars::~TestsRepositoryFileTXTofCars()
{
}

void TestsRepositoryFileTXTofCars::testAll()
{
    this->testLoadFromFile();
    this->testSaveToFile();

    this->testAddCar();
    this->testUpdateCar();
    this->testDeleteCar();

    this->testfindCar();
    this->getCarByID();
    this->testGetAll();
}

void TestsRepositoryFileTXTofCars::testLoadFromFile()
{
    RepositoryFileTXT<Car> repo = RepositoryFileTXT<Car>(this->fileName);
    repo.loadFromFile();
    assert(repo.getAll().size() == this->sample_cars.size());

    vector<Car> cars = repo.getAll();
    for (int i = 0; i < cars.size(); i++)
    {
        assert(cars[i] == this->sample_cars[i]);
    }
}

void TestsRepositoryFileTXTofCars::testSaveToFile()
{
    RepositoryFileTXT<Car> repo = RepositoryFileTXT<Car>(this->fileName);
    repo.setFileName(this->fileNameOut);
    Car new_car(3000, "GJ76JOP", 2, 3.8, 1.34);
    repo.add(new_car);
    repo.loadFromFile();
    assert(repo.getAll().size() == this->sample_cars.size() + 1);

    vector<Car> cars = repo.getAll();
    for (int i = 0; i < cars.size() - 1; i++)
    {
        assert(cars[i] == this->sample_cars[i]);
    }
    assert(cars[cars.size() - 1] == new_car);
}


void TestsRepositoryFileTXTofCars::testAddCar()
{
    RepositoryFileTXT<Car> repo = RepositoryFileTXT<Car>(this->fileName);
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    int initialLen = repo.getAll().size();
    Car new_car(4044, "IF55HHO", 2, 3.8, 1.34);
    repo.add(new_car);
    assert(repo.getAll().size() == initialLen + 1);
    assert(repo.getAll()[initialLen] == new_car);
}

void TestsRepositoryFileTXTofCars::testUpdateCar()
{
    RepositoryFileTXT<Car> repo = RepositoryFileTXT<Car>(this->fileName);
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    repo.update(this->sample_cars[0], this->sample_cars[0]);
    vector<Car> cars = repo.getAll();
    for (int i = 0; i < repo.getAll().size(); i++)
    {
        assert(cars[i] == this->sample_cars[i]);
    }
    Car c(2324, "CV67NAR", 2, 3.8, 1.34);
    repo.update(this->sample_cars[1], c);
    assert(repo.getAll()[1] == c);
}

void TestsRepositoryFileTXTofCars::testDeleteCar()
{
    RepositoryFileTXT<Car> repo = RepositoryFileTXT<Car>(this->fileName);
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    int initialLen = repo.getAll().size();
    repo.deleteElem(this->sample_cars[2]);
    assert(repo.getAll().size() == initialLen - 1);
    repo.deleteElem(Car(9999, "IS44TTU", 2, 3.8, 1.34));
    assert(repo.getAll().size() == initialLen - 1);
}

void TestsRepositoryFileTXTofCars::testfindCar()
{
    RepositoryFileTXT<Car> repo = RepositoryFileTXT<Car>(this->fileName);
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    assert(repo.find(this->sample_cars[2]));
    Car c(2324, "CV67NAR", 2, 3.8, 1.34);
    assert(repo.find(c) == false);
}

void TestsRepositoryFileTXTofCars::getCarByID()
{
    RepositoryFileTXT<Car> repo = RepositoryFileTXT<Car>(this->fileName);
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    assert(repo.getElementByID(8798) == this->sample_cars[2]);
    try {
        repo.getElementByID(9999);
        assert(false);
    }
    catch (RepositoryException) {
        assert(true);
    }
}

void TestsRepositoryFileTXTofCars::testGetAll()
{
    RepositoryFileTXT<Car> repo = RepositoryFileTXT<Car>(this->fileName);
   vector<Car> cars = repo.getAll();
    for (int i = 0; i < repo.getAll().size(); i++)
    {
        assert(cars[i] == this->sample_cars[i]);
    }
}
