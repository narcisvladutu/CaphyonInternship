#include "CityService.h"
#include "CarValidator.h"
#include "ParkingLocationValidator.h"
#include "ReservationValidator.h"

//Desc: create an instance of the CityService 
//In: a repository of cars, a repository of parking locations, a repository of reservations
//Out: the CityService
CityService::CityService(RepoFile<Car>* r1, RepoFile<ParkingLocation>* r2, RepoFile<Reservation>* r3, RepoFile<Bus>* r4): repo_cars{r1}, repo_parking_locations{r2}, repo_reservations{r3}, repo_bus{r4}
{
}

//Descr: distroy a CityService 
//In: a car 
//Out: - 
CityService::~CityService()
{
}

void CityService::addBus(int ID, string registration_plate, float length, float width, float height)
{
    for (Bus b : this->repo_bus->getAll()) {
        if (b.getID() == ID) {
            throw UniqueIDException("ID should be unique!");
        }
    }
    for (int i = 0; i < registration_plate.size(); i++) {
        registration_plate[i] = toupper(registration_plate[i]);
    }
    Bus b(ID, registration_plate, length, width, height);
    this->validator_for_car.validate(b);
    this->repo_bus->add(b);
}

double CityService::parkABus(int ID, int ID_bus, int ID_parking_location, int hours_of_staying, int minutes_of_staying, time_t arrival_time)
{
    for (Reservation res : this->repo_reservations->getAll()) {
        if (res.getID() == ID) {
            throw UniqueIDException("ID should be unique!");
        }
    }
    Reservation r(ID, ID_bus, ID_parking_location, hours_of_staying, minutes_of_staying, arrival_time);
    bool found = false;

    this->validator_for_reservation.validate(r);

    for (Bus c : this->repo_bus->getAll()) {
        if (c.getID() == ID_bus) {
            found = true;
        }
    }
    if (!found) {
        throw RepositoryException("There is an reservation for an inexisting car! ");
    }
    found = false;

    for (ParkingLocation c : this->repo_parking_locations->getAll()) {
        if (c.getID() == ID_parking_location) {
            found = true;
        }
    }
    if (!found) {
        throw RepositoryException("There is an reservation for an inexisting parking location! ");
    }

    ParkingLocation p = this->repo_parking_locations->getElementByID(ID_parking_location);

    if (p.getCapacity() - p.getSize() < 5) {
        throw ValidationException("You can't park a bus here!");
    }

    int total_minutes_of_staying = minutes_of_staying + hours_of_staying * 60;
    if (p.getType() == "Orange") {
        if (!(total_minutes_of_staying == 15 || total_minutes_of_staying == 30 || total_minutes_of_staying == 45 || total_minutes_of_staying == 60)) {
            throw ValidationException("In this parking location you can stay 15 minutes, 30 minutes, 45 minutes or 1 hour!");
        }
    }
    if (p.getType() == "Purple") {
        if (total_minutes_of_staying > 180) {
            throw ValidationException("In this parking location you can stay maximum 3 hours!");
        }
    }
    if (p.getType() == "Blue") {
        if (total_minutes_of_staying > 1440) {
            throw ValidationException("In this parking location you can stay maximum 24 hours!");
        }
    }

    vector<Reservation> v = p.getAllReservations();
    v.push_back(r);

    ParkingLocation p_updated(p.getID(), p.getType(), p.getArea(), p.getCapacity(), v);
    this->validator_for_parking_location.validate(p_updated);

    this->repo_reservations->add(r);
    this->repo_parking_locations->update(p, p_updated);

    double price = 0;
    if (p.getArea() == "Central") price = (double)100 / 60 * total_minutes_of_staying;
    if (p.getArea() == "Residential") price = (double)70 / 60 * total_minutes_of_staying;
    if (p.getArea() == "Commercial") price = (double)50 / 60 * total_minutes_of_staying;
    if (p.getArea() == "Working") price = (double)30 / 60 * total_minutes_of_staying;

    return price;
}

//Descr: add a Car in the system
//In: the ID of the car and the registration plate of the car
//Out: - 
void CityService::addCar(int ID, string registration_plate, float length, float width, float height)
{
    for (Car c : this->repo_cars->getAll()) {
        if (c.getID() == ID) {
            throw UniqueIDException("ID should be unique!");
        }
    }
    for (int i = 0; i < registration_plate.size(); i++) {
        registration_plate[i] = toupper(registration_plate[i]);
    }
    Car c(ID, registration_plate, length, width, height);
    this->validator_for_car.validate(c);
    this->repo_cars->add(c);
}

