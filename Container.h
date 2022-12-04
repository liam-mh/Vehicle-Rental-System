#pragma once
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
    void displayReg();
    void displayMainData();
    void addItemPage();
    void createCar();
    void createBike();
    bool checkRegFormat(string reg);

    void searchForBike();
    void searchForCar();
};
