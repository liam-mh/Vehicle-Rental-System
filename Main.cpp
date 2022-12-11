#define CLEAR_SCREEN system("cls")
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

    Disk* disk = new Disk();
    Container* container = disk->readVehiclesFromDisk();

    /* STORING VEHICLES
    * Whilst implementing reading from disk
    * -----------------------------------------------------------------------------------
    
    
    Vehicle** PPv = new Vehicle* [10];

    PPv[0] = new Car(3, 5, "GY46 HHH", "Honda", "Civic", 2023);
    PPv[1] = new Car(5, 5, "JU77 HSG", "Ford", "Focus", 2022);
    PPv[2] = new Car(5, 5, "AA22 AAA", "Audi", "TT", 2005);
    PPv[3] = new Car(5, 5, "LL47 CSA", "Audi", "Q5", 2020);
    PPv[4] = new Bike(75, 2, "FS77 DFD", "Honda", "MotorCross", 2011);
    PPv[5] = new Bike(50, 2, "CI92 FSS", "Toyota", "Moped", 2008);
    PPv[6] = new Car(3, 2, "BM99 HDS", "BMW", "M3", 2021);
    PPv[7] = new Bike(883, 2, "SF52 YYT", "Harley Davidson", "Dyna", 2019);
    
    for (int i = 0; i < sizeof(PPv); i++)
        container->addItem(PPv[i]);

    
    * end
    * -----------------------------------------------------------------------------------
    */

    RentalHistory* rentalHistory = new RentalHistory("GY46 HHH");

    Rent* r = new Rent("GY46 HHH", 1, 5, 25.00, "08 / 12 / 2023", "13 / 12 / 2023", "Liam", "80 Brunswick", "07706666514");
    
    //rentalHistory->addRent(r);
    


    
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
        case 2: CLEAR_SCREEN; container->removeItemPage();
        case 3: CLEAR_SCREEN; container->search("Car"); break;
        case 4: CLEAR_SCREEN; container->search("Bike"); break;
        case 5: CLEAR_SCREEN; regFilter  = true, costFilter = false; break;
        case 6: CLEAR_SCREEN; costFilter = true, regFilter  = false; break;
        }
        

    } while (option != 9);


    container->save();
    delete container;

    Container* newContainer = disk->readVehiclesFromDisk();

    option = NULL;
    while (option != 9)
    {
        newContainer->displayMainData(false, false);
        cin >> option;
    }

    


    #ifdef _DEBUG
        //_CrtSeBreakAlloc();
        _onexit(_CrtDumpMemoryLeaks);
    #endif
    
    //delete vehicles;

    cout << "**END OF MAIN.CPP" << endl;
    return 0;
}
