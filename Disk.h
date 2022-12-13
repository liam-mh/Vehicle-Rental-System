#pragma once
#include "Container.h"
#include "RentalHistory.h"
//#include "Vehicle.h"
#include <vector>

class Disk
{
private:

public:

    Disk();
    ~Disk();

    static Container* readVehiclesFromDisk();
    static void writeVehiclesToDisk(vector<Vehicle*> data);

    static RentalHistory* readRentalHistoryFromDisk(Vehicle* vehicle);
    static void writeRentalHistoryToDisk(Rent** data, int totalRents, int newRents);
    static void removeRentalHistory(Vehicle* vehicle);
};
