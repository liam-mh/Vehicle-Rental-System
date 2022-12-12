#pragma once
#include "Car.h"
#include "Vehicle.h"

#include <vector>
using namespace std;

class Container
{
    class sortByReg
    {
    public:
        bool operator() (Vehicle* a, Vehicle* b)
        {
            return a->getVehicleReg() < b->getVehicleReg();
        }
    };
    class sortByCost
    {
    public:
        bool operator() (Vehicle* a, Vehicle* b)
        {
            return a->costPerDay() < b->costPerDay();
        }
    };

private:
    vector<Vehicle*> vehicles;

public:
    Container();
    ~Container();

    void addItem(Vehicle* vehicle);
    void removeItem(string reg);
    void removeItem(int index);

    void displayMainData(bool sortReg, bool sortCost);
    void displayFilteredData(string type, int filters, int filterValue);
    void displayFilteredData(string type, int filters, string filterValue);
    int selectFilteredVehicle();
    void printData(string type, int i);

    void addItemPage();
    void removeItemPage();

    void create(string type);

    bool checkRegExists(string reg, bool errorMessage);

    void search(string type);

    void save();

    string enterReg(bool checkExists);


};