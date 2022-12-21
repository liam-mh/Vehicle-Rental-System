#define CLEAR_SCREEN system("cls");
#define SPACE cout << "\n";

#include "Container.h"
#include "Disk.h"

#include <iostream>
using namespace std;

#ifdef _DEBUG
    //#include <crtdbg.h>
#endif

int main() {

#ifdef _DEBUG
    //_CrtSetBreakAlloc();
    //_onexit(_CrtDumpMemoryLeaks);
#endif

    Container* container = Disk::readVehiclesFromDisk();

    int option;
    bool regFilter = false,
        costFilter = false;

    do
    {
        CLEAR_SCREEN;
        cout << "-----------------------------------------------------" << endl;
        cout << "Vehicle Rental System - Liam Hammond" << endl;
        cout << "-----------------------------------------------------" << endl;

        // Display data
        if (regFilter) 
            cout << "\nFiltered by registration, in alphabetical order\n" << endl;
        if (costFilter)
            cout << "\nFiltered by cost per day, in ascending order\n" << endl;   
        container->displayMainData(regFilter, costFilter);
        SPACE

        // User options
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
            case 3: CLEAR_SCREEN; container->searchForVehiclePage("Car"); break;
            case 4: CLEAR_SCREEN; container->searchForVehiclePage("Bike"); break;
            case 5: CLEAR_SCREEN; regFilter = true, costFilter = false; break;
            case 6: CLEAR_SCREEN; regFilter = false, costFilter = true; break;
        }
    } while (option != 9);

    delete container;

    return 0;
}