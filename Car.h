#pragma once
#include "Vehicle.h"

class Car : public Vehicle
{
private:
    int doors = 0;
    int seats = 0;

public:
    Car(int doors, int seats, string registration, string make, string model, int age);
    ~Car();

    //void createCar();
    virtual double costPerDay() const override;

};

