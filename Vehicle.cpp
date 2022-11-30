#include "Vehicle.h"
#include <iostream>
#include <regex>

Vehicle::Vehicle(string registration, string type, string make, string model, int age) 
    : registration(registration), type(type), make(make), model(model), age(age) 
{}

Vehicle::~Vehicle() 
{};

ostream& operator<<(ostream& os, const Vehicle& v)
{
    os 
        << v.registration << ', '
        << v.type << ', '
        << v.make << ', '
        << v.model << ', '
        << v.age << "\n";

        return os;
}
