#pragma once
#include "Rent.h"

#include <vector>
#include <string>
using namespace std;

class RentalHistory
{
private:
    string registration;
    int totalRents = 0;
    Rent* rents = (Rent*)malloc(sizeof(Rent) * totalRents);

public:
    RentalHistory(string registration);
    ~RentalHistory();

    const int getTotalRents();
    void incrementTotalRents();

    void addRent(Rent* newEntry);
    void resize();
};

inline const int RentalHistory::getTotalRents() { return totalRents; }
inline void RentalHistory::incrementTotalRents() { totalRents++; }