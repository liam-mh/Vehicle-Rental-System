#include "Disk.h"
#include "Bike.h"
#include "Car.h"
#include "Container.h"
#include "Rent.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdio.h>
using namespace std;

Disk::Disk() {}
Disk::~Disk() {}

// Container methods
Container* Disk::readVehiclesFromDisk()
{
    Container* container = new Container;

    ifstream input;
    input.open("Vehicle.csv");
    if (input.is_open())
    {
        string registration, type, make, model;
        int age  = 0,
            var1 = 0,
            var2 = 0;

        string line, singleValue, temp;

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

            Vehicle* v = nullptr;
            if (type == "Car") { v = new Car(var1, var2, registration, make, model, age); }
            if (type == "Bike") { v = new Bike(var1, var2, registration, make, model, age); }
            *container + v;
        }
        input.close();
    }
    else 
    {
        cout << "Error: Cannot read from vehicle directory." << endl;
    }
    return container;
};

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

// Rental methods
RentalHistory* Disk::readRentalHistoryFromDisk(Vehicle* vehicle)
{
    RentalHistory* rh = new RentalHistory(vehicle);

    ifstream input;
    input.open("RentalHistory.csv");
    if (input.is_open())
    {
        string registration, startDate, endDate, name, address, number;
        int rentNum = 0,
            daysRented = 0;
        double periodCost = 0.00;

        string line, singleValue, temp;

        while (getline(input, line))
        {
            stringstream ss(line);
            getline(ss, registration, ',');

            if (registration == vehicle->getVehicleReg())
            {
                getline(ss, temp, ','); rentNum = stoi(temp);
                getline(ss, temp, ','); daysRented = stoi(temp);
                getline(ss, temp, ','); periodCost = stod(temp);
                getline(ss, startDate, ',');
                getline(ss, endDate, ',');
                getline(ss, name, ',');
                getline(ss, address, ',');
                getline(ss, number, ',');

                Rent* r = new Rent(registration, rentNum, daysRented, periodCost, startDate, endDate, name, address, number);
                *rh + r;
            }
        }
        input.close();
    }
    else 
        cout << "Error: Cannot read from rental history directory." << endl;
    
    return rh;
};

void Disk::writeRentalHistoryToDisk(Rent** data, int totalRents, int newRents)
{
    ofstream output;
    output.open("RentalHistory.csv", fstream::app);

    int i = 0;

    for (int i = totalRents-newRents; i < totalRents; i++)
    {
        if (output.is_open())
        {
            Rent* rent = data[i];
            output << rent;
        }
        else
            cout << "Error: Cannot write to vehicle directory." << endl;
    }
    output.close();
}

void Disk::removeRentalHistory(string RemoveRegistration)
{
    ifstream input;
    input.open("RentalHistory.csv");

    if (input.is_open())
    {
        ofstream output;
        output.open("temp.csv");
        string line, singleValue, temp;

        string registration, startDate, endDate, name, address, number;
        int rentNum = 0,
            daysRented = 0;
        double periodCost = 0.00;

        while (getline(input, line))
        {
            stringstream ss(line);
            getline(ss, registration, ',');

            if (registration != RemoveRegistration)
            {
                getline(ss, temp, ','); rentNum = stoi(temp);
                getline(ss, temp, ','); daysRented = stoi(temp);
                getline(ss, temp, ','); periodCost = stod(temp);
                getline(ss, startDate, ',');
                getline(ss, endDate, ',');
                getline(ss, name, ',');
                getline(ss, address, ',');
                getline(ss, number, ',');

                Rent* r = new Rent(registration, rentNum, daysRented, periodCost, startDate, endDate, name, address, number);
                if (output.is_open())
                    output << r;
                else
                    cout << "Error: Cannot write to vehicle directory." << endl;
            }
        }
        input.close();
        output.close();
        if (remove("RentalHistory.csv") != 0)
            cout << "Error: Cannot remove file" << endl;
        if (rename("temp.csv", "RentalHistory.csv") != 0)
            cout << "Error: Cannot rename file" << endl;
    }
    else
        cout << "Error: Cannot read from rental history directory." << endl;
}
