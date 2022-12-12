#pragma once
#include "Container.h"
#include "Vehicle.h"
#include <vector>

class Disk
{
private:

public:

    Disk();
    ~Disk();

    static Container* readVehiclesFromDisk();
    static void writeVehicleToDisk(Vehicle* data);
    // static void writeVehiclesToDisk(vector<Vehicle*> data);
};
