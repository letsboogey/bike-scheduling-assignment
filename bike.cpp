#include "bike.h"

Bike::Bike(int id){
    bike_number = id;
    destination = 0;
    loan_period = 0;
    start_time = 0;
    remaining_time = 0;
}

void Bike::updateLoan(){
    (remaining_time) ? remaining_time-- : remaining_time ;
}

void Bike::setStartTime(int start){
    start_time = start;
}

void Bike::setDestination(int dest){
    destination = dest;
}

bool Bike::loanExpired(){
    return (remaining_time) ? false : true ;
}

int Bike::getStartTime(){
    return start_time;
}

int Bike::getRemainingTime(){
    return remaining_time;
}

int Bike::getLoanPeriod(){
    return loan_period;
}

int Bike::getDestination(){
    return destination;
}

Bike::~Bike(){}

