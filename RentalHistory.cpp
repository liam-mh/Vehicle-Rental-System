#include "RentalHistory.h"

RentalHistory::RentalHistory(string registration)
    : registration(registration)
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
    int index = getTotalRents();
    rents[index] = *newEntry;
}

void RentalHistory::resize()
{
    rents = (Rent*)realloc(rents, sizeof(Rent) * totalRents);
}
