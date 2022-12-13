#define CLEAR_SCREEN system("cls");
#define SPACE cout << "" << endl;
#include "RentalHistory.h"
#include "Rent.h"

#include <string>
#include <iostream>
#include "Vehicle.h"
#include <iomanip>
using namespace std;

RentalHistory::RentalHistory(Vehicle* vehicle)
    : vehicle(vehicle)
{}

RentalHistory::RentalHistory(Vehicle* vehicle, int totalRents)
    : vehicle(vehicle), totalRents(totalRents)
{}

RentalHistory::~RentalHistory()
{
    delete[] rents;
    rents = nullptr;
}

void RentalHistory::addRent(Rent* newEntry)
{
    incrementTotalRents();
    resize();
    int index = getTotalRents()-1;
    
    if (rents[index] != NULL)
        rents[index] = newEntry;
}

void RentalHistory::resize()
{
    Rent** temp = (Rent**)realloc(rents, sizeof(Rent) * getTotalRents());
    if (!temp)
        free(rents);
    if (temp != NULL)
        rents = temp;
}

void RentalHistory::displayData()
{
    for (int i = 0; i < getTotalRents(); i++)
    {
        rents[i]->displayRent(i);
    }
}

void RentalHistory::viewHistory()
{
    
    int option = NULL;
    int index = getTotalRents()-1;

    while (option != 9)
    {
        CLEAR_SCREEN
        cout << "Rental Vehicle: " << vehicle->getVehicleMake() << " " << vehicle->getVehicleModel() << endl;
        cout << "------------------------------" << endl;
        rents[index]->displayRent(getTotalRents());
        SPACE
        if (index-1 < 0)
            cout << " ) Oldest record is being shown already!" << endl;
        else
            cout << "1) View previous record" << endl;

        if (index+1 > getTotalRents() - 1)
            cout << " ) Newest record is being shown already!" << endl;
        else
            cout << "2) View next record" << endl;

        cout << "9) Return to vehicle information screen" << endl;
        cin >> option;

        if (option == 1 && index-1 > 0)
            index--;
        if (option == 2 && index+1 < getTotalRents()-1)
                index++;
        if (option == 9)
            break;
    }
}

void RentalHistory::rentalPage()
{
    int option = NULL;

    while (option != 9)
    {
        CLEAR_SCREEN
        cout << "Rental Vehicle: " << vehicle->getVehicleMake() << " " << vehicle->getVehicleModel() << endl;
        cout << "------------------------------" << endl;
        cout << left << setw(25) << "Cost per day:" << "\x9C" << vehicle->costPerDay() << endl;
        cout << left << setw(25) << "Total rental income:" << "\x9C" << getTotalIncome() << endl;
        cout << left << setw(25) << "Total days rented:" << getTotalDays() << endl;
        SPACE
        cout << "What do you wish to do?" << endl;
        cout << "1) Rent Vehicle" << endl;
        if (getTotalDays() == 0)
            cout << " ) No rental history to display!" << endl;
        else
            cout << "2) View Historical Rentals" << endl;
        cout << "9) Return to the main menu" << endl;
        cin >> option;
        SPACE
  
        if (option == 1)
            createRent();
        if (option == 2 && getTotalDays() != 0)
            viewHistory();
        if (option == 9)
            break;
    }
}

void RentalHistory::createRent()
{
    int option = NULL;
    int days = 0;
    string from, too, name, address, number;

    while (option != 9)
    {
        cout << "Rent Vehicle: " << vehicle->getVehicleReg() << " : " << vehicle->getVehicleMake() << " " << vehicle->getVehicleModel() << endl;
        cout << "------------------------------" << endl;
        cout << "Do you wish to continue and rent this vehicle?" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        cin >> option;
        SPACE
            if (option == 2)
                break;
        option = NULL;

        cout << "Please enter the following details:" << endl;
        cout << left << setw(20) << "Starting Date: ";    cin >> from;
        cout << left << setw(20) << "Finish Date: ";      cin >> too;
        cout << left << setw(20) << "Number of days: ";   cin >> days;
        cout << left << setw(20) << "Customer Name: ";    cin >> name;
        cout << left << setw(20) << "Customer Address: "; cin >> address;
        cout << left << setw(20) << "Customer Number: ";  cin >> number;
        SPACE
        cout << "Please confirm the details above are correct" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        cin >> option;
        SPACE
            if (option == 2)
                break;
        option = NULL;

        cout << "The breakdown of rental cost:" << endl;
        cout << "Cost per day: " << "\x9C" << vehicle->costPerDay() << endl;
        cout << "Days being rented: " << days << endl;
        double cost = vehicle->costPerDay() * days;
        cout << "TOTAL COST: " << "\x9C" << cost << endl;

        cout << "Do you wish to continue?" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        cin >> option;
        SPACE
            if (option == 2)
                break;
       
        Rent* rent = new Rent(vehicle->getVehicleReg(), totalRents+1, days, cost, from, too, name, address, number);;
        addRent(rent);
    }
}

const double RentalHistory::getTotalIncome()
{
    double total = 0.00;
    for (int i = 0; i < getTotalRents(); i++)
    {
        double current = rents[i]->getPeriodCost();
        total += current;
    }
    return total;
}

const int RentalHistory::getTotalDays()
{
    int total = 0;
    for (int i = 0; i < getTotalRents(); i++)
    {
        int current = rents[i]->getDaysRented();
        total += current;
    }
    return total;
}