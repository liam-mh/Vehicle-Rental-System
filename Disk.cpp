#include "Disk.h"
#include "Vehicle.h"

#include <fstream>
#include <vector>
#include <string>
#include <utility>

#include <iostream>
using namespace std;

Disk::Disk() {}
Disk::~Disk() {}

void Disk::readVehicleFromDisk()
{
    // file pointer
    fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("reportcard.csv", ios::out | ios::app);

    cout << "Enter the details of 5 students:"
        << " roll name maths phy chem bio" << endl;

    int i, roll, phy, chem, math, bio;
    string name;

    // Read the input
    for (i = 0; i < 5; i++) {

        cin >> roll
            >> name
            >> math
            >> phy
            >> chem
            >> bio;

        // Insert the data to file
        fout << roll << ", "
            << name << ", "
            << math << ", "
            << phy << ", "
            << chem << ", "
            << bio
            << "\n";
    }
};

/*
void Disk::writeVehicleToDisk(vector<Vehicle> dataset)
{
    // Create an output filestream object
    ofstream myFile("Vehicle.csv");

    // Send data to the stream
    for (int i = 0; i < dataset.size(); ++i)
    {
      
    }

    // Close the file
    myFile.close();
    
}
*/