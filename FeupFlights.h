//
// Created by Davide Teixeira on 27/12/2022.
//

#ifndef AED_PROJECT2_FEUPFLIGHTS_H
#define AED_PROJECT2_FEUPFLIGHTS_H


#include <unordered_set>
#include "Airline.h"

class FeupFlights {
    unordered_set<Airline, betAirline, betAirline> airlines;

public:
    FeupFlights();
    void readAirlines();
};


#endif //AED_PROJECT2_FEUPFLIGHTS_H
