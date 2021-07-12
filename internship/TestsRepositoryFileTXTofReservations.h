#pragma once
#include"RepositoryFileTXT.h"
#include"Reservation.h"


class TestsRepositoryFileTXTofReservations
{
public:
    TestsRepositoryFileTXTofReservations();
    ~TestsRepositoryFileTXTofReservations();
    void testAll();
private:
    const string fileNameOut = "reservationsOut.txt";
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

