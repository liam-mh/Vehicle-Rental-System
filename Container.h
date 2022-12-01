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
    void removeItem(string reg);
    void removeItem(int index);

    //void displayReg();
    void displayMainData();
    void addItemPage();
    void removeItemPage();

    void createCar();
    void createBike();

    bool checkRegFormat(string reg);
    bool checkRegExists(string reg);

    void searchForBike();
    void searchForCar();
};
