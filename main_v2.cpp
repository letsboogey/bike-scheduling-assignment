#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <random>
#include <unistd.h>
#include <stack>
#include <algorithm>
#include "dockingstation.h"
#include "bike.h"

using namespace std;

//variables
int loan_period;

//create the four docking stations
DockingStation ds1 , ds2 , ds3 , ds4;

//create four helper vectors to store list of bikes in each station for printing purposes
vector<Bike> vec1 , vec2 , vec3 , vec4;

//vector to store bikes on loan
vector<Bike> loanedBikes;
vector<Bike> helper;

struct input{
    int to;
    int from;
}fromto;

//method to recieve input from the user
void getUserInput(){
    int loan_from, return_to;
    cout << "Enter 1,2,3 or 4 to loan/return a bike from DS-1, DS-2, DS-3 or DS-4 respectively [ 0 to not loan ]...\n" << endl;
    cout << "Loan from: ";
    cin >> loan_from;

    if(loan_from){
        cout << "Return to: ";
        cin >> return_to;
    }else{
        return_to = 0;
    }

    if(loan_from < 0 || loan_from > 4 || return_to > 4){
        cout << "\nError: Invalid input!" << endl;
        getUserInput();
    }else{
        fromto.from = loan_from;
        fromto.to = return_to;
    }
}


//prints the bikes docked in each docking station
void printDockingStations(vector<Bike> v1,vector<Bike> v2,vector<Bike> v3,vector<Bike> v4 ){

    cout << "Current status of docking stations..." << endl;
    cout << "\n  Docking station" << "\t\tBikes Available" << endl;

    //ensure vector elements are printed from left - right
    //this is because left-most element is the top of the stack
    reverse(v1.begin(),v1.end());
    reverse(v2.begin(),v2.end());
    reverse(v3.begin(),v3.end());
    reverse(v4.begin(),v4.end());

    cout << "\n\tDS-1\t\t ";
    for(Bike b : v1){
        cout << setw(5)<< right  << b.getBikeID();
    }

    cout << "\n\tDS-2\t\t ";
    for(Bike b : v2){
        cout << setw(5)<< right  << b.getBikeID();
    }

    cout << "\n\tDS-3\t\t ";
    for(Bike b : v3){
        cout << setw(5)<< right << b.getBikeID();
    }

    cout << "\n\tDS-4\t\t ";
    for(Bike b : v4){
        cout << setw(5)<< right << b.getBikeID();
    }

    cout << "\n\n";
}

//method to return bike if loan period has elapsed
void returnBike(Bike b){
    switch (b.getDestination()) {
        case 1:
            ds1.dockBike(b);
            vec1.push_back(b);
            break;
        case 2:
            ds2.dockBike(b);
            vec2.push_back(b);
            break;
        case 3:
            ds3.dockBike(b);
            vec3.push_back(b);
            break;
        case 4:
            ds4.dockBike(b);
            vec4.push_back(b);
            break;
    }
    //remove returned bike from loaned bike vector with the help of helper vector
    //which temporarily stores those still on loan
    for(Bike onLoan : loanedBikes){
        if(b.getBikeID() == onLoan.getBikeID()){
            continue;
        }
        helper.push_back(onLoan);
    }

    loanedBikes.erase(loanedBikes.begin(),loanedBikes.end());

    for(Bike stillOnLoan : helper){
         loanedBikes.push_back(stillOnLoan);
     }
}

//method to print all bikes that are on loan
void printLoanedBikes(int time){
   vector<Bike> expired;
    cout << "\n\nBikes currently on loan..."<< endl;
    for( int i = 0 ; i < loanedBikes.size() ; i++){

        Bike on_loan = loanedBikes[i];

        if(on_loan.loanExpired(time)){
            expired.push_back(on_loan);
            returnBike(expired[0]);
            expired.pop_back();
           continue;
        }
        cout << "\tBike ID: [ " << on_loan.getBikeID() << " ]" ;
        cout << "  , Return destination: [ " << on_loan.getDestination() << " ]" ;
        cout << "  , Loan Period(minutes): [ " << on_loan.getLoanPeriod() << " ]";
        cout << "  , Loan start time(minute): [ " << on_loan.getStartTime() << " ]" << endl;
        cout << "\n";
    }
}



