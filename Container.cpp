#include "HELPER_METHODS.h"
#define SPACE HELPER_METHODS::SPACE();

#include "Container.h"
#include "Bike.h"
#include "Car.h"
#include "Disk.h"
#include "RentalHistory.h"
#include "Vehicle.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <windows.h> // causes std error
using namespace std;


Container::Container()
{}
Container::~Container()
{}

void Container::addItem(Vehicle* vehicle)
{
    vehicles.push_back(vehicle);
}

void Container::removeItem(string reg)
{
    vector<Vehicle*>::iterator it;
    int i = 0;
    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        if (vehicles[i]->getVehicleReg() == reg)
            vehicles.erase(vehicles.begin() + i);
    }
}
void Container::removeItem(int index)
{
    vehicles.erase(vehicles.begin() + index);
}

void Container::printData(string type, int i)
{
    if ((type == "Car") && (typeid(*vehicles[i]) == typeid(Car)))
    {
        cout << left << setw(17) << setprecision(2) << fixed << vehicles[i]->costPerDay();
        cout << left << setw(17) << vehicles[i]->getVehicleMake();
        cout << left << setw(17) << vehicles[i]->getVehicleModel() << endl;
    }
    else
    {
        cout << left << setw(17) << setprecision(2) << fixed << vehicles[i]->costPerDay();
        cout << left << setw(17) << vehicles[i]->getVehicleMake();
        cout << left << setw(17) << vehicles[i]->getVehicleModel() << endl;
    }
}

void Container::displayMainData(bool sortReg, bool sortCost)
{
    if (sortReg)
        sort(vehicles.begin(), vehicles.end(), sortByReg());
    if (sortCost)
        sort(vehicles.begin(), vehicles.end(), sortByCost());

    cout << left << setw(24) << "Registration Number" << left << setw(17) << "Cost Per Day" << left << setw(17) << "Vehicle Type" << endl;
    cout << left << setw(24) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;
    vector<Vehicle*>::iterator it;
    int i = 0;
    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        cout << left << setw(24) << vehicles[i]->getVehicleReg();

        if ((typeid(*vehicles[i]) == typeid(Car)))
        {
            cout << left << setw(17) << setprecision(2) << fixed << vehicles[i]->costPerDay();
            cout << left << setw(17) << "Car" << endl;
        }
        else
        {
            cout << left << setw(17) << setprecision(2) << fixed << vehicles[i]->costPerDay();
            cout << left << setw(17) << "Bike" << endl;
        }
    }
    cout << left << setw(24) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;
}

void Container::displayFilteredData(string type, int filter, string filterValue)
{
    vector<Vehicle*>::iterator it;
    int i = 0;
    int filterCount = 0;

    cout << left << setw(28) << "Registration Number" << left << setw(17) << "Cost Per Day" << left << setw(17) << "Make" << left << setw(17) << "Model" << endl;
    cout << left << setw(28) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;

    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        if (filterValue == vehicles[i]->getVehicleReg())
        {
            filterCount++;
            cout << left << setw(4) << filterCount << left << setw(24) << vehicles[i]->getVehicleReg();
            printData(type, i);
        }
    }
    cout << left << setw(28) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;
}
void Container::displayFilteredData(string type, int filter, int filterValue)
{
    vector<Vehicle*> temp;

    vector<Vehicle*>::iterator it;
    int i = 0;
    int filterCount = 0;

    cout << left << setw(28) << "Registration Number" << left << setw(17) << "Cost Per Day" << left << setw(17) << "Make" << left << setw(17) << "Model" << endl;
    cout << left << setw(28) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;

    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        switch (filter)
        {
        case 1:
            if (filterValue == vehicles[i]->getVal1())
            {
                if (type == "Bike")
                    if (typeid(*vehicles[i]) == typeid(Car))
                        break;
                filterCount++;
                temp.push_back(vehicles[i]);
                //cout << left << setw(4) << filterCount << left << setw(24) << vehicles[i]->getVehicleReg();
                //printData(type, i);
            }
            break;
        case 2:
            if (((type == "Bike") && (filterValue >= vehicles[i]->getVal2())) || (filterValue == vehicles[i]->getVal2()))
            {
                if (type == "Bike")
                    if (typeid(*vehicles[i]) == typeid(Car))
                        break;
                filterCount++;
                temp.push_back(vehicles[i]);
                //cout << left << setw(4) << filterCount << left << setw(24) << vehicles[i]->getVehicleReg();
                //printData(type, i);
            }
            break;
        }
    }
    if (filterCount == 0)
    {
        cout << "NO RECORDS FOUND" << endl;
        cout << left << setw(28) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;
        return;
    }
    
    // printing filtered data
    i = 0;
    for (it = temp.begin(); it != temp.end(); it++, i++)
    {
        cout << left << setw(4) << i+1 << left << setw(24) << vehicles[i]->getVehicleReg();
        printData(type, i);
    }

    SPACE
    int option = selectFilteredVehicle();
    if (option == NULL)
        return;

    Vehicle* selection = temp[option];
    RentalHistory* rh = new RentalHistory(selection);
    rh->rentalPage();
        
}
int Container::selectFilteredVehicle()
{
    int option = NULL;
    cout << "Would you like to select a vehicle or return to the menu?" << endl;
    SPACE
    cout << "1) Select a vehicle" << endl;
    cout << "2) Return to main menu" << endl;
    cin >> option;
    SPACE
    if (option == 2)
        return NULL;

    option = NULL;
    cout << "Please enter the index of a vehicle: ";
    cin >> option;

    return option;
}


