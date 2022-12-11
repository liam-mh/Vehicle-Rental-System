#define _CRT_SECURE_NO_WARNINGS
#include "Bike.h"
#include "Vehicle.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

Bike::Bike(int engine, int wheels, string registration, string make, string model, int age)
    : engine(engine), wheels(wheels), Vehicle(registration, "Bike", make, model, age)
{}

Bike::~Bike()
{}

double Bike::costPerDay() const
{
    int remainder = engine % 100;
    int calc = 1500+(engine + 100 - remainder);
    /*if (calc < 1000)
        return 10.00;*/
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