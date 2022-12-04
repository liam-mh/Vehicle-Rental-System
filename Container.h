#pragma once
#include "Car.h"
#include "Vehicle.h"

#include <vector>
using namespace std;

class Container
{
private:
    vector<Vehicle*> vehicles;

public:
    Container();
    ~Container();

    void addItem(Vehicle* vehicle);
    void removeItem(string reg);
    void removeItem(int index);

    void displayMainData();
    void displayFilteredData(string type, int filters, int filterValue);
    void displayFilteredData(string type, int filters, string filterValue);
    void printData(string type, int i);

    void addItemPage();
    void removeItemPage();

    void create(string type);

    bool checkRegExists(string reg, bool errorMessage);

    void search(string type);

    void save();

    string enterReg(bool checkExists);
    
};