//Descr: delete a Car from the system
//In: the ID of the car
//Out: - 
void CityService::deleteCarByID(int ID)
{
    bool found = false;
    for (Car c : this->repo_cars->getAll()) {
        if (c.getID() == ID) {
            this->repo_cars->deleteElem(c);
            found = true;
            break;
        }
    }
    if (found) {
        for (Reservation res : this->repo_reservations->getAll()) {
            if (res.getIDCar() == ID) {
                this->repo_reservations->deleteElem(res);
                ParkingLocation p = this->repo_parking_locations->getElementByID(res.getIDParkingPlace());
                vector<Reservation> v = p.getAllReservations();
                for (int i = 0; i < v.size(); i++) {
                    if (v[i] == res) {
                        v.erase(v.begin() + i);
                        break;
                    }
                }
                ParkingLocation p_uptaded(p.getID(), p.getType(), p.getArea(), p.getCapacity(), v);
                this->repo_parking_locations->update(p, p_uptaded);
                break;
            }
        }
    }
    else {
        throw RepositoryException("The ID is not valid! Try again!");
    }
}

//Descr: delete a Car from the system
//In: the registration plate of the car
//Out: - 
void CityService::deleteCarByRegistrationPlate(string registration_plate)
{
    for (Car c : this->repo_cars->getAll()) {
        if (c.getRegistrationPlate() == registration_plate) {
            this->repo_cars->deleteElem(c);
            return;
        }
    }
    throw RepositoryException("The registration plate is not valid! Try again!");
}

//Descr: update a Car from the system
//In: the id of the car, the new registration plate of the car
//Out: -
void CityService::updateCar(int ID, string registration_plate, float length, float width, float height)
{
    for (int i = 0; i < registration_plate.size(); i++) {
        registration_plate[i] = toupper(registration_plate[i]);
    }
    for (Car c : this->repo_cars->getAll()) {
        if (c.getID() == ID) {
            Car new_car(ID, registration_plate == "0" ? c.getRegistrationPlate(): registration_plate,
                length == 0? c.getLenght(): length, width == 0? c.getWidth(): width, height == 0? c.getHeight(): height);
            this->validator_for_car.validate(new_car);
            this->repo_cars->update(c, new_car);
            return;
        }
    }
    throw RepositoryException("The ID is not valid! Try again!");
}

//Descr: add a ParkingLocation in the system
//In: the ID of the ParkingLocation, the type of ParkingLocation, the area of the ParkingLocation, the capacity of the ParkingLocation, the reservations of the ParkingLocation
//Out: - 
void CityService::addParkingLocation(int ID, string type, string area, int capacity, vector<Reservation> reservations)
{
    for (ParkingLocation p : this->repo_parking_locations->getAll()) {
        if (p.getID() == ID) {
            throw UniqueIDException("ID should be unique!");
        }
    }
    for (Reservation r : reservations) {
        bool found = false;
        for (Car c : this->repo_cars->getAll()) {
            if (r.getID() == c.getID()) {
                found = true;
            }
        }
        if (!found) {
            throw RepositoryException("There is an reservation for an inexisting car! ");
        }
    }
    for (Reservation r : reservations) {
        this->validator_for_reservation.validate(r);
        this->repo_reservations->add(r);
    }
    if (type.size() > 0 && area.size() > 0) {
        type[0] = toupper(type[0]);
        area[0] = toupper(area[0]);
    }
    ParkingLocation p(ID, type, area, capacity, reservations);
    this->validator_for_parking_location.validate(p);
    this->repo_parking_locations->add(p);
}

