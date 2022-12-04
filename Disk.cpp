#include "Disk.h"
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
                Car* c = new Car(var1, var2, registration, make, model, age);
                container->addItem(c);
            }
            
        }
        input.close();
    }
    else {
        cout << "Error: Cannot read from vehicle directory." << endl;
    }
    return container;
};


void Disk::writeVehicleToDisk(Vehicle* data)
{
    ofstream output;
    output.open("Vehicle.csv");
    if (output.is_open())
    {
        Car* test = dynamic_cast<Car*>(data);
        if (test != nullptr)
            output << test;
        else
            cout << "not a car" << endl;
           
        output.close();
    }
    else {
        cout << "Error: Cannot write to vehicle directory." << endl;
    }
}

/*
void Disk::writeVehiclesToDisk(Container* data)
{
    ofstream output;
    output.open("Vehicle.csv");
    if (output.is_open())
    {
        vector<Vehicle*>::iterator it;
        int i = 0;
        for (it = data.begin(); it != data.end(); it++, i++)
        {
            Car* test = dynamic_cast<Car*>(data);
            if (test != nullptr)
                output << test;
            else
                cout << "not a car" << endl;
        }

        output.close();
    }
    else {
        cout << "Error: Cannot write to vehicle directory." << endl;
    }
}
*/

