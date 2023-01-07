//
// Created by Davide Teixeira on 27/12/2022.
//

#ifndef AED_PROJECT2_FEUPFLIGHTS_H
#define AED_PROJECT2_FEUPFLIGHTS_H


#include <unordered_set>
#include "Airline.h"
#include "Airport.h"
#include "graph.h"

/**
 * Esta classe pretende representar a classe responsável por ter todos os algoritmos e de gerir as restantes classes
 */
class FeupFlights {

    /**
     * Hash table que contém todas as companhias aéreas
     */
    unordered_set<Airline, HashAirline, HashAirline> airlines;

    /**
     * Hash table que contém todos os aeroportos
     */
    unordered_set<Airport, HashAirport, HashAirport> airports;

    /**
     * Grafo com os aeroportos, assim como os voos entre eles
     */
    Graph flights;
public:
    FeupFlights();
    void readAirlines();
    void readAirports();
    void readFlights();
    void createFlightGraphTEST();
    void bfsAndleastFlightsTEST();
    void showEdgesTest();
    double haversine(float lat1, float lon1, float lat2, float lon2);
    vector<string> allAirportsLessThan(int x, float lat, float lon);
    vector<string> allAirportsCity(string city, string country);
    vector<string> allAirportsFromCountry(string country);
    vector<string> allAirportsFromCity(string city);
    vector<string> allAirlinesFromCountry(string country);
};


#endif //AED_PROJECT2_FEUPFLIGHTS_H