int main(){

    //SET STARTUP CONDITIONS

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
    //display list of bikes at each station
    printDockingStations(vec1,vec2,vec3,vec4);

    //begin 30 minute operation simulation
    for(int min = 1 ; min < 31 ; min++){

        cout << "\n\nCurrent time : "<< min <<endl;

        getUserInput();
        //generate a random for loan period in range 1-30
        srand(time(NULL));
        loan_period = min + (rand() % (int)(10 - min + 1));

        if(fromto.from){
            int loan = fromto.from;
            int ret = fromto.to;

            switch (loan){
                //loan bike from DS-1
                case 1:
                    if(ds1.bikeAvailable()){
                        Bike loaned = ds1.despatchBike();
                        vec1.pop_back();
                        loaned.setDestination(ret);
                        loaned.setStartTime(min);
                        loaned.setLoanPeriod(loan_period);
                        loanedBikes.push_back(loaned);
                        system("clear");
                        printLoanedBikes(min);
                        printDockingStations(vec1,vec2,vec3,vec4);


                    }else{
                        system("clear");
                        cout << "\n\nSorry, no bikes available for loan in DS-1, try another station in a moment..." << endl;
                        sleep(3);
                        printDockingStations(vec1,vec2,vec3,vec4);
                        printLoanedBikes(min);
                        getUserInput();
                    }
                    break;
                //loan bike from DS-2
                case 2:
                    if(ds2.bikeAvailable()){
                        Bike loaned = ds2.despatchBike();
                        vec2.pop_back();
                        loaned.setDestination(ret);
                        loaned.setStartTime(min);
                        loaned.setLoanPeriod(loan_period);
                        loanedBikes.push_back(loaned);
                        system("clear");
                        printLoanedBikes(min);
                        printDockingStations(vec1,vec2,vec3,vec4);

                    }else{
                        system("clear");
                        cout << "\n\nSorry, no bikes available for loan in DS-2, try another station in a moment..." << endl;
                        sleep(3);
                        printDockingStations(vec1,vec2,vec3,vec4);
                        printLoanedBikes(min);
                        getUserInput();
                    }
                    break;

                //loan bike from DS-3
                case 3:
                    if(ds3.bikeAvailable()){
                        Bike loaned = ds3.despatchBike();
                        vec3.pop_back();
                        loaned.setDestination(ret);
                        loaned.setStartTime(min);
                        loaned.setLoanPeriod(loan_period);
                        loanedBikes.push_back(loaned);
                        system("clear");
                         printLoanedBikes(min);
                        printDockingStations(vec1,vec2,vec3,vec4);

                    }else{
                        system("clear");
                        cout << "\n\nSorry, no bikes available for loan in DS-3, try another station in a moment..." << endl;
                        sleep(3);
                        printDockingStations(vec1,vec2,vec3,vec4);
                        printLoanedBikes(min);
                        getUserInput();
                    }
                    break;

                //loan bike from DS-4
                case 4:
                    if(ds4.bikeAvailable()){
                        Bike loaned = ds4.despatchBike();
                        vec4.pop_back();
                        loaned.setDestination(ret);
                        loaned.setStartTime(min);
                        loaned.setLoanPeriod(loan_period);
                        loanedBikes.push_back(loaned);
                        system("clear");
                        printLoanedBikes(min);
                        printDockingStations(vec1,vec2,vec3,vec4);

                    }else{
                        system("clear");
                        cout << "\n\nSorry, no bikes available for loan in DS-4, try another station in a moment..." << endl;
                        sleep(3);
                        printDockingStations(vec1,vec2,vec3,vec4);
                        printLoanedBikes(min);
                        getUserInput();
                    }
                    break;
            }


        }else{
            continue;
        }
    }

    return 0;
}

