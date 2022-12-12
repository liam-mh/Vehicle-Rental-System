#pragma once
#include "Rent.h"
#include "Vehicle.h"

#include <vector>
#include <string>
using namespace std;

class RentalHistory
{
private:
    Vehicle* vehicle;
    //string registration;
    int totalRents = 0;
    Rent** rents = (Rent**)malloc(sizeof(Rent) * totalRents);

public:
    RentalHistory(Vehicle* vehicle);
    RentalHistory(Vehicle* vehicle, int totalRents);

    ~RentalHistory();

    const int getTotalRents();
    void incrementTotalRents();

    const double getTotalIncome();
    const int getTotalDays();

    void addRent(Rent* newEntry);
    void resize();

    void displayData();
    void viewHistory();

    void rentalPage();
    void createRent();

};

inline const int RentalHistory::getTotalRents() { return totalRents; }
inline void RentalHistory::incrementTotalRents() { totalRents++; }