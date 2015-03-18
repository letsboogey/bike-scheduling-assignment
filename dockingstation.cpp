#include "dockingstation.h"

using namespace std;

DockingStation::DockingStation(){}

bool DockingStation::bikeAvailable(){
    return (dock.size()) ? true : false ;
}

Bike DockingStation::despatchBike(){
    Bike bike = dock.top();
    dock.pop();
    return bike;
}

void DockingStation::dockBike(Bike id){
    dock.push(id);
}

DockingStation::~DockingStation(){}

