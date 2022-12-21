#include "Container.h"
#include "Vehicle.h"
#include "Bike.h"
#include "Car.h"
#include <iomanip>
#define _CRT_SECURE_NO_WARNINGS
#define SPACE cout << "\n";
#define CLEAR_SCREEN system("cls");
#define IN_1_OR_2 validateUserInput(option, 2, 9);

#include "Pages.h"
#include "ValidateUserInput.h"
#include <windows.h> 

#include <iostream>
using namespace std;

void Pages::addItemPage(Container* container)
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
                createVehiclePage(container, "Car");
            else if (option == 2)
                createVehiclePage(container, "Bike");

        cout << "Returning to the home page..." << endl;
        Sleep(3000);
    }
}

void Pages::createVehiclePage(Container* container, string type)
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
        cout << left << setw(15) << (type == "Car" ? "Doors:" : "Wheels:"); validateUserInput(var1);
        cout << left << setw(15) << (type == "Car" ? "Seats:" : "Engine size:"); validateUserInput(var2);
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
        registration = userEnterReg(true);
    cout << left << setw(15) << "Make:";  validateUserInput(make);
    cout << left << setw(15) << "Model:"; validateUserInput(model);
    cout << left << setw(15) << "Age:";   validateUserInput(age);
    while (age > getCurrentYear() || age < 1800)
    {
        cout << "\nInvalid vehicle age, please retry.\n";
        cout << left << setw(15) << "Age:"; validateUserInput(age);
    }
    getVehicleSpecificDetails(type);

    CLEAR_SCREEN
        cout << "Please confirm these details are correct:" << endl;
    cout << left << setw(20) << "Registration:" << registration << endl;
    cout << left << setw(20) << "Make and Model:" << make << " " << model << endl;
    cout << left << setw(20) << "Age:" << age << endl;
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
            container->addItem(v);
            cout << make << " " << model << " has been added" << endl;
        }
}