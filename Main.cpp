#define CLEAR_SCREEN system("cls")
#include "Container.h"
#include "Vehicle.h"
#include "Disk.h"
#include "Car.h"
#include "Bike.h"

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;



int main() {

    Disk* disk = new Disk();
    Container* container = disk->readVehiclesFromDisk();

    /* STORING VEHICLES
    * Whilst implementing reading from disk
    * -----------------------------------------------------------------------------------
    */

    
    Vehicle** PPv = new Vehicle* [10];

    PPv[0] = new Car(3, 5, "GY46 HHH", "Honda", "Civic", 2010);
    PPv[1] = new Car(5, 5, "JU77 HSG", "Ford", "Focus", 2002);
    PPv[2] = new Car(5, 5, "AA22 AAA", "Audi", "TT", 2005);
    PPv[3] = new Car(5, 5, "LL47 CSA", "Audi", "Q5", 2020);
    PPv[4] = new Bike(75, 2, "FS77 DFD", "Honda", "MotorCross", 2011);
    PPv[5] = new Bike(50, 2, "CI92 FSS", "Toyota", "Moped", 2008);
    PPv[6] = new Car(3, 2, "BM99 HDS", "BMW", "M3", 2021);
    PPv[7] = new Bike(883, 2, "SF52 YYT", "Harley Davidson", "Dyna", 2019);
    
    for (int i = 0; i < sizeof(PPv); i++)
        container->addItem(PPv[i]);



    /*
    // Read vehicles from disk
    ifstream input;
    input.open("Vehicle.csv");
    if (input.is_open())
    {
        string registration, type, make, model, temp;
        int age, var1, var2 = 0;

        string line, singleValue;

        while (getline(input, line))
        {
            stringstream ss(line);
            getline(ss, temp, ','); var1 = stoi(temp);
            getline(ss, temp, ','); var2 = stoi(temp);
            getline(ss, registration, ',');
            getline(ss, type, ',');
            getline(ss, make, ',');
            getline(ss, model, ',');
            getline(ss, temp, ','); age = stoi(temp);

            if (type == "Car")
            {
                Car* c = new Car(var1, var2, registration, make, model, age);
                container->addItem(c);
            }   
        }
        input.close();
    } else {
        cout << "Error: Cannot read from vehicle directory." << endl;
    }
    */

    /*
    * end
    * -----------------------------------------------------------------------------------
    */

    
    int option;

    do
    {
        CLEAR_SCREEN;

        cout << "-----------------------------------------------------" << endl;
        cout << "Vehicle Rental System - Liam Hammond" << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "" << endl;
        
        container->displayMainData();
        cout << "" << endl;
      
        cout << "1) Add Vehicle" << endl;
        cout << "2) Remove Vehicle" << endl;
        cout << "3) Search for car" << endl;
        cout << "4) Search for bike" << endl;
        cout << "5) Sort vehicles by registration number" << endl;
        cout << "6) Sort vehicles by cost per day" << endl;
        cout << "9) Exit" << endl;
        cout << "" << endl;
        cout << "Please enter option :" << endl;

        cin >> option;
        cout << "" << endl;
        
        switch (option)
        {
        case 1: CLEAR_SCREEN; container->addItemPage(); break;
        case 2: CLEAR_SCREEN; container->removeItemPage();
        case 3: CLEAR_SCREEN; container->search("Car"); break;
        case 4: CLEAR_SCREEN; container->search("Bike"); break;
        //case 5: MiniApps::sortReg(); break;
        //case 6: MiniApps::sortCPD(); break;
        }
        

    } while (option != 9);


    container->save();
    delete container;

    Container* newContainer = disk->readVehiclesFromDisk();

    option = NULL;
    while (option != 9)
    {
        newContainer->displayMainData();
        cin >> option;
    }

    


    #ifdef _DEBUG
        // _CrtSeBreakAlloc();
        _onexit(_CrtDumpMemoryLeaks);
    #endif
    
    //delete vehicles;

    cout << "**END OF MAIN.CPP" << endl;
    return 0;
}
