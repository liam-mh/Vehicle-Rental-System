#include "Bike.h"

#include <fstream>

Bike::Bike(int wheels, int engine, string registration, string make, string model, int age)
    : wheels(wheels), engine(engine), Vehicle(registration, "Bike", make, model, age)
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
        << v->wheels << ","
        << v->engine << ","
        << v->getVehicleReg() << ","
        << "Bike" << ","
        << v->getVehicleMake() << ","
        << v->getVehicleModel() << ","
        << v->getVehicleAge() << "\n";
    return of;
}

string Bike::getVehicleType(){
    return "Bike";
}
