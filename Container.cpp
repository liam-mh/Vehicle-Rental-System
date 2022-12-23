#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define SPACE cout << "\n";
#define CLEAR_SCREEN system("cls");
#define VUI ValidateUserInput::getInstance()->validateUserInput
#define IN_1_OR_2 VUI(option, 2, 9);

#include "Bike.h"
#include "Car.h"
#include "RentalHistory.h"
#include "ValidateUserInput.h"
#include "Disk.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h> 
#include "container.h"

Container::Container()
{}
Container::~Container()
{
    Disk::writeVehiclesToDisk(this->vehicles);
    for (Vehicle* v : vehicles)
        delete v;
    vehicles.clear();   
}

// Vector manipulators 
void Container::addItem(Vehicle* vehicle)
{
    vehicles.push_back(vehicle);
}

void Container::removeItem(int index)
{
    Vehicle* vehicle = vehicles.at(index);
    Disk::removeRentalHistory(vehicle);
    vehicles.erase(vehicles.begin() + index);
}

void Container::operator+(Vehicle* newEntry)
{
    addItem(newEntry);
}

// Display vector content
void Container::sortByReg() {
    sort(vehicles.begin(), vehicles.end(), [](Vehicle* lhs, Vehicle* rhs)
        {return lhs->getVehicleReg() < rhs->getVehicleReg();});
    displayFilter = "\nFiltered by registration, in alphabetical order\n\n";
}
void Container::sortByCost() {
    sort(vehicles.begin(), vehicles.end(), [](Vehicle* lhs, Vehicle* rhs)
        {return lhs->costPerDay() < rhs->costPerDay();});
    displayFilter = "\nFiltered by cost per day, in ascending order\n\n";
}

void Container::displayMainData()
{
    vector<Vehicle*>::iterator it;
    int i = 0;

    // Printing data
    cout << displayFilter;
    cout << left << setw(24) << "Registration Number" << left << setw(17) << "Cost Per Day" << left << setw(17) << "Vehicle Type" << endl;
    cout << left << setw(24) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;
    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        cout << left << setw(24) << vehicles[i]->getVehicleReg();
        cout << left << setw(17) << setprecision(2) << fixed << vehicles[i]->costPerDay();
        cout << left << setw(17) << vehicles[i]->getVehicleType() << endl;
    }
    cout << left << setw(24) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;
}

void Container::displayFilteredData(string type, int &filter, int filterValue)
{
    /*
    * displayFilteredData() iterates thorugh the 'vehicles' vector and displays data under filters.
    * Filters:
    *   type - Passes derived class of Vehicle.
    *   filter - Controls the switch statement for what to search by:
    *       0 - registration.
    *       1 - seats for Car, wheels for Bike.
    *       2 - doors for Car, max engine size for Bike.
    *   filterValue - The number to search by under filter.
    * 
    * Function manipulation - Instead of overloading
    *   If searching by registration, that value is passed as parameter 'string type'.
    *   The type is then taken and converted under the parameter 'int filterValue',
    *   as this parameter has no use with the single filter of registration.
    * 
    * Function manipulation - Instead of return type int
    *   If there are vehicles matching the search criteria,
    *   the reference parameter 'int &filter' will be set to the int value of total filtered vehicles.
    */

    vector<int> indexVector;
    vector<Vehicle*>::iterator it;
    int i = 0;
    int filterCount = 0;
    auto printAndPush = [&]()
    {
        filterCount++;
        cout << left << setw(4) << filterCount;
        printFilteredVehicleData(type, i);
        indexVector.push_back(i);
    };

    // Check if searching by registration
    string registration;
    if (type != "Car" && type != "Bike")
    {
        registration = type;
        type = filterValue == 1 ? "Car" : "Bike";
    }

    // Display data
    cout << left << setw(28) << "Registration Number" << left << setw(17) << "Cost Per Day" << left << setw(17) << "Make" << left << setw(17) << "Model" << endl;
    cout << left << setw(28) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;
    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        if (type == "Car"  && typeid(*vehicles[i]) != typeid(Car)) continue;
        if (type == "Bike" && typeid(*vehicles[i]) != typeid(Bike)) continue;
        switch (filter)
        {
            case 0:
                if (registration == vehicles[i]->getVehicleReg())
                    printAndPush();
                break;
            case 1:
                if (filterValue == vehicles[i]->getVal1())
                    printAndPush();
                break;
            case 2:
                if (((type == "Bike") && (filterValue >= vehicles[i]->getVal2())) || (filterValue == vehicles[i]->getVal2()))
                    printAndPush(); 
                break;
        }
    }
    if (filterCount == 0)
        cout << "NO RECORDS FOUND" << endl;
    cout << left << setw(28) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;
    filter = filterCount;
}

