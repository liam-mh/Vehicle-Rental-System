#define _CRT_SECURE_NO_WARNINGS
#include "Car.h"
#include "Vehicle.h"
#include "Container.h"
#include <ctime>
#include <string>
#include <iostream>
using namespace std;

//Car::Car(int doors, int seats, Vehicle* vehicle)
//    : doors(doors), seats(seats)
//{}

Car::Car(int doors, int seats, string registration, string make, string model, int age)
    : doors(doors), seats(seats), Vehicle(registration, "Car", make, model, age)
{}

Car::~Car()
{}

//const void Car::displayCar()
//{   
//    displayVehicle();
//    cout << "Doors: " << doors << endl;
//    cout << "Seats: " << seats << endl;
//}

double Car::costPerDay() const
{
    time_t t = time(0);
    tm* tP = localtime(&t);
    int currentYear = (tP->tm_year)+1900;
    int age = currentYear - getVehicleAge();

    double calc = 2500-(age*150)-(doors*200);
    if (calc < 1000)
        return 10.00;
    return calc/100;
}

