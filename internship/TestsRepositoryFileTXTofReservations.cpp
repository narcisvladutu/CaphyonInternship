#include "TestsRepositoryFileTXTofReservations.h"
#include<cassert>

TestsRepositoryFileTXTofReservations::TestsRepositoryFileTXTofReservations()
{
    Reservation r1(1212, 2222, 1000, 2, 15, 1621097035);
    Reservation r2(2324, 3333, 1000, 3, 45, 1621100035);
    Reservation r3(8798, 4444, 2345, 0, 30, 1621097035);

    this->sample_reservations.push_back(r1);
    this->sample_reservations.push_back(r2);
    this->sample_reservations.push_back(r3);

}

TestsRepositoryFileTXTofReservations::~TestsRepositoryFileTXTofReservations()
{
}

void TestsRepositoryFileTXTofReservations::testAll()
{
    this->testLoadFromFile();
    this->testSaveToFile();

    this->testAddReservation();
    this->testUpdateReservation();
    this->testDeleteReservation();

    this->testFindReservation();
    this->getReservationByID();
    this->testGetAll();
}

void TestsRepositoryFileTXTofReservations::testLoadFromFile()
{
    RepositoryFileTXT<Reservation> repo = RepositoryFileTXT<Reservation>("reservationsIn.txt");
    repo.loadFromFile();
    assert(repo.getAll().size() == this->sample_reservations.size());

    vector<Reservation> reservations = repo.getAll();
    for (int i = 0; i < reservations.size(); i++)
    {
        assert(reservations[i] == this->sample_reservations[i]);
    }
}

void TestsRepositoryFileTXTofReservations::testSaveToFile()
{
    RepositoryFileTXT<Reservation> repo = RepositoryFileTXT<Reservation>("reservationsIn.txt");
    repo.setFileName(this->fileNameOut);
    Reservation new_reservation(3000, 3000, 2344, 4, 0, time(NULL));
    repo.add(new_reservation);
    repo.loadFromFile();
    assert(repo.getAll().size() == this->sample_reservations.size() + 1);

    vector<Reservation> reservations = repo.getAll();
    for (int i = 0; i < reservations.size() - 1; i++)
    {
        assert(reservations[i] == this->sample_reservations[i]);
    }
    assert(reservations[reservations.size() - 1] == new_reservation);
}


void TestsRepositoryFileTXTofReservations::testAddReservation()
{
    RepositoryFileTXT<Reservation> repo = RepositoryFileTXT<Reservation>("reservationsIn.txt");
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    int initialLen = repo.getAll().size();
    Reservation new_reservation(3000, 3000, 2344, 4, 0, time(NULL));
    repo.add(new_reservation);
    assert(repo.getAll().size() == initialLen + 1);
    assert(repo.getAll()[initialLen] == new_reservation);
}

void TestsRepositoryFileTXTofReservations::testUpdateReservation()
{
    RepositoryFileTXT<Reservation> repo = RepositoryFileTXT<Reservation>("reservationsIn.txt");
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    repo.update(this->sample_reservations[0], this->sample_reservations[0]);
    vector<Reservation> reservations = repo.getAll();
    for (int i = 0; i < repo.getAll().size(); i++)
    {
        assert(reservations[i] == this->sample_reservations[i]);
    }
    Reservation r(3000, 3000, 2344, 4, 0, time(NULL));
    repo.update(this->sample_reservations[1], r);
    assert(repo.getAll()[1] == r);
}

void TestsRepositoryFileTXTofReservations::testDeleteReservation()
{
    RepositoryFileTXT<Reservation> repo = RepositoryFileTXT<Reservation>("reservationsIn.txt");
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    int initialLen = repo.getAll().size();
    repo.deleteElem(this->sample_reservations[2]);
    assert(repo.getAll().size() == initialLen - 1);
    Reservation r(3000, 3000, 2344, 4, 0, time(NULL));
    repo.deleteElem(r);
    assert(repo.getAll().size() == initialLen - 1);
}

void TestsRepositoryFileTXTofReservations::testFindReservation()
{
    RepositoryFileTXT<Reservation> repo = RepositoryFileTXT<Reservation>("reservationsIn.txt");
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    assert(repo.find(this->sample_reservations[2]));
    Reservation r(3000, 3000, 2344, 4, 0, time(NULL));
    assert(repo.find(r) == false);
}

void TestsRepositoryFileTXTofReservations::getReservationByID()
{
    RepositoryFileTXT<Reservation> repo = RepositoryFileTXT<Reservation>("reservationsIn.txt");
    repo.loadFromFile();
    repo.setFileName(this->fileNameOut);
    assert(repo.getElementByID(8798) == this->sample_reservations[2]);
    try {
        repo.getElementByID(9999);
        assert(false);
    }
    catch (RepositoryException) {
        assert(true);
    }
}

void TestsRepositoryFileTXTofReservations::testGetAll()
{
    RepositoryFileTXT<Reservation> repo = RepositoryFileTXT<Reservation>("reservationsIn.txt");
    vector<Reservation> reservations = repo.getAll();
    for (int i = 0; i < repo.getAll().size(); i++)
    {
        assert(reservations[i] == this->sample_reservations[i]);
    }
}