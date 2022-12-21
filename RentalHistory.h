#pragma once
#include "Rent.h"
#include "Vehicle.h"

using namespace std;

class RentalHistory
{
private:
    const Vehicle* vehicle;
    int totalRents = 0;
    Rent** rents = (Rent**)malloc(sizeof(Rent) * totalRents);

public:
    RentalHistory(Vehicle* vehicle);
    ~RentalHistory();

    // Array manipulators
    void addRent(Rent* newEntry);
    void resize();
    void operator+(Rent* newEntry);

    // Display content
    void displayData();
    void viewHistory();

    // User input 
    void rentalPage();
    int createRent();

    const int getTotalRents();
    const double getTotalIncome();
    const int getTotalDays();

    void save(int newRents);
    
};

inline const int RentalHistory::getTotalRents() { return totalRents; }