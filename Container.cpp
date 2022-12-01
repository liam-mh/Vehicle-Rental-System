#include "Container.h"
#include "Car.h"
#include "Bike.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <regex>
#include <windows.h>
using namespace std;

Container::Container() {};
Container::~Container() {};

void Container::addItem(Vehicle* vehicle)
{ vehicles.push_back(vehicle); }

void Container::removeItem(string reg)
{
    vector<Vehicle*>::iterator it;
    int i = 0;
    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        if (vehicles[i]->getVehicleReg() == reg)
            vehicles.erase(vehicles.begin()+i);
    }
}
void Container::removeItem(int index)
{ vehicles.erase(vehicles.begin() + index); }

//void Container::displayReg()
//{
//    cout << "Displaying Items" << std::endl;
//    for (int i = 0; i < vehicles.size(); i++) 
//    {
//        cout << vehicles[i]->getVehicleReg() << " ";
//    }
//}

void Container::displayMainData()
{
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

void Container::addItemPage()
{ 
    int option = NULL;

    while (option != 9)
    {
        cout << "Add a vehicle" << endl;
        cout << "-------------" << endl;
        cout << "Here we will create a new vehicle to add." << endl;
        cout << "Do you wish to continue?" << endl;
        cout << "" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        cin >> option;
        cout << "" << endl;
        if (option == 2)
            break;

        option = NULL;
        cout << "What kind of vehicle would you like to add? A car or bike?" << endl;
        cout << "" << endl;
        cout << "1) Car" << endl;
        cout << "2) Bike" << endl;
        cin >> option;
        cout << "" << endl;
        if (option == 1)
            createCar();
        else if (option == 2)
            createBike();
   
        option = NULL;
        cout << "What would you like to do now?" << endl;
        cout << "" << endl;
        cout << "1) Create another vehicle" << endl;
        cout << "2) Return to main menu" << endl;
        cin >> option;
        cout << "" << endl;
        if (option == 2)
            break;
  
        cout << "**END OF addItemPage LOOP" << endl;
    } 
    cout << "**END OF addItemPage()" << endl;
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
        cout << "" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        cin >> option;
        cout << "" << endl;
        if (option == 2)
            break;

        cout << "Please enter the registration of the vehicle you wish to remove:" << endl;
        cout << "Must be in the following format where A = a letter, and 1 = a number:" << endl;
        cout << "AA11 AAA   example: DY62 HYT" << endl;
        cin.ignore();
        getline(cin, registration);
        cout << "" << endl;
        checkRegFormat(registration) ? correct = true : correct = false;

        while (correct == false)
        {
            getline(cin, registration);
            cout << "" << endl;
            checkRegFormat(registration) ? correct = true : correct = false;
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
        cout << "" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        cin >> option;
        cout << "" << endl;
        if (option == 2)
            break;

        option = NULL;
        cout << "Once deleted the vehicle cannot be retrieved" << endl;
        cout << "Final confirmation to delete:" << endl;
        cout << "" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        cin >> option;
        cout << "" << endl;
        if (option == 1)
        {
            removeItem(index);
            cout << "Vehicle successfully removed." << endl;
        }
        if (option == 2)
            break;

        option = NULL;
        cout << "What would you like to do now?" << endl;
        cout << "" << endl;
        cout << "1) Remove another vehicle" << endl;
        cout << "2) Return to main menu" << endl;
        cin >> option;
        cout << "" << endl;
        if (option == 2)
            break;

        cout << "**END OF addItemPage LOOP" << endl;
    }
    cout << "**END OF addItemPage()" << endl;
}

void Container::createCar()
{
    int option, doors, seats, age = 0;
    string registration, type, make, model;
    bool correct = true;

    cout << "Please enter the registration plate." << endl;
    cout << "Must be in the following format where A = a letter, and 1 = a number:" << endl;
    cout << "AA11 AAA   example: DY62 HYT" << endl;
    cin.ignore();
    getline(cin, registration);
    cout << "" << endl;
    checkRegExists(registration) ? correct=false : correct=true;
    checkRegFormat(registration) ? correct=true : correct=false;

    while (correct == false)
    {
        bool e;
        bool f;
        getline(cin, registration);
        cout << "" << endl;
        checkRegExists(registration) ? e=true : e=false;
        checkRegFormat(registration) ? f=true : f=false;
        if (e==false && f==true)
            correct = true;
    } 

    cout << "" << endl;

    cout << "Please enter the make: ";
    cin >> make;
    cout << endl;

    cout << "And model: ";
    cin >> model;
    cout << endl;
    
    cout << "The age: ";
    cin >> age;
    cout << "" << endl;

    cout << "And the amount of doors, followed by the amount of seats." << endl;
    cin >> doors >> seats;
    cout << "" << endl;

    cout << "Please confirm these details are correct:" << endl;
    cout << "Registration: " << registration << endl;
    cout << "Make and Model: " << make << " " << model << endl;
    cout << "Age: " << age << endl;
    cout << "Doors: " << doors << endl;
    cout << "Seats: " << seats << endl;
    cout << "" << endl;
    cout << "1) Yes" << endl;
    cout << "2) No" << endl;
    cin >> option;
    cout << "" << endl;
    if (option == 1)
    {
        Vehicle* v = new Car(doors, seats, registration, make, model, age);
        addItem(v);
        cout << make << " " << model << " has been added" << endl;
    }
    else if (option == 2)
        cout << "Please retry and enter the correct details." << endl;
  
}

void Container::createBike()
{
    cout << "Create a bike" << endl;
}


bool Container::checkRegFormat(string reg)
{
    regex r("([A-HJ-PR-Y]{2}([0][1-9]|[1-9][0-9])|[A-HJ-PR-Y]{1}([1-9]|[1-2][0-9]|30|31|33|40|44|55|50|60|66|70|77|80|88|90|99|111|121|123|222|321|333|444|555|666|777|888|999|100|200|300|400|500|600|700|800|900))[ ][A-HJ-PR-Z]{3}$");
    if (regex_match(reg, r) && reg.size() == 8)
        return true;
    cout << "Invalid format: Please retry in the correct format AA11 AAA" << endl;
    return false;

    /*if (8 == reg.length())
    {
        const char* arr = reg.c_str();
        for (int i = 0; i < 8; i++)
        {
            if (i == 2 || i == 3)
                isdigit(arr[i]) ? check : check = false;
            else if (i == 4)
                isblank(arr[i]) ? check : check = false;
            else
                (isalpha(arr[i])) ? check : check = false;
        }
    }
    else
    {
        check = false;
    }
    return check;*/
}

bool Container::checkRegExists(string reg)
{
    vector<Vehicle*>::iterator it;
    int i = 0;
    for (it = vehicles.begin(); it != vehicles.end(); it++, i++)
    {
        if (vehicles[i]->getVehicleReg() == reg)
        {
            cout << "Vehicle registration is already in the database, please try again" << endl;
            break;
            return true;
        }
    }
    return false;
}

