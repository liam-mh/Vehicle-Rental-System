#include "Container.h"
#include "Vehicle.h"
#include "Disk.h"
#include "Car.h"
#include "Bike.h"

#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    /* STORING VEHICLES
    * Whilst implementing reading from disk
    * -----------------------------------------------------------------------------------
    */
    Vehicle** vehicles = new Vehicle* [10];

    vehicles[0] = new Car(3, 5, "GY46 HHH", "Honda", "Civic", 2010);
    vehicles[1] = new Car(5, 5, "JU77 HSG", "Ford", "Focus", 2002);
    vehicles[2] = new Car(5, 5, "AA22 AAA", "Audi", "TT", 2005);
    vehicles[3] = new Car(5, 5, "LL47 CSA", "Audi", "Q5", 2020);
    vehicles[4] = new Bike(75, 2, "FS77 DFD", "Honda", "MotorCross", 2011);
    vehicles[5] = new Bike(50, 2, "CI92 FSS", "Toyota", "Moped", 2008);
    vehicles[6] = new Car(3, 2, "BM99 HDS", "BMW", "M3", 2021);
    vehicles[7] = new Bike(883, 2, "SF52 YYT", "Harley Davidson", "Dyna", 2019);

    // Wrap vehicle pointers into Container vector
    Container* container = new Container();
    for (int i = 0; i < sizeof(vehicles); i++)
        container->addItem(vehicles[i]);

    ofstream output;
    output.open("Vehicle.csv");

    for (int i = 0; i < sizeof(vehicles); i++)
    {
        Car* test = dynamic_cast<Car*>(vehicles[i]);
        if (test != nullptr)
            output << test;
    }
       
    output.close();
   

    /*
    * end
    * -----------------------------------------------------------------------------------
    */


    int option;

    do
    {
        cout << "" << endl;
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
        case 1: container->addItemPage();
        case 2: container->removeItemPage();
        //case 3: MiniApps::searchCar(); break;
        //case 4: MiniApps::searchBike(); break;
        //case 5: MiniApps::sortReg(); break;
        //case 6: MiniApps::sortCPD(); break;
        }
        

    } while (option != 9);

    #ifdef _DEBUG
        // _CrtSeBreakAlloc();
        _onexit(_CrtDumpMemoryLeaks);
    #endif
    delete container;
    //delete vehicles;

    cout << "**END OF MAIN.CPP" << endl;
    return 0;
}
