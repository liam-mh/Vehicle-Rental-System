#pragma once
#include "Vehicle.h"

class Bike : public Vehicle
{
private:
    int wheels = 0,
        engine = 0;
    
public:
    Bike(int engine, int wheels, string registration, string make, string model, int age);
    ~Bike();

    virtual const int getVal1() override;
    virtual const int getVal2() override;
    virtual double costPerDay() const override;

};

inline const int Bike::getVal1() { return wheels; }
inline const int Bike::getVal2() { return engine; }