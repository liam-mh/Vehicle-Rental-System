#include "Rent.h"

#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

// Customer
Rent::Customer::Customer()
{}

Rent::Customer::Customer(string name, string address, string number)
    : name(name), address(address), number(number)
{}

Rent::Customer::~Customer()
{}

void Rent::Customer::displayCustomer()
{
    cout << left << setw(20) << "Name: " << name << endl;
    cout << left << setw(20) << "Address: " << address << endl;
    cout << left << setw(20) << "Number: " << number << endl;
}

// Rent
Rent::Rent(string registration, int rentNum, int daysRented, double periodCost, string startDate, string endDate, string name, string address, string number)
    : registration(registration), rentNum(rentNum), daysRented(daysRented), periodCost(periodCost), startDate(startDate), endDate(endDate)
{
    customer = new Customer(name, address, number);
}

Rent::~Rent()
{
    delete customer;
    customer = nullptr;
}

void const Rent::displayRent(int totalRents)
{
    cout << left << setw(20) << "Rental number: " << rentNum << " of " << totalRents << endl;
    cout << left << setw(20) << "Date from: " << startDate << endl;
    cout << left << setw(20) << "Date to: " << endDate << endl;
    cout << left << setw(20) << "Rental days: " << daysRented << endl;
    cout << left << setw(20) << "Total cost: " << "\x9C" << periodCost << "\n" << endl;
    customer->displayCustomer();
}

ofstream& operator<<(ofstream& of, const Rent* r)
{
    of
        << r->registration << ","
        << r->rentNum << ","
        << r->daysRented << ","
        << r->periodCost << ","
        << r->startDate << ","
        << r->endDate << ","
        << r->customer->name << ","
        << r->customer->address << ","
        << r->customer->number << "\n";
    return of;
}
