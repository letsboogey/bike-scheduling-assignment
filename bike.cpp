#include "bike.h"

Bike::Bike(int id){
    bike_number = id;
}

void Bike::setStartTime(int start){
    start_time = start;
}

void Bike::setDestination(int dest){
    destination = dest;
}

void Bike::setLoanPeriod(int period){
    loan_period = period;
}

bool Bike::loanExpired(){
    return (remaining_time) ? false : true ;
}

int Bike::getBikeID(){
    return bike_number;
}

int Bike::getStartTime(){
    return start_time;
}

int Bike::getRemainingTime(){
    loan_period -= 1;
    remaining_time = loan_period;
    return remaining_time;
}

int Bike::getLoanPeriod(){
    return loan_period;
}

int Bike::getDestination(){
    return destination;
}

Bike::~Bike(){}

