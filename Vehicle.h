#pragma once
#include <cstring>
#include <string>
using namespace std;

class Vehicle
{
private:
    string registration, type, make, model;
    //char* make;
    
   /* ifstream >> string make;

    make_char_array = malloc(sizeof(make))

    for (int i = 0; i < make.length; i++){
        make_char_array[i] = string_make[i];
    }*/

    int age = 0;

public:
    Vehicle(string registration, string type, string make, string model, int age);
    virtual ~Vehicle();

    virtual const int getVal1() = 0;
    virtual const int getVal2() = 0;
    virtual const void displayVehicle();
    virtual double costPerDay() const = 0;

    const string getVehicleReg() const;
    const string getVehicleMake() const;
    const string getVehicleModel() const;
    const int getVehicleAge() const;

    static bool checkRegFormat(string reg);
    //friend bool operator<(const Vehicle& lhs, const Vehicle& rhs);
};

inline const string Vehicle::getVehicleReg() const { return registration; }
inline const string Vehicle::getVehicleMake() const { return make; }
inline const string Vehicle::getVehicleModel() const { return model; }
inline const int Vehicle::getVehicleAge() const { return age; }





