#pragma once
#include <vector>
#include "Vehicle.h"
#include <iostream>
using namespace std;

class Container
{
private:
    vector<Vehicle*> vehicles;
    string displayFilter;

public:
    Container();
    ~Container();

    // Vector manipulators 
    void addItem(Vehicle* vehicle);
    void removeItem(int index);
    void operator+(Vehicle* newEntry);

    // Display vector content
    void sortByReg();
    void sortByCost();
    void displayMainData();
    void displayFilteredData(string type, int &filter, int filterValue);
    void printFilteredVehicleData(string type, int i);

    // User input 
    void addItemPage();
    void removeItemPage();
    void createVehiclePage(string type);
    void searchForVehiclePage(string type);
    // Helping user input
    void selectForRentalHistory(int totalOptions);
    string userEnterReg(bool alreadyExistsErrorMessage, bool loop);
    bool checkRegExists(string reg, bool alreadyExistsErrorMessage);
};


