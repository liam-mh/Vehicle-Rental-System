#define _CRT_SECURE_NO_WARNINGS
#include "Vehicle.h"

#include <iomanip>
#include <iostream>
#include <regex>

Vehicle::Vehicle(string registration, string type, string make, string model, int age) 
    : registration(registration), type(type),  model(model), age(age) 
{
    this->make = new char[make.length() + 1];
    strcpy(this->make, make.c_str());
}

Vehicle::~Vehicle() 
{
    delete make;
    make = nullptr;
}

const void Vehicle::displayVehicle()
{
    cout << left << setw(20) << "Registration: " << registration << endl;
    cout << left << setw(20) << "Make and Model: " << make << " " << model << endl;
    cout << left << setw(20) << "Age: " << age << endl;
}
