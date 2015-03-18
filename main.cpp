#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "dockingstation.h"
#include "bike.h"

using namespace std;

int main(){

    //SET STARTUP CONDITIONS

    //create the four docking stations
    DockingStation ds1 , ds2 , ds3 , ds4;

    //create four helper vectors to store list of bikes in each station for printing purposes
    vector<Bike> vec1 , vec2 , vec3 , vec4;

    //open file that contains the bikes
    ifstream bikes("bikes.txt");

    //if file successfully opens
    //dock five bikes in each docking station
    if(!bikes){
        cout << "ERROR: failed to open bikes file!" << endl;
        exit(1);
    }else{

        while( !bikes.eof() ){

            int bike_id;
            bikes >> bike_id;
            Bike newBike(bike_id);

            //bikes with ID 1-5 are put in docking station 1
            if(bike_id>0 && bike_id<=5){
                ds1.dockBike(newBike);
                vec1.push_back(newBike);

            //bikes with ID 6-10 are put in docking station 2
            }else if(bike_id>5 && bike_id<=10){
                ds2.dockBike(newBike);
                vec2.push_back(newBike);

            //bikes with ID 11-15 are put in docking station 3
            }else if(bike_id>10 && bike_id<=15){
                ds3.dockBike(newBike);
                vec3.push_back(newBike);

            //bikes with ID 16-20 are put in docking station 4
            }else{
                ds4.dockBike(newBike);
                vec4.push_back(newBike);
            }
        }
    }

    //BEGIN SIMULATION

    cout << "\t\tWELCOME TO ACSE BIKES TRACKER\n\n" << endl;
    cout << "Current status of docking stations..." << endl;

    cout << "\nDocking station" << "\t\t\t\tBikes Available" << endl;
    cout << "\n\t1\t\t\t";
    for(Bike b : vec1){
        cout << right << setw(8) << "bike-" << b.getBikeID();
    }

    cout << "\n\t2\t\t\t";
    for(Bike b : vec2){
        cout << right << setw(8) << "bike-" << b.getBikeID();
    }

    cout << "\n\t3\t\t\t";
    for(Bike b : vec3){
        cout << right << setw(8) <<  "bike-" << b.getBikeID();
    }

    cout << "\n\t4\t\t\t";
    for(Bike b : vec4){
        cout << right << setw(8) <<  "bike-" << b.getBikeID();
    }

    cout << endl;







    return 0;
}

