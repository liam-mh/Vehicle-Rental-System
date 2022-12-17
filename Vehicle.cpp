#include "Vehicle.h"

#include <fstream>
#include <iostream>
#include <regex>


Vehicle::Vehicle(string registration, string type, string make, string model, int age) 
    : registration(registration), type(type), make(make), model(model), age(age) 
{}

Vehicle::~Vehicle() 
{}

const void Vehicle::displayVehicle()
{
    cout << "Registration: " << registration << endl;
    cout << "Make and Model: " << make << " " << model << endl;
    cout << "Age: " << age << endl;
}

bool Vehicle::checkRegFormat(string reg)
{
    regex r("([A-HJ-PR-Y]{2}([0][1-9]|[1-9][0-9])|[A-HJ-PR-Y]{1}([1-9]|[1-2][0-9]|30|31|33|40|44|55|50|60|66|70|77|80|88|90|99|111|121|123|222|321|333|444|555|666|777|888|999|100|200|300|400|500|600|700|800|900))[ ][A-HJ-PR-Z]{3}$");
    if (regex_match(reg, r) && reg.size() == 8)
        return true;
    cout << "Invalid format: Please retry in the correct format AA11 AAA" << endl;
    return false;
}

/*
bool operator<(const Vehicle& lhs, const Vehicle& rhs)
{
    return lhs.registration < rhs.registration;
}
*/