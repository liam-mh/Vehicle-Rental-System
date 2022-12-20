#include "Bike.h"

#include <fstream>

Bike::Bike(int engine, int wheels, string registration, string make, string model, int age)
    : engine(engine), wheels(wheels), Vehicle(registration, "Bike", make, model, age)
{}

Bike::~Bike()
{}

double Bike::costPerDay() const
{
    int calc = 1500 + ((engine+100) - (engine%100));
    return calc / 100;
}

ofstream& operator<<(ofstream& of, const Bike* v)
{
    of
        << v->engine << ","
        << v->wheels << ","
        << v->getVehicleReg() << ","
        << "Bike" << ","
        << v->getVehicleMake() << ","
        << v->getVehicleModel() << ","
        << v->getVehicleAge() << "\n";
    return of;
}