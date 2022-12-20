#pragma once
#include <iostream>
using namespace std;

class Rent
{
private:

    class Customer
    {
        //friend class Rent;
    //private:

    public:
        string name;
        string address;
        string number;

        Customer();
        Customer(string name, string address, string number);
        ~Customer();

        void displayCustomer();
    };

    string registration;
    int rentNum = 0,
        daysRented = 0;
    double periodCost = 0.00;
    string startDate;
    string endDate;
    Customer* customer;

public:
    Rent(string registration, int rentNum, int daysRented, double periodCost, string startDate, string endDate, string name, string address, string number);
    ~Rent();

    const int getDaysRented();
    const double getPeriodCost();
    void const displayRent(int totalRents);
  
    friend ofstream& operator<<(ofstream& of, const Rent* r);
};
inline const int Rent::getDaysRented() { return daysRented; }
inline const double Rent::getPeriodCost() { return periodCost; }
