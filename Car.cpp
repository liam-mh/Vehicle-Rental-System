#define _CRT_SECURE_NO_WARNINGS

#include "Car.h"

#include <ctime>
#include <fstream>

Car::Car(int doors, int seats, string registration, string make, string model, int age)
    : doors(doors), seats(seats), Vehicle(registration, "Car", make, model, age)
{}

Car::~Car()
{}

double Car::costPerDay() const
{
    /*
    * Code Snippet - Highlighted below
    * https://stackoverflow.com/questions/58151350/more-elegant-way-to-get-the-current-year-in-c
    * I have learnt from this forum some methods on how to obtain the current year.
    * I have modified it slightly to be more understandbale in this instance.
    * It does however require the _CRT_SECURE_NO_WARNINGS declaration at the top.
    */

    // ----------------------------------
    time_t t = time(0);
    tm* tP = localtime(&t);
    int currentYear = (tP->tm_year)+1900;
    // ----------------------------------
    int age = currentYear - getVehicleAge();
    double calc = 2500-(age*150)-(doors*200);
    if (calc < 1000)
        return 10.00;
    return calc/100;
}

ofstream& operator<<(ofstream& of, const Car* v)
{
    of 
        << v->doors << ","
        << v->seats << ","
        << v->getVehicleReg() << ","
        << "Car" << ","
        << v->getVehicleMake() << ","
        << v->getVehicleModel() << ","
        << v->getVehicleAge() << "\n";
    return of;
}

