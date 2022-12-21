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

bool Vehicle::checkRegFormat(string reg)
{
    /*
    * checkRegFormat() Uses regex to check a correct registration format is entered.
    * Returns a bool.
    */

    /*
    * Code Snippet - Highlighted below
    * https://regexlib.com/REDetails.aspx?regexp_id=1981
    * I have used the regex template from this website and learnt how to use regex expressions on others.
    * I couldn't find a better expression as this one will also accept AA1 AAA, as I just need AA11 AAA format.
    * To combat this I have applied a length filter to only return correct if 8 characters long.
    */

    // ----------------------------------
    regex r("([A-HJ-PR-Y]{2}([0][1-9]|[1-9][0-9])|[A-HJ-PR-Y]{1}([1-9]|[1-2][0-9]|30|31|33|40|44|55|50|60|66|70|77|80|88|90|99|111|121|123|222|321|333|444|555|666|777|888|999|100|200|300|400|500|600|700|800|900))[ ][A-HJ-PR-Z]{3}$");
    // ----------------------------------
    if (regex_match(reg, r) && reg.size() == 8)
        return true;
    cout << "\nInvalid format: Please retry in the correct format AA11 AAA" << endl;
    return false;
}

bool Vehicle::operator<(const Vehicle* rhs)
{
    return registration < rhs->getVehicleReg();
}