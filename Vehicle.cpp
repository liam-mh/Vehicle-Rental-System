#include "Vehicle.h"

Vehicle::Vehicle(string registration, string type, string make, string model, int age) 
    : registration(registration), type(type), make(make), model(model), age(age) 
{}

Vehicle::~Vehicle() 
{};