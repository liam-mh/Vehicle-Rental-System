#pragma once
#include "Vehicle.h"

#include <vector>

class Container
{
    class sortByReg
    {
    public:
        bool operator() (Vehicle* lhs, Vehicle* rhs) { return lhs->getVehicleReg() < rhs->getVehicleReg(); }
    };

    class sortByCost
    {
    public:
        bool operator() (Vehicle* lhs, Vehicle* rhs) { return lhs->costPerDay() < rhs->costPerDay(); }
    };

private:
    vector<Vehicle*> vehicles;

public:
    Container();
    ~Container();

    // Vector manipulators 
    void addItem(Vehicle* vehicle);
    void removeItem(int index);

    // Display vector content
    void displayMainData(bool sortReg, bool sortCost);
    void displayFilteredData(string type, int filters, int filterValue);
    int selectFilteredVehicle();
    void printFilteredVehicleData(string type, int i);

    // User input 
    void addItemPage();
    void removeItemPage();
    void createVehiclePage(string type);
    void searchForVehiclePage(string type);
    string userEnterReg(bool checkExists, bool alreadyExistsErrorMessage);
    bool checkRegExists(string reg, bool alreadyExistsErrorMessage);
};