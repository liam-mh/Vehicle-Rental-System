#pragma once
#include "Vehicle.h"

class Bike : public Vehicle
{
private:
    int engine = 0;
    int wheels = 0;

public:
    Bike(int engine, int wheels, string registration, string make, string model, int age);
    ~Bike();

    virtual double costPerDay() const override;

};