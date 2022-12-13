#include "Disk.h"
#include "Bike.h"
#include "Car.h"
#include "Container.h"
#include "Vehicle.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <utility>
using namespace std;


Disk::Disk() {}
Disk::~Disk() {}

Container* Disk::readVehiclesFromDisk()
{
    Container* container = new Container;

    ifstream input;
    input.open("Vehicle.csv");
    if (input.is_open())
    {
        string registration, type, make, model, temp;
        int age  = 0,
            var1 = 0,
            var2 = 0;

        string line, singleValue;

        while (getline(input, line))
        {
            stringstream ss(line);
            getline(ss, temp, ','); var1 = stoi(temp);
            getline(ss, temp, ','); var2 = stoi(temp);
            getline(ss, registration, ',');
            getline(ss, type, ',');
            getline(ss, make, ',');
            getline(ss, model, ',');
            getline(ss, temp, ','); age = stoi(temp);

            if (type == "Car")
            {
                Vehicle* v = new Car(var1, var2, registration, make, model, age);
                container->addItem(v);
            }
            if (type == "Bike")
            {
                Vehicle* v = new Bike(var1, var2, registration, make, model, age);
                container->addItem(v);
            }
        }
        input.close();
    }
    else {
        cout << "Error: Cannot read from vehicle directory." << endl;
    }
    return container;
};

/*
void Disk::writeVehicleToDisk(Vehicle* data)
{
    ofstream output;
    output.open("Vehicle.csv");
    if (output.is_open())
    {
        Car* carTest = dynamic_cast<Car*>(data);
        if (carTest != nullptr)
            output << carTest;
        
        Bike* bikeTest = dynamic_cast<Bike*>(data);
        if (bikeTest != nullptr)
            output << bikeTest;
           
        output.close();
    }
    else {
        cout << "Error: Cannot write to vehicle directory." << endl;
    }
}
*/


void Disk::writeVehiclesToDisk(vector<Vehicle*> data)
{
    vector<Vehicle*>::iterator it;
    int i = 0;

    ofstream output;
    output.open("Vehicle.csv");

    for (it = data.begin(); it != data.end(); it++, i++)
    {
        if (output.is_open())
        {
            Car* carTest = dynamic_cast<Car*>(data[i]);
            if (carTest != nullptr)
                output << carTest;

            Bike* bikeTest = dynamic_cast<Bike*>(data[i]);
            if (bikeTest != nullptr)
                output << bikeTest;
        }
        else 
        {
            cout << "Error: Cannot write to vehicle directory." << endl;
        }
    }

    output.close();
}


void Disk::writeRentalHistoryToDisk(Rent** data)
{
    ofstream output;
    output.open("RentalHistory.csv");

    for (int i = 0; i < 1; i++)
    {
        if (output.is_open())
        {
            Rent* rent = data[i];
            output << rent;
        }
        else
        {
            cout << "Error: Cannot write to vehicle directory." << endl;
        }
    }

    output.close();
}