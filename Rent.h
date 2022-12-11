#pragma once
#include <string>
using namespace std;

class Rent
{
private:
    string registration;
    int rentNum = 0,
        daysRented = 0;
    double periodCost = 0.00;
    string startDate;
    string endDate;

    class Customer
    {
    public:
        string name;
        string address;
        string number; 

        Customer();
        Customer(string name, string address, string number);
        ~Customer();

        //const string getName();
        //const string getAddress();
        //const string getNumber();

        void displayCustomer();
    };

    Customer* customer;

public:
    Rent(string registration, int rentNum, int daysRented, double periodCost, string startDate, string endDate, string name, string address, string number);
    ~Rent();

    const int getRentNum();
    const int getDaysRented();
    const double getPeriodCost();
    const string getStartDate();
    const string getEndDate();

    void displayRent(int totalRents);
};

inline const int Rent::getRentNum() { return rentNum; }
inline const int Rent::getDaysRented() { return daysRented; }
inline const double Rent::getPeriodCost() { return periodCost; }
inline const string Rent::getStartDate() { return startDate; }
inline const string Rent::getEndDate() { return endDate; }

//inline const string Rent::Customer::getName() { return name; }
//inline const string Rent::Customer::getAddress() { return address; }
//inline const string Rent::Customer::getNumber() { return number; }

