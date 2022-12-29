//
// Created by Davide Teixeira on 27/12/2022.
//

#ifndef AED_PROJECT2_FEUPFLIGHTS_H
#define AED_PROJECT2_FEUPFLIGHTS_H


#include <unordered_set>
#include "Airline.h"
#include "Airport.h"
#include "graph.h"

class FeupFlights {
    unordered_set<Airline, HashAirline, HashAirline> airlines;
    unordered_set<Airport, HashAirport, HashAirport> airports;
    Graph flights;
public:
    FeupFlights();
    void readAirlines();
    void readAirports();
    void readFlights();
    void createFlightGraphTEST();
    void showEdgesTest();
    double haversine(float lat1, float lon1, float lat2, float lon2);
    vector<string> allAirportsLessThan(int x, float lat, float lon);
    vector<string> allAirportsCity(string city, string country);
};


#endif //AED_PROJECT2_FEUPFLIGHTS_H
