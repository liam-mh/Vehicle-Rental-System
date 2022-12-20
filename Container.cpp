#include "HELPER_METHODS.h"
#define SPACE cout << "\n";
#define CLEAR_SCREEN system("cls");

#include "Container.h"
#include "Bike.h"
#include "Car.h"
#include "Disk.h"
#include "RentalHistory.h"

#include <iomanip>
#include <iostream>
#include <regex>
#include <string>
#include <windows.h> 
using namespace std;

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

// Display vector content
void Container::displayMainData(bool sortReg, bool sortCost)
{
    if (sortReg)
        sort(vehicles.begin(), vehicles.end(), [](Vehicle* lhs, Vehicle* rhs) 
            {return lhs->getVehicleReg() < rhs->getVehicleReg(); });
    if (sortCost)
        sort(vehicles.begin(), vehicles.end(), [](Vehicle* lhs, Vehicle* rhs) 
            {return lhs->costPerDay() < rhs->costPerDay();});

    vector<Vehicle*>::iterator it;
    int i = 0;

    cout << left << setw(24) << "Registration Number" << left << setw(17) << "Cost Per Day" << left << setw(17) << "Vehicle Type" << endl;
    cout << left << setw(24) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;
    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        cout << left << setw(24) << vehicles[i]->getVehicleReg();
        cout << left << setw(17) << setprecision(2) << fixed << vehicles[i]->costPerDay();
        string type = typeid(*vehicles[i]) == typeid(Car) ? "Car" : "Bike";
        cout << left << setw(17) << type << endl;
    }
    cout << left << setw(24) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;
}

void Container::displayFilteredData(string type, int filter, int filterValue)
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
    */

    string registration;
    if (type != "Car" && type != "Bike")
    {
        registration = type;
        type = filterValue == 1 ? "Car" : "Bike";
    }

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

    cout << left << setw(28) << "Registration Number" << left << setw(17) << "Cost Per Day" << left << setw(17) << "Make" << left << setw(17) << "Model" << endl;
    cout << left << setw(28) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;

    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        if (type == "Car" && typeid(*vehicles[i]) != typeid(Car)) continue;
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
    {
        cout << "NO RECORDS FOUND" << endl;
        cout << left << setw(28) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;
        SPACE
        cout << "9) Return to search menu" << endl;
        int option = NULL;
        cin >> option;
        if (option == 9)
            return;
    }
    else
    {
        cout << left << setw(28) << "-------------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << left << setw(17) << "------------" << endl;
        SPACE
            int option = selectFilteredVehicle();
        if (option == NULL)
            return;
        
        Vehicle* selection = vehicles[indexVector[option - 1]];
        RentalHistory* rh = Disk::readRentalHistoryFromDisk(selection);
        rh->rentalPage();
        delete rh;
    }  
}

int Container::selectFilteredVehicle()
{
    int option = NULL;
    cout << "Would you like to select a vehicle or return to the menu?" << endl;
    SPACE
    cout << "1) Select a vehicle" << endl;
    cout << "2) Return to search menu" << endl;
    cin >> option;
    SPACE
    if (option == 2)
        return NULL;

    option = NULL;
    cout << "Please enter the index of a vehicle: ";
    cin >> option;

    return option;
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
            createVehiclePage("Car");
        else if (option == 2)
            createVehiclePage("Bike");

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

void Container::createVehiclePage(string type)
{
    int option = 0,
        var1   = 0,
        var2   = 0,
        age    = 0;
    string registration, make, model;

    auto getVehicleSpecificDetails = [&](string type)
    {
        if (type == "Car")
            cout << "And the amount of doors, followed by the amount of seats." << endl;
        if (type == "Bike")
            cout << "And the number of wheels, followed by the enigine size." << endl;
        cin >> var1 >> var2;
    };
    auto displayVehicleSpecificDetails = [&](string type)
    {
        if (type == "Car")
        {
            cout << "Doors: " << var1 << endl;
            cout << "Seats: " << var2 << endl;
        }
        if (type == "Bike")
        {
            cout << "Wheels: " << var1 << endl;
            cout << "Engine size: " << var2 << "cc" << endl;
        }     
    };

    // Start user input
    registration = userEnterReg(true, true);
    cout << "Please enter the make: ";
    cin >> make;
    SPACE
    cout << "And model: ";
    cin >> model;
    SPACE
    cout << "The age: ";
    cin >> age;
    SPACE
    getVehicleSpecificDetails(type);
    SPACE

    cout << "Please confirm these details are correct:" << endl;
    cout << "Registration: " << registration << endl;
    cout << "Make and Model: " << make << " " << model << endl;
    displayVehicleSpecificDetails(type);
    SPACE
    cout << "1) Yes" << endl;
    cout << "2) No" << endl;
    cin >> option;
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
    else if (option == 2)
        cout << "Please retry and enter the correct details." << endl;
}

void Container::searchForVehiclePage(string type)
{
    int option = NULL;
    auto searchFilter = [&](string filter)
    {
        int input = 0;
        int filterNum = 0;

        cout << "Search by " << type << " " << filter << endl;
        if (filter == "engine")
            cout << "Please enter maximum " << filter << " size: ";
        else
            cout << "Please enter amount of " << filter << ": ";
        cin >> input;

        if (filter == "seats" || filter == "wheels")
            filterNum = 1;
        if (filter == "doors" || filter == "engine")
            filterNum = 2;

        CLEAR_SCREEN
        cout << "List of " << type << "s matching search filter: " << input << " " << filter << endl;
        SPACE
        displayFilteredData(type, filterNum, input);
        SPACE
    };

    while (option != 9)
    {
        CLEAR_SCREEN
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

        if (option == 1) 
        {
            cout << "Search by registration number" << endl;
            string registration;
            registration = userEnterReg(true, false);
            
            CLEAR_SCREEN
            cout << "Vehicles matching registration search:" << endl;
            SPACE
            displayFilteredData(registration, 0, type == "Car" ? 1 : 2);
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

string Container::userEnterReg(bool checkExists, bool alreadyExistsErrorMessage)
{
    /*
    * userEnterReg() loops until user enters correct format registration plate.
    * Filters:
    *   checkExists - Sees if registration is already in 'vehicles' vector using checkRegExists().
    *   alreadyExistsErrorMessage - Will display error message if already in 'vehicles' vector.
    * Returns the correct registrstion under filters.
    */

    bool correct;
    string registration;

    cout << "Please enter the registration plate." << endl;
    cout << "Must be in the following format where A = a letter, and 1 = a number:" << endl;
    cout << "AA11 AAA   example: DY62 HYT" << endl;
    cin.ignore();
    getline(cin, registration);
    SPACE
    if (checkExists)
        checkRegExists(registration, alreadyExistsErrorMessage) ? correct = false : correct = true;
    Vehicle::checkRegFormat(registration) ? correct = true : correct = false;

    while (correct == false)
    {
        bool alreadyExists = false;
        bool correctFormat = false;
        getline(cin, registration);
        SPACE
        if (checkExists)
            checkRegExists(registration, alreadyExistsErrorMessage) ? alreadyExists = true : correctFormat = false;
        else
            alreadyExists = false;
        Vehicle::checkRegFormat(registration) ? correctFormat = true : correctFormat = false;
        if (alreadyExists == false && correctFormat == true)
            correct = true;
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
                cout << "Vehicle registration is already in the database, please try again" << endl;
            return true;
        }
    }
    return false;
}
