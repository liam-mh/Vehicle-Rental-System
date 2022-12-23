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
    const int getTotalRents();
    const double getTotalIncome();
    const int getTotalDays();

    // User input 
    void rentalPage();
    int createRent();
    // Help user input
    tm* getCurrentDate(string& date);
    void addDays(tm* data, int days, string& date);
    string convertToDate(int day, int month, int year);
    
    void save(int newRents);
};
inline const int RentalHistory::getTotalRents() { return totalRents; }