void Container::printFilteredVehicleData(string type, int i)
{
    cout << left << setw(24) << vehicles[i]->getVehicleReg();
    cout << left << setw(17) << setprecision(2) << fixed << vehicles[i]->costPerDay();
    cout << left << setw(17) << vehicles[i]->getVehicleMake();
    cout << left << setw(17) << vehicles[i]->getVehicleModel() << endl;
}

// User input 
void Container::addItemPage()
{
    int option = NULL;

    while (option != 9)
    {
        CLEAR_SCREEN
        cout << "Add a vehicle" << endl;
        cout << "-------------" << endl;
        cout << "Here we will create a new vehicle to add." << endl;
        cout << "Do you wish to continue?" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        IN_1_OR_2
        if (option == 2)
            break;
        SPACE

        option = NULL;
        cout << "What kind of vehicle would you like to add? A car or bike?" << endl;
        cout << "1) Car" << endl;
        cout << "2) Bike" << endl;
        IN_1_OR_2
        if (option == 1)
            createVehiclePage("Car");
        else if (option == 2)
            createVehiclePage("Bike");

        cout << "Returning to the home page..." << endl;
        Sleep(3000);
    }
}

void Container::removeItemPage()
{
    int option = NULL;
    bool correct = true;
    string registration;

    while (option != 9)
    {
        CLEAR_SCREEN
        cout << "Remove a vehicle" << endl;
        cout << "----------------" << endl;
        cout << "Here we will remove a vehicle from the database." << endl;
        cout << "Do you wish to continue?" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        IN_1_OR_2
        if (option == 2)
            break;
        SPACE
        registration = userEnterReg(false, false);

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
            SPACE
            cout << "No vehicle in the database with this registration." << endl;
            cout << "Returning to the home page..." << endl;
            Sleep(5000);
            break;
        }
        SPACE

        option = NULL;
        cout << "Is this the correct vehicle?:" << endl;
        vehicles[index]->displayVehicle();
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        IN_1_OR_2
        if (option == 2)
            break;
        SPACE

        option = NULL;
        cout << "Once deleted, the vehicle cannot be retrieved." << endl;
        cout << "Final confirmation to delete:" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        IN_1_OR_2
        SPACE
        if (option == 1)
        {
            removeItem(index);
            cout << "Vehicle successfully removed." << endl;
        }
        cout << "Returning to the home page..." << endl;
        Sleep(3000);
        break;
    }
}

void Container::createVehiclePage(string type)
{
    int option = 0,
        var1 = 0,
        var2 = 0,
        age = 0;
    string registration, make, model;
    auto getCurrentYear = []() -> int
    {
        time_t t = time(0);
        tm* tP = localtime(&t);
        return (tP->tm_year) + 1900;
    };
    auto getVehicleSpecificDetails = [&](string type)
    {
        cout << left << setw(15) << (type == "Car" ? "Doors:" : "Wheels:"); VUI(var1);
        cout << left << setw(15) << (type == "Car" ? "Seats:" : "Engine size:"); VUI(var2);
    };
    auto displayVehicleSpecificDetails = [&](string type)
    {
        cout << left << setw(20) << (type == "Car" ? "Doors:" : "Wheels:") << var1 << endl;
        cout << left << setw(20) << (type == "Car" ? "Seats:" : "Engine size:") << var2 << endl;  
    };

    // User input
    CLEAR_SCREEN
    cout << "Please enter the following vehicle details: " << endl;
    SPACE
    registration = userEnterReg(true, true);
    cout << left << setw(15) << "Make:";  VUI(make);
    cout << left << setw(15) << "Model:"; VUI(model);
    cout << left << setw(15) << "Age:";   VUI(age);
    while (age > getCurrentYear() || age < 1800)
    {
        cout << "\nInvalid vehicle age, please retry.\n";
        cout << left << setw(15) << "Age:"; VUI(age);
    }
    getVehicleSpecificDetails(type);
   
    CLEAR_SCREEN
    cout << "Please confirm these details are correct:" << endl;
    cout << left << setw(20) << "Registration:" << registration << endl;
    cout << left << setw(20) << "Make and Model:" << make << " " << model << endl;
    displayVehicleSpecificDetails(type);
    SPACE
    cout << "1) Yes" << endl;
    cout << "2) No" << endl;
    IN_1_OR_2
    SPACE

    if (option == 1)
    {
        Vehicle* v = nullptr;
        if (type == "Car")
            v = new Car(var1, var2, registration, make, model, age);
        if (type == "Bike")
            v = new Bike(var1, var2, registration, make, model, age);
        addItem(v);
        cout << make << " " << model << " has been added" << endl;
    }
}

