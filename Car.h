#pragma once
#include "Vehicle.h"

class Car : public Vehicle
{
private:
    int doors = 0;
    int seats = 0;

public:
    //Car(int doors, int seats, Vehicle* vehicle);
    Car(int doors, int seats, string registration, string make, string model, int age);
    ~Car();

    //const void displayCar();
    virtual double costPerDay() const override;

    friend ofstream& operator<<(ofstream& of, const Car* v);
};

