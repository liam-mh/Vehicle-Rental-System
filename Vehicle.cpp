#include "Vehicle.h"
#include <iostream>
#include <regex>
#include <fstream>

Vehicle::Vehicle(string registration, string type, string make, string model, int age) 
    : registration(registration), type(type), make(make), model(model), age(age) 
{}

Vehicle::~Vehicle() 
{};

const void Vehicle::displayVehicle()
{
    cout << "Registration: " << registration << endl;
    cout << "Make and Model: " << make << " " << model << endl;
    cout << "Age: " << age << endl;
}

//ofstream& operator<<(ofstream& of, const Vehicle& v)
//{
//    of 
//        << v.registration << ', '
//        << v.type << ', '
//        << v.make << ', '
//        << v.model << ', '
//        << v.age << "\n";
//    return of;
//}