void Container::searchForVehiclePage(string type)
{
    int option = NULL;
    int filterNum = 0;
    auto searchFilter = [&](string filter)
    {
        int input = 0;

        cout << "Search by " << type << " " << filter << endl;
        if (filter == "engine")
            cout << "Please enter maximum " << filter << " size: ";
        else
            cout << "Please enter amount of " << filter << ": ";
        VUI(input);

        if (filter == "seats" || filter == "wheels")
            filterNum = 1;
        if (filter == "doors" || filter == "engine")
            filterNum = 2;

        CLEAR_SCREEN
        cout << "List of " << type << "s matching search filter: " << input << ", " << filter << endl;
        SPACE
        displayFilteredData(type, filterNum, input);
    };

    // User input 
    while (option != 9)
    {
        CLEAR_SCREEN
        cout << "Search for a vehicle" << endl;
        cout << "--------------------" << endl;
        cout << "Here we will search for a " << type << endl;
        cout << "Do you wish to continue?" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        IN_1_OR_2
        if (option == 2)
            break;
        SPACE

        option = NULL;
        cout << "What would you like to search by?" << endl;
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
        VUI(option, 3, 9);
        SPACE
       
        if (option == 1) 
        {
            cout << "Search by registration number" << endl;
            string registration;
            registration = userEnterReg(false, true);
            
            CLEAR_SCREEN
            cout << "Vehicles matching registration search:" << endl;
            SPACE
            displayFilteredData(registration, filterNum, type == "Car" ? 1 : 2);
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
        break;
    }

    // Rental History if selection
    int index = filterNum;
    if (index - 1 < 0)
    {
        cout << "Returning to the home page..." << endl;
        Sleep(3000);
        return;
    }
    SPACE
    selectForRentalHistory(index);
}

// Helping user input
void Container::selectForRentalHistory(int totalOptions)
{
    int option = 0;
    cout << "Would you like to select a vehicle or return to the menu?" << endl;
    cout << "1) Select a vehicle" << endl;
    cout << "2) Return to search menu" << endl;
    IN_1_OR_2
    if (option == 2)
        return;
    SPACE

    option = NULL;
    cout << "Please enter the index of a vehicle: ";
    VUI(option, totalOptions);
    option--;

    // Accessing rental history
    Vehicle* VehicleSelection = vehicles[option];
    RentalHistory* rh = Disk::readRentalHistoryFromDisk(VehicleSelection);
    rh->rentalPage();
    delete rh;
}

string Container::userEnterReg(bool alreadyExistsError, bool loop)
{
    /*
    * userEnterReg() loops until user enters correct format registration plate.
    * Filters:
    *   alreadyExistsErrorMessage - Will display error message if registration is already in 'vehicles' vector.
    * Returns the correct registrstion under filters.
    */

    string registration;

    cout << "Please enter the registration plate." << endl;
    cout << "Must be in the following format where A = a letter, and 1 = a number:" << endl;
    cout << "AA11 AAA   example: DY62 HYT" << endl;
    cout << left << setw(15) << "Registration: ";
    VUI(registration);
    bool alreadyExists = checkRegExists(registration, alreadyExistsError);

    while (alreadyExists && loop)
    {
        cout << "Please input a different registration." << endl;
        cout << left << setw(15) << "Registration: ";
        VUI(registration);
        alreadyExists = checkRegExists(registration, alreadyExistsError);
    }
   
    return registration;
}

bool Container::checkRegExists(string reg, bool alreadyExistsErrorMessage)
{
    vector<Vehicle*>::iterator it;
    int i = 0;
    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        if (vehicles[i]->getVehicleReg() == reg)
        {
            if (alreadyExistsErrorMessage)
                cout << "\nVehicle registration is already in the database." << endl;
            return true;
        }
    }
    return false;
}
