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
        int bike_number, destination, loan_period, start_time;

    //member functions
    public:
        Bike(int); //constructor
        void setDestination(int); //set the dock number for bike return
        void setStartTime(int); //set the loan start time
        void setLoanPeriod(int); //set the loan period
        bool loanExpired(int); //updates the remaining loan time
        int getDestination(); //returns the dock number for bike to be returned to
        int getBikeID(); //returns the bike number
        int getLoanPeriod(); //returns the assigned loan period
        int getStartTime(); //returns time when loan period began
        ~Bike(); //destructor
};

#endif // BIKE_H
