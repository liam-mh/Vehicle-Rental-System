#pragma once
#include "Vehicle.h"

class Car : public Vehicle
{
private:
    int doors = 0,
        seats = 0;

public:
    Car(int doors, int seats, string registration, string make, string model, int age);
    ~Car();

    virtual const int getVal1() override;
    virtual const int getVal2() override;
    virtual double costPerDay() const override;
    virtual string getVehicleType() override;

    friend ofstream& operator<<(ofstream& of, const Car* v);
};
inline const int Car::getVal1() { return doors; }
inline const int Car::getVal2() { return seats; }