void Container::addItemPage()
{
    int option = NULL;

    while (option != 9)
    {
        cout << "Add a vehicle" << endl;
        cout << "-------------" << endl;
        cout << "Here we will create a new vehicle to add." << endl;
        cout << "Do you wish to continue?" << endl;
        SPACE
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        cin >> option;
        if (option == 2)
            break;

        option = NULL;
        cout << "What kind of vehicle would you like to add? A car or bike?" << endl;
        SPACE
            cout << "1) Car" << endl;
        cout << "2) Bike" << endl;
        cin >> option;
        SPACE
        if (option == 1)
            create("Car");
        else if (option == 2)
            create("Bike");

        option = NULL;
        cout << "What would you like to do now?" << endl;
        SPACE
        cout << "1) Create another vehicle" << endl;
        cout << "2) Return to main menu" << endl;
        cin >> option;
        SPACE
        if (option == 2)
            break;
    }
}

void Container::removeItemPage()
{
    string registration;
    int option = NULL;
    bool correct = true;

    while (option != 9)
    {
        cout << "Remove a vehicle" << endl;
        cout << "----------------" << endl;
        cout << "Here we will remove a vehicle from the database." << endl;
        cout << "Do you wish to continue?" << endl;
        SPACE
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        cin >> option;
        SPACE
            if (option == 2)
                break;

        cout << "Please enter the registration of the vehicle you wish to remove:" << endl;
        cout << "Must be in the following format where A = a letter, and 1 = a number:" << endl;
        cout << "AA11 AAA   example: DY62 HYT" << endl;
        cin.ignore();
        getline(cin, registration);
        SPACE
            Vehicle::checkRegFormat(registration) ? correct = true : correct = false;

        while (correct == false)
        {
            getline(cin, registration);
            SPACE
                Vehicle::checkRegFormat(registration) ? correct = true : correct = false;
        }

        vector<Vehicle*>::iterator it;
        int index = 0;
        for (it = vehicles.begin(); it != vehicles.end(); it++, index++)
        {
            if (vehicles[index]->getVehicleReg() == registration)
            {
                correct = true;
                break;
            }
            else
                correct = false;
        }
        if (correct == false)
        {
            cout << "No vehicle in the database with this registration." << endl;
            cout << "Returning to the home page..." << endl;
            Sleep(3000);
            break;
        }


        option = NULL;
        cout << "Is this the correct vehicle?:" << endl;
        vehicles[index]->displayVehicle();
        SPACE
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        cin >> option;
        SPACE
            if (option == 2)
                break;

        option = NULL;
        cout << "Once deleted the vehicle cannot be retrieved" << endl;
        cout << "Final confirmation to delete:" << endl;
        SPACE
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        cin >> option;
        SPACE
        if (option == 1)
        {
            removeItem(index);
            cout << "Vehicle successfully removed." << endl;
        }
        if (option == 2)
            break;

        option = NULL;
        cout << "What would you like to do now?" << endl;
        SPACE
        cout << "1) Remove another vehicle" << endl;
        cout << "2) Return to main menu" << endl;
        cin >> option;
        SPACE
        if (option == 2)
            break;
    }
}

void Container::create(string type)
{
    int option = 0,
        doors = 0,
        seats = 0,
        wheels = 0,
        engine = 0,
        age = 0;
    string registration, make, model;
    bool correct = true;

    registration = enterReg(true);

    cout << "Please enter the make: ";
    cin >> make;
    SPACE

    cout << "And model: ";
    cin >> model;
    SPACE

    cout << "The age: ";
    cin >> age;
    SPACE

    if (type == "Car")
    {
        cout << "And the amount of doors, followed by the amount of seats." << endl;
        cin >> doors >> seats;
        SPACE

        cout << "Please confirm these details are correct:" << endl;
        cout << "Registration: " << registration << endl;
        cout << "Make and Model: " << make << " " << model << endl;
        cout << "Age: " << age << endl;
        cout << "Doors: " << doors << endl;
        cout << "Seats: " << seats << endl;
    }
    if (type == "Bike")
    {
        cout << "And the number of wheels, followed by the enigine size." << endl;
        cin >> wheels >> engine;
        SPACE

        cout << "Please confirm these details are correct:" << endl;
        cout << "Registration: " << registration << endl;
        cout << "Make and Model: " << make << " " << model << endl;
        cout << "Age: " << age << endl;
        cout << "Wheels: " << wheels << endl;
        cout << "Engine size: " << engine << "cc" << endl;
    }

    SPACE
    cout << "1) Yes" << endl;
    cout << "2) No" << endl;
    cin >> option;
    SPACE
    if (option == 1)
    {
        if (type == "Car")
        {
            Vehicle* v = new Car(doors, seats, registration, make, model, age);
            addItem(v);
        }
        if (type == "Bike")
        {
            Vehicle* v = new Bike(wheels, engine, registration, make, model, age);
            addItem(v);
        }
        cout << make << " " << model << " has been added" << endl;
    }
    else if (option == 2)
        cout << "Please retry and enter the correct details." << endl;
}

bool Container::checkRegExists(string reg, bool errorMessage)
{
    vector<Vehicle*>::iterator it;
    int i = 0;
    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        if (vehicles[i]->getVehicleReg() == reg)
        {
            if (errorMessage)
                cout << "Vehicle registration is already in the database, please try again" << endl;
            return true;
        }
    }
    return false;
}

void Container::save()
{
    vector<Vehicle*>::iterator it;
    int i = 0;
    ofstream output;
    output.open("Vehicle.csv");
    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        cout << vehicles[i]->getVehicleReg() << endl;
        if (output.is_open())
        {
            Car* carTest = dynamic_cast<Car*>(vehicles[i]);
            if (carTest != nullptr)
                output << carTest; 

            Bike* bikeTest = dynamic_cast<Bike*>(vehicles[i]);
            if (bikeTest != nullptr)
                output << bikeTest; 
        }
        else {
            cout << "Error: Cannot write to vehicle directory." << endl;
        }
    }
    output.close();
}

void Container::search(string type)
{
    int option = NULL;

    while (option != 9)
    {
        cout << "Search for a vehicle" << endl;
        cout << "--------------------" << endl;
        cout << "Here we will search for a " << type << endl;
        cout << "Do you wish to continue?" << endl;
        SPACE
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        cin >> option;
        SPACE
        if (option == 2)
            break;

        option = NULL;
        cout << "What would you like to search by?" << endl;
        SPACE;
        cout << "1) Registration number" << endl;
        if (type == "Car")
        {
            cout << "2) Number of seats" << endl;
            cout << "3) Number of doors" << endl;
        }
        if (type == "Bike")
        {
            cout << "2) Number of wheels" << endl;
            cout << "3) Max engine size" << endl;
        }
        cout << "9) Return to main menu" << endl;
        cin >> option;
        SPACE

        auto searchFilter = [&](string filter)
        {
            cout << "Search by " << type << " " << filter << endl;
            if (filter == "engine")
                cout << "Please enter maximum " << filter << " size: ";
            else
                cout << "Please enter amount of " << filter << ": ";
            int input = 0;
            cin >> input;

            int filterNum = 0;
            if (filter == "seats" || filter == "wheels")
                filterNum = 1;
            if (filter == "doors" || filter == "engine")
                filterNum = 2;

            SPACE
            cout << "List of " << type << "s matching search filter: " << input << " " << filter << endl;
            SPACE
            displayFilteredData(type, filterNum, input);
            SPACE
        };

        if (option == 1) // search by reg
        {
            cout << "Search by registration number" << endl;
            string registration;
            registration = enterReg(true);

            cout << "List of " << type << "s matching search" << endl;
            SPACE
            displayFilteredData(type, 0, registration);
            SPACE
        }
        if (type == "Car")
        {
            if (option == 2)
                searchFilter("seats");
            if (option == 3)
                searchFilter("doors");
        }
        if (type == "Bike")
        {
            if (option == 2)
                searchFilter("wheels");
            if (option == 3)
                searchFilter("engine");
        }
    }
}

string Container::enterReg(bool checkExists)
{
    bool correct;
    string registration;

    cout << "Please enter the registration plate." << endl;
    cout << "Must be in the following format where A = a letter, and 1 = a number:" << endl;
    cout << "AA11 AAA   example: DY62 HYT" << endl;
    cin.ignore();
    getline(cin, registration);
    SPACE
        if (checkExists)
            checkRegExists(registration, false) ? correct = false : correct = true;
    Vehicle::checkRegFormat(registration) ? correct = true : correct = false;

    while (correct == false)
    {
        bool e;
        bool f;
        getline(cin, registration);
        SPACE
            if (checkExists)
                checkRegExists(registration, false) ? e = true : e = false;
            else
                e = false;

        Vehicle::checkRegFormat(registration) ? f = true : f = false;
        if (e == false && f == true)
            correct = true;
    }
    return registration;
}
