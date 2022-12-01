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

    virtual const void displayVehicle();
    virtual double costPerDay() const = 0;

    const string getVehicleReg() const;
    const string getVehicleMake() const;
    const string getVehicleModel() const;
    const int getVehicleAge() const;

    // friend ofstream& operator<<(ofstream& of, const Vehicle& v);
};

inline const string Vehicle::getVehicleReg() const { return registration; }
inline const string Vehicle::getVehicleMake() const { return make; }
inline const string Vehicle::getVehicleModel() const { return model; }
inline const int Vehicle::getVehicleAge() const { return age; }
