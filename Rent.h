#pragma once
class Rent
{
private:
    int
        rentNum = 0,
        totalDays = 0,
        totalCost = 0;
    string
        startDate,
        endDate;

    class Customer
    {
    private:
        string
            name,
            address,
            number;

    public:
        Customer(string name, string address, string number);
        ~Customer();
    };


public:
    Rent(int rentNum, int totalDays, int totalCost, string startDate, string endDate, string name, string address, string number);
    ~Rent();

};

