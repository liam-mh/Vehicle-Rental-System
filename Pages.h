#pragma once
#include "RentalHistory.h"
#include <string>

class Pages
{
public:
    Container* container;
    RentalHistory* rentalHistory;

    Pages(Container* container, RentalHistory* rentalHistory);
    // User input 
    void addItemPage();
    void removeItemPage();
    void createVehiclePage(Container* container, string type);
    void searchForVehiclePage(Container* container, string type);
    // Helping user input
    void selectForRentalHistory(int totalOptions);
    string userEnterReg(bool alreadyExistsErrorMessage);

    // User input 
    void rentalPage();
    int createRent();
};