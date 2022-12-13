#define CLEAR_SCREEN system("cls");
#define SPACE cout << "" << endl;
#include "Container.h"
#include "Vehicle.h"
#include "Disk.h"
#include "Car.h"
#include "Bike.h"

#include "Rent.h"
#include "RentalHistory.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
using namespace std;


int main() {

    Container* container = Disk::readVehiclesFromDisk();

    /* RENTAL TESTS
    * Getting rental history working before transferring it to classes
    * -----------------------------------------------------------------------------------
    
    RentalHistory* rentalHistory = new RentalHistory();
    rentalHistory->displayData();
    Rent* r = new Rent("GY46 HHH", 1, 5, 25.00, "08 / 12 / 2023", "13 / 12 / 2023", "Liam", "80 Brunswick", "07706666514");
    Rent* r2 = new Rent("GY46 HHH", 2, 5, 25.00, "08 / 12 / 2023", "13 / 12 / 2023", "Liam", "80 Brunswick", "07706666514");

    rentalHistory->addRent(r);
    rentalHistory->addRent(r2);

    cout << "new" << endl;
    rentalHistory->displayData();

    //rentalHistory->createRent();

    
    * end
    * -----------------------------------------------------------------------------------
    */

    int option;
    bool regFilter = false,
        costFilter = false;

    do
    {
        CLEAR_SCREEN;

        cout << "-----------------------------------------------------" << endl;
        cout << "Vehicle Rental System - Liam Hammond" << endl;
        cout << "-----------------------------------------------------" << endl;

        SPACE
        if (regFilter)
        {
            cout << "Filtered by registration, in ascending order" << endl;
            SPACE
        }
        if (costFilter)
        {
            cout << "Filtered by cost per day, in ascending order" << endl;
            SPACE
        }
        container->displayMainData(regFilter, costFilter);
        SPACE

        cout << "1) Add Vehicle" << endl;
        cout << "2) Remove Vehicle" << endl;
        cout << "3) Search for car" << endl;
        cout << "4) Search for bike" << endl;
        cout << "5) Sort vehicles by registration number" << endl;
        cout << "6) Sort vehicles by cost per day" << endl;
        cout << "9) Exit" << endl;
        SPACE
        cout << "Please enter option :" << endl;
        cin >> option;
        SPACE

        switch (option)
        {
        case 1: CLEAR_SCREEN; container->addItemPage(); break;
        case 2: CLEAR_SCREEN; container->removeItemPage(); break;
        case 3: CLEAR_SCREEN; container->search("Car"); break;
        case 4: CLEAR_SCREEN; container->search("Bike"); break;
        case 5: CLEAR_SCREEN; regFilter = true, costFilter = false; break;
        case 6: CLEAR_SCREEN; costFilter = true, regFilter = false; break;
        }


    } while (option != 9);


    container->save();
    delete container;


#ifdef _DEBUG
    //_CrtSeBreakAlloc();
    _onexit(_CrtDumpMemoryLeaks);
#endif

    return 0;
}