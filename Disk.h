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

    Container* readVehiclesFromDisk();
    static void writeVehicleToDisk(Vehicle* data);
    //static void writeVehiclesToDisk(Container* data);
};
