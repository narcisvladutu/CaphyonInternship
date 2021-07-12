#pragma once
#include"RepositoryFileCSV.h"
#include"Reservation.h"

class TestsRepositoryFileCSVofReservations
{
public:
    TestsRepositoryFileCSVofReservations();
    ~TestsRepositoryFileCSVofReservations();
    void testAll();
private:
    const string fileNameOut = "reservationsOut.csv";
    vector<Reservation> sample_reservations;

    void testAddReservation();
    void testUpdateReservation();
    void testDeleteReservation();

    void testFindReservation();
    void getReservationByID();
    void testGetAll();

    void testLoadFromFile();
    void testSaveToFile();
};

