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

public:

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

    FeupFlights();
    void readAirlines();
    void readAirports();
    void readFlights();
    double haversine(float lat1, float lon1, float lat2, float lon2);
    vector<string> allAirportsLessThan(int x, float lat, float lon);
    vector<string> allAirportsCity(string city, string country);
    Airport findAirport(string cod);
    Airline findAirline(string cod);
    int manyFlights(string airport);
    int differentAirlines(string airport);
    int differentDestenies(string airport);
    int differentCountries(string airport);
    int airportsLessThanY(string airport, int y);
    int citiesLessThanY(string airport, int y);
    int countriesLessThanY(string airport, int y);
};


#endif //AED_PROJECT2_FEUPFLIGHTS_H
