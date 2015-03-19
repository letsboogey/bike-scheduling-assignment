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

bool Bike::loanExpired(int min){
    int expires_at = start_time + loan_period - 1;
    return (min < expires_at) ? false : true;
}

int Bike::getBikeID(){
    return bike_number;
}

int Bike::getStartTime(){
    return start_time;
}

int Bike::getLoanPeriod(){
    return loan_period;
}

int Bike::getDestination(){
    return destination;
}

Bike::~Bike(){}

