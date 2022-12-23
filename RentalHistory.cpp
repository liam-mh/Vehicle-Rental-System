#define _CRT_SECURE_NO_WARNINGS
#define CLEAR_SCREEN system("cls");
#define SPACE cout << "\n";
#define VUI ValidateUserInput::getInstance()->validateUserInput
#define IN_1_OR_2 VUI(option, 2, 9);

#include "RentalHistory.h"
#include "Disk.h"
#include "Rent.h"
#include "ValidateUserInput.h"
#include "Vehicle.h"

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

RentalHistory::RentalHistory(Vehicle* vehicle)
    : vehicle(vehicle)
{}

RentalHistory::~RentalHistory()
{
    for (int i = 0; i < totalRents; i++)
    {
        delete rents[i];
    }
    free(rents);
    rents = nullptr;
}

// Array manipulators
void RentalHistory::addRent(Rent* newEntry)
{
    totalRents++;
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

void RentalHistory::operator+(Rent* newEntry)
{
    addRent(newEntry);
}

// Display content
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
        IN_1_OR_2

        if (option == 1 && index-1 > -1)
            index--;
        if (option == 2 && index+1 < getTotalRents())
            index++;
        if (option == 9)
            break;
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

// User input
void RentalHistory::rentalPage()
{
    int option = NULL;
    int newRents = 0;

    while (option != 9)
    {
        CLEAR_SCREEN
        cout << "Rental Vehicle: " << vehicle->getVehicleMake() << " " << vehicle->getVehicleModel() << endl;
        cout << "------------------------------" << endl;
        cout << left << setw(25) << "Cost per day:"        << "\x9C" << vehicle->costPerDay() << endl;
        cout << left << setw(25) << "Total rental income:" << "\x9C" << getTotalIncome() << endl;
        cout << left << setw(25) << "Total days rented:"   << getTotalDays() << endl;
        SPACE
        cout << "What do you wish to do?" << endl;
        cout << "1) Rent Vehicle" << endl;
        if (getTotalDays() == 0)
            cout << " ) No rental history to display!" << endl;
        else
            cout << "2) View Historical Rentals" << endl;
        cout << "9) Return to the main menu" << endl;
        IN_1_OR_2
        SPACE
  
        if (option == 1)
            newRents = createRent();
        if (option == 2 && getTotalDays() != 0)
            viewHistory();
        if (option == 9)
            break;
    }
    if (newRents != 0)
        save(newRents);
}

int RentalHistory::createRent()
{
    int NewRents = 0;
    int option = NULL;
    int days = 0;
    double cost = vehicle->costPerDay() * days;
    string startDate, endDate, name, address, number;
    
    while (option != 9)
    {
        cout << "Rent Vehicle: " << vehicle->getVehicleReg() << " : " << vehicle->getVehicleMake() << " " << vehicle->getVehicleModel() << endl;
        cout << "------------------------------" << endl;
        cout << "Do you wish to continue and rent this vehicle?" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        IN_1_OR_2
        if (option == 2)
            break;
        SPACE

        option = NULL;
        tm* data = getCurrentDate(startDate);
        cout << "Please enter the following details:\n";
        cout << left << setw(20) << "Starting Date: "     << startDate << endl;;
        cout << left << setw(20) << "Number of days: ";   VUI(days);
        addDays(data, days, endDate);
        cout << left << setw(20) << "Finish Date: "       << endDate << endl;
        cout << left << setw(20) << "Customer Name: ";    VUI(name);
        cout << left << setw(20) << "Customer Address: "; VUI(address);
        cout << left << setw(20) << "Customer Number: ";  ValidateUserInput::getInstance()->validateMobileInput(number);
        SPACE
        cout << "Please confirm the details above are correct" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        IN_1_OR_2
        if (option == 2)
            break;
        SPACE

        option = NULL;
        cout << "The breakdown of rental cost:" << endl;
        cout << left << setw(20) << "Cost per day: "      << "\x9C" << vehicle->costPerDay() << endl;
        cout << left << setw(20) << "Days being rented: " << days << endl;
        cout << left << setw(20) << "TOTAL COST: "        << "\x9C" << cost << endl;
        cout << "Do you wish to continue?" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No" << endl;
        IN_1_OR_2
        cin >> option;
        if (option == 2)
            break;
        SPACE
       
        Rent* rent = new Rent(vehicle->getVehicleReg(), totalRents+1, days, cost, startDate, endDate, name, address, number);;
        addRent(rent);
        NewRents++;
    }
    return NewRents;
}

// Help user input
tm* RentalHistory::getCurrentDate(string &date)
{
    time_t t = time(0);
    tm* now = localtime(&t);
    date = convertToDate((now->tm_mday), (now->tm_mon + 1), (now->tm_year + 1900));
    return now;
}

void RentalHistory::addDays(tm* data, int days, string &date)
{
    /*
    * Code Snippet - Highlighted below
    * https://stackoverflow.com/questions/38722589/c-add-or-subtract-values-to-the-date
    * I took an idea that I was looking into and used this example to implement my own function.
    * Using tm to add an integer and generate a new date.
    */

    time_t t = mktime(data);
    // ------------------------
    t += (60 * 60 * 24 * days);
    // ------------------------
    data = localtime(&t);
    date = convertToDate((data->tm_mday), (data->tm_mon + 1), (data->tm_year + 1900));
}

string RentalHistory::convertToDate(int day, int month, int year)
{
    string date;
    date += to_string(day);
    date += "/";
    date += to_string(month);
    date += "/";
    date += to_string(year);
    return date;
}

void RentalHistory::save(int newRents)
{
    Disk::writeRentalHistoryToDisk(this->rents, totalRents, newRents);
}


