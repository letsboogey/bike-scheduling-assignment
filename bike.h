#ifndef BIKE_H
#define BIKE_H

/*
 * @author - Letsibogo Ramadi
 * Description:
  This class defines a bike object and other information about the bike including
  it's return destination, loan status and loan period.
*/

class Bike
{
    //variables
    private:
        int bike_number, destination, loan_period, start_time, remaining_time;

    //member functions
    public:
        Bike(); //constructor
        void setDestination(int); //set the dock number for bike return
        void setStartTime(int); //set the loan period start time
        void updateLoan(); //updates the remaining time during simulation
        int getDestination(); //returns the dock number for bike to be returned to
        int getLoanPeriod(); //returns the assigned loan period
        int getStartTime(); //returns time when loan period began
        int getRemainingTime(); //returns remaining time until loan period expires
        bool loanExpired(); //checks if the loan period for bike has expired
        ~Bike(); //deconstructor
};

#endif // BIKE_H
