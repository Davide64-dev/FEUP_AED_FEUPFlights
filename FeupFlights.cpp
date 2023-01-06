//
// Created by Davide Teixeira on 27/12/2022.
//

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include "FeupFlights.h"

using namespace std;

FeupFlights::FeupFlights() = default;

void FeupFlights::readAirlines() {
    vector<string> lineV(3);
    ifstream in("../dataset/airlines.csv");
    string cod, name, callSign, country;
    string line, word;

    getline(in, line);
    while (getline(in, line)) {
        lineV.clear();
        istringstream iss(line);
        while (getline(iss, word, ',')) {
            lineV.push_back(word);
        }
        cod = lineV[0];
        name = lineV[1];
        callSign = lineV[2];
        country = lineV[3];

        if (!country.empty() && country[country.size() - 1] == '\r')
            country.erase(country.size() - 1);

        Airline temp = Airline(cod, name, callSign, country);
        airlines.insert(temp);
    }
}

void FeupFlights::readAirports() {
    vector<string> lineV(6);
    ifstream in("../dataset/airports.csv");
    string cod, name, city, country, latitude, longitude;
    string line, word;

    getline(in, line);
    while (getline(in, line)) {
        lineV.clear();
        istringstream iss(line);
        while (getline(iss, word, ',')) {
            lineV.push_back(word);
        }
        cod = lineV[0];
        name = lineV[1];
        city = lineV[2];
        country = lineV[3];
        latitude = lineV[4];
        longitude = lineV[5];

        if (!longitude.empty() && longitude[longitude.size() - 1] == '\r')
            longitude.erase(longitude.size() - 1);

        Airport temp = Airport(cod, name, city, country, stof(latitude), stof(longitude));
        airports.insert(temp);
        flights.addNode(cod);
    }
}

void FeupFlights::readFlights() {
    vector<string> lineV(3);
    ifstream in("../dataset/flights.csv");
    string line, word;
    string source, target, airline;

    getline(in, line);
    int i = 0;
    while (getline(in, line)) {
        lineV.clear();
        istringstream iss(line);
        while (getline(iss, word, ',')) {
            lineV.push_back(word);
        }
        source= lineV[0];
        target = lineV[1];
        airline = lineV[2];

        if (!airline.empty() && airline[airline.size() - 1] == '\r')
            airline.erase(airline.size() - 1);
        flights.addEdge(source, target, airline);
    }


}

void FeupFlights::createFlightGraphTEST() {
    list<string> airports = {"test1", "test2", "test3", "test4", "test5"};
    flights = Graph(airports);
    flights.addEdge("test1", "test2", "al1");
    flights.addEdge("test1", "test3", "al1");
    flights.addEdge("test2", "test5", "al2");
    flights.addEdge("test2", "test5", "al3");
}

void FeupFlights::bfsAndleastFlightsTEST() {
    list<string> result;

    result = flights.leastFlights({"OPO"}, {"GVA"});
    for(const string& airport : result)
        cout << airport << "->";
    cout << "\n";

    result = flights.leastFlights({"OPO"}, {"CDG"});
    for(const string& airport : result)
        cout << airport << "->";
    cout << "\n";

    result = flights.leastFlights({"OPO"}, {"PEK"});
    for(const string& airport : result)
        cout << airport << "->";
    cout << "\n";

    result = flights.leastFlights({"OPO"}, {"ORD"});
    for(const string& airport : result)
        cout << airport << "->";
    cout << "\n";

    result = flights.leastFlights({"OPO"}, {"DAX"});
    for(const string& airport : result)
        cout << airport << "->";
    cout << "\n";

    result = flights.leastFlights({"OPO", "YYZ"}, {"DAX"});
    for(const string& airport : result)
        cout << airport << "->";
    cout << "\n";

    result = flights.leastFlights({"OPO", "YYZ"}, {"DAX", "GVA"});
    for(const string& airport : result)
        cout << airport << "->";
    cout << "\n";
    /*
    list<string> airports = {"test1", "test2", "test3", "test4", "test5"};
    flights = Graph(airports);
    flights.addEdge("test1", "test2", "al1");
    flights.addEdge("test2", "test3", "al1");
    flights.addEdge("test3", "test4", "al1");
    flights.addEdge("test4", "test5", "al1");

    result = flights.leastFlights("test1", "test5");
    for(string airport : result)
        cout << airport << "->";
    cout << "\n";

    flights.addEdge("test1", "test3", "al1");
    result = flights.leastFlights("test1", "test5");
    for(string airport : result)
        cout << airport << "->";
    cout << "\n";

    flights.addEdge("test1", "test5", "al1");
    result = flights.leastFlights("test1", "test5");
    for(string airport : result)
        cout << airport << "->";
    cout << "\n";
     */

}

void FeupFlights::showEdgesTest() {
    this->flights.printEdgesTest();
}

double  FeupFlights::haversine(float lat1, float lon1, float lat2, float lon2) {
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

vector<string> FeupFlights::allAirportsLessThan(int x, float lat, float lon) {
    vector<string> res;
    unordered_set<Airport>::iterator it;
    for (it = airports.begin(); it != airports.end();it++){
        float latAirport = it->getLatitude();
        float lonAirport = it->getLongitude();
        double distance = haversine(lat, lon, latAirport, lonAirport);
        if (distance <= double(x)){
            res.push_back(it->getCod());
        }
    }
    return res;

}

vector<string> FeupFlights::allAirportsCity(string city, string country) {
    vector<string> res;
    unordered_set<Airport>::iterator it;
    for (it = airports.begin(); it != airports.end();it++){
        if (it->getCity() == city && it->getCountry() == country){
            res.push_back(it->getCod());
        }
    }
    return res;
}
