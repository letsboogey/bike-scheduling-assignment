#ifndef DOCKINGSTATION_H
#define DOCKINGSTATION_H
#include <stack>
#include "bike.h"

using namespace std;

class DockingStation
{
    //variables
    private:
        stack<Bike> dock;

    //member functions
    public:
        DockingStation(); //constructor
        void dockBike(Bike); //stores returned in left-most position of the docking station (top of stack)
        Bike despatchBike(); //loans bike in left-most position of the docking station (top of stack)
        bool bikeAvailable(); //checks if there are any bikes available for loan in the docking station
        ~DockingStation(); //destructor
};

#endif // DOCKINGSTATION_H
