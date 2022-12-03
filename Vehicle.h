#pragma once
#include <string>
#include <cstring>

using namespace std;

class Vehicle
{
private:
    string registration, type, make, model;
    int age = 0;

public:
    Vehicle(string registration, string type, string make, string model, int age);
    virtual ~Vehicle();

    const string getVehicleReg() const;
    const int getVehicleAge() const;
    virtual double costPerDay() const = 0;
};

inline const string Vehicle::getVehicleReg() const { return registration; }
inline const int Vehicle::getVehicleAge() const { return age; }