//Descr: update a ParkingLocation from the system
//In: the id of the ParkingLocation, the new type of the ParkingLocation or 0 to do not modify the old one, the new area of the ParkingLocation or 0 to do not modify the old one, the new capacity of the ParkingLocation or 0 to do not modify the old one
//Out: -
void CityService::updateParkingLocation(int ID, string new_type, string new_area, int new_capacity)
{
    if (new_type.size() > 0 && new_area.size() > 0) {
        new_type[0] = toupper(new_type[0]);
        new_area[0] = toupper(new_area[0]);
    }
    for (ParkingLocation p : this->repo_parking_locations->getAll()) {
        if (p.getID() == ID) {
            vector<Reservation> v = p.getAllReservations();
            ParkingLocation p_new(ID, new_type == "0" ? p.getType() : new_type, new_area == "0" ? p.getArea() : new_area,
                new_capacity == 0 ? p.getCapacity() : new_capacity, v);
            this->validator_for_parking_location.validate(p_new);

            string type = new_type == "" ? p.getType() : new_type;
            if (type != p.getType()) {
                for (Reservation r : v) {
                    int total_minutes_of_staying = r.getMinutesOfStaying() + r.getHoursOfStaying() * 60;
                    if (type == "Orange") {
                        if (!(total_minutes_of_staying == 15 || total_minutes_of_staying == 30 || total_minutes_of_staying == 45 || total_minutes_of_staying == 60)) {
                            throw ValidationException("There is an resrvation here which will be invalide after this update! The best time for making an update to a parking location is when it is empty!");
                        }
                    }
                    if (type == "Purple") {
                        if (total_minutes_of_staying > 180) {
                            throw ValidationException("There is an resrvation here which will be invalide after this update! The best time for making an update to a parking location is when it is empty!");
                        }
                    }
                    if (type == "Blue") {
                        if (total_minutes_of_staying > 1440) {
                            throw ValidationException("There is an resrvation here which will be invalide after this update! The best time for making an update to a parking location is when it is empty!");
                        }
                    }
                }
            }

        this->repo_parking_locations->update(p, p_new);
        return;
        }
    }
    throw RepositoryException("The ID is not valid! Try again!");
}

//Descr: delete a ParkingLocation from the system
//In: the id of the ParkingLocation
//Out: - 
void CityService::deleteParkingLocationByID(int ID)
{
    for (Reservation r : this->repo_reservations->getAll()) {
        if (r.getIDParkingPlace() == ID) {
            this->repo_reservations->deleteElem(r);
            ;
        }
    }    
    for (ParkingLocation p : this->repo_parking_locations->getAll()) {
        if (p.getID() == ID) {
            this->repo_parking_locations->deleteElem(p);
            return;
        }
    }
    throw RepositoryException("There ID is not valid! Try again! ");
}

//Descr: add a Reservation in the system
//In: the ID of the Reservation, the ID of the Car,  the ID of the ParkingLocation, the number of hours of staying, the number of minutes of staying, the arrival time(time_t)
//Out: the money the driver has to pay
double CityService::addReservation(int id, int id_car, int id_parking_place, int hours_of_staying, int minutes_of_staying, time_t arrival_time)
{
    for (Reservation res : this->repo_reservations->getAll()) {
        if (res.getID() == id) {
            throw UniqueIDException("ID should be unique!");
        }
    }
    Reservation r(id, id_car, id_parking_place, hours_of_staying, minutes_of_staying, arrival_time);
    bool found = false;

    this->validator_for_reservation.validate(r);

    for (Car c : this->repo_cars->getAll()) {
        if (c.getID() == id_car) {
            found = true;
        }
    }
    if (!found) {
        throw RepositoryException("There is an reservation for an inexisting car! ");
    }
    found = false;

    for (ParkingLocation c : this->repo_parking_locations->getAll()) {
        if (c.getID() == id_parking_place) {
            found = true;
        }
    }
    if (!found) {
        throw RepositoryException("There is an reservation for an inexisting parking location! ");
    }

    ParkingLocation p = this->repo_parking_locations->getElementByID(id_parking_place);
    int total_minutes_of_staying = minutes_of_staying + hours_of_staying * 60;
    if (p.getType() == "Orange") {
        if (!(total_minutes_of_staying == 15 || total_minutes_of_staying == 30 || total_minutes_of_staying == 45 || total_minutes_of_staying == 60)) {
            throw ValidationException("In this parking location you can stay 15 minutes, 30 minutes, 45 minutes or 1 hour!");
        }
    }
    if (p.getType() == "Purple") {
        if (total_minutes_of_staying > 180) {
            throw ValidationException("In this parking location you can stay maximum 3 hours!");
        }
    }
    if (p.getType() == "Blue") {
        if (total_minutes_of_staying > 1440) {
            throw ValidationException("In this parking location you can stay maximum 24 hours!");
        }
    }

    vector<Reservation> v = p.getAllReservations();
    v.push_back(r);

    ParkingLocation p_updated(p.getID(), p.getType(), p.getArea(), p.getCapacity(), v);
    this->validator_for_parking_location.validate(p_updated);

    this->repo_reservations->add(r);
    this->repo_parking_locations->update(p, p_updated);

    double price = 0;
    if (p.getArea() == "Central" ) price = (double) 100 / 60 * total_minutes_of_staying;
    if (p.getArea() == "Residential") price = (double) 70 / 60 * total_minutes_of_staying;
    if (p.getArea() == "Commercial") price = (double) 50 / 60 * total_minutes_of_staying;
    if (p.getArea() == "Working") price = (double) 30 / 60 * total_minutes_of_staying;

    return price;
}


//Descr: delete a Reservation from the system
//In: the ID of the Reservation
//Out: - 
void CityService::deleteReservationByID(int ID)
{
    for (Reservation res : this->repo_reservations->getAll()) {
        if (res.getID() == ID) {
            this->repo_reservations->deleteElem(res);
            ParkingLocation p = this->repo_parking_locations->getElementByID(res.getIDParkingPlace());
            vector<Reservation> v = p.getAllReservations();
            for (int i = 0; i < v.size(); i++) {
                if (v[i] == res) {
                    v.erase(v.begin() + i);
                    break;
                }
            }
            ParkingLocation p_uptaded(p.getID(), p.getType(), p.getArea(), p.getCapacity(), v);
            this->repo_parking_locations->update(p, p_uptaded);
            return;
        }
    }
    throw RepositoryException("There ID is not valid! Try again! ");
}


//***Bonus Task****
//Descr: add extra time to a Reservation
//In: the ID of the Reservation, the number of extra hours, the number of extra minutes
//Out: the money the driver has to pay
double CityService::addMoreMinutesToReservation(int ID, int more_hours, int more_minutes)
{
    Reservation r = this->repo_reservations->getElementByID(ID);
    int total_minutes_of_staying = r.getHoursOfStaying() * 60 + r.getMinutesOfStaying() + more_hours * 60 + more_minutes;

    ParkingLocation p = this->repo_parking_locations->getElementByID(r.getIDParkingPlace());
    if (p.getType() == "Orange") {
        if (!(total_minutes_of_staying == 15 || total_minutes_of_staying == 30 || total_minutes_of_staying == 45 || total_minutes_of_staying == 60)) {
            throw ValidationException("In this parking location you can stay 15 minutes, 30 minutes, 45 minutes or 1 hour!");
        }
    }
    if (p.getType() == "Purple") {
        if (total_minutes_of_staying > 180) {
            throw ValidationException("In this parking location you can stay maximum 3 hours!");
        }
    }
    if (p.getType() == "Blue") {
        if (total_minutes_of_staying > 1440) {
            throw ValidationException("In this parking location you can stay maximum 24 hours!");
        }
    }

    vector<Reservation> v = p.getAllReservations();

    if (((r.getMinutesOfStaying() + more_minutes) / 60) != 0) {
        Reservation r_new(ID, r.getIDCar(), r.getIDParkingPlace(), r.getHoursOfStaying() + more_hours + 1, r.getMinutesOfStaying() + more_minutes - 60, r.getArrivalTime());
        this->validator_for_reservation.validate(r_new);
        this->repo_reservations->update(r, r_new);
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == r) {
                v[i] = r_new;
                break;
            }
        }
    }
    else {
        Reservation r_new(ID, r.getIDCar(), r.getIDParkingPlace(), r.getHoursOfStaying() + more_hours, r.getMinutesOfStaying() + more_minutes, r.getArrivalTime());
        this->validator_for_reservation.validate(r_new);
        this->repo_reservations->update(r, r_new);
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == r) {
                v[i] = r_new;
                break;
            }
        }
    }

    ParkingLocation p_updated(p.getID(), p.getType(), p.getArea(), p.getCapacity(), v);
    this->repo_parking_locations->update(p, p_updated);

    int more_minutes_added = more_hours * 60 + more_minutes;
    
    if (p.getArea() == "Central") return (double) 100 / 60 * more_minutes_added;
    if (p.getArea() == "Residential") return (double) 70 / 60 * more_minutes_added;
    if (p.getArea() == "Commercial") return (double) 50 / 60 * more_minutes_added;
    if (p.getArea() == "Working") return (double) 30 / 60 * more_minutes_added;

    return 0;
}

//Descr: delete all the Reservations which expired
//In: -
//Out: -
void CityService::maintainReservations()
{
    for (Reservation r : this->repo_reservations->getAll()) {
        if (r.getDepartureTime() < time(NULL)) {
            ParkingLocation p = this->repo_parking_locations->getElementByID(r.getIDParkingPlace());
            this->repo_reservations->deleteElem(r);
            vector<Reservation> v = p.getAllReservations();
            for (int i = 0; i < v.size(); i++) {
                if (v[i] == r) {
                    v.erase(v.begin() + i);
                    break;
                }
            }
            ParkingLocation p_uptaded(p.getID(), p.getType(), p.getArea(), p.getCapacity(), v);
            this->repo_parking_locations->update(p, p_uptaded);
        }
    }
}

//***Bonus Task**** You should be running the console aplication in that moments in driver mode to see this notifications
//Descr: give notifications about Reservations which will expire in about 10 minutes
//In: -
//Out: an message for that Reservations
string CityService::notifications()
{
    string message = "";
    for (Reservation r : this->repo_reservations->getAll()) {
        int seconds_before_expire = r.getDepartureTime() - time(NULL);
        if (540 < seconds_before_expire && seconds_before_expire < 600) {
            message += "In 10 minutes, the reservation for the car with ID: " + to_string(r.getIDCar()) + " will expire! " + "\n";
        }
    }
    return message;
}

//Descr: give acces to all the cars from the system
//In: -
//Out: all the cars from the system, vector
vector<Car> CityService::getAllCars() const
{
    return this->repo_cars->getAll();
}

//Descr: give acces to all the parking locations from the system
//In: -
//Out: all the parking locations from the system, vector
vector<ParkingLocation> CityService::getAllParkingLocations() const
{
    return this->repo_parking_locations->getAll();
}

//Descr: give acces to all the reservations from the system
//In: -
//Out: all the reservations from the system, vector
vector<Reservation> CityService::getAllReservations() const
{
    return this->repo_reservations->getAll();
}

//Descr: give acces to all the parking locations that have a free spot from the system
//In: -
//Out: all the parking locations that have a free spot from the system, vector
vector<ParkingLocation> CityService::getAllParkingLocationsThatHaveFreeSpots() const
{
    vector<ParkingLocation> result;
    for (ParkingLocation r : this->repo_parking_locations->getAll()) {
        if (r.getCapacity() - r.getSize() > 0) {
            result.push_back(r);
        }
    }
    return result;
}

//Descr: give acces to all the parking locations from a certain area, that have a free spot, from the system
//In: the area
//Out: all the parking locations from a certain area, that have a free spot, from the system, vector
vector<ParkingLocation> CityService::getAllParkingLocationsThatHaveFreeSpotsInAnParkingArea(string area) const
{
    vector<ParkingLocation> result;
    for (ParkingLocation r : this->repo_parking_locations->getAll()) {
        if (r.getCapacity() - r.getSize() > 0 && r.getArea() == area){
            result.push_back(r);
        }
    }
    return result;
}

//Descr: give acces to all the reservations from a certain parking location, from the system
//In: the ID of the parking location
//Out: all the reservations from a certain parking location, from the system, vector
vector<Reservation> CityService::getAllReservationsForAParkingLocation(int ID) const
{
    vector<Reservation> result;
    for (Reservation r : this->repo_reservations->getAll()) {
        if (r.getIDParkingPlace() == ID) {
            result.push_back(r);
        }
    }
    return result;
}

//i want to use localtime in visual studio
#pragma warning(disable : 4996)

//***BONUS TASK***
//Descr: in de midday(11- 16), the prices will de doubled
//In: the time of the arrival of a car
//Out: true, if it is noon, false, otherwise
bool CityService::doubleThePriceInMidday(time_t arrival_time)
{
    struct tm* arr;
    arr = localtime(&arrival_time);
    if (11 <= arr->tm_hour && arr->tm_hour <= 16) {
        return true;
    }
    return false;
}

void CityService::filterReservations(int min_time, int max_time)
{
    for (Reservation r : this->getAllReservations()) {
        time_t arr = r.getArrivalTime();
        struct tm* arr_time = localtime(&arr);
        if (min_time <= arr_time->tm_hour && arr_time->tm_hour <= max_time) {
            this->deleteReservationByID(r.getID());
        }
    }
}

vector<ParkingLocation> CityService::sortParkingLocationsByCapacity()
{
    vector<ParkingLocation> all_sorted = this->getAllParkingLocations();
    ParkingLocation aux;
    int i, last_position;
    int unordred_lenght = all_sorted.size() - 1;
    do {
        last_position = 0;
        for (i = 0; i < unordred_lenght; i++)
            if (all_sorted[i].getCapacity() > all_sorted[i + 1].getCapacity()) {
                aux = all_sorted[i];
                all_sorted[i] = all_sorted[i + 1];
                all_sorted[i + 1] = aux;
                last_position = i;
            }
        unordred_lenght = last_position;
    } while (last_position > 0);
    return all_sorted;
}

vector<Bus> CityService::getAllBusss() const
{
    return this->repo_bus->getAll();
}
