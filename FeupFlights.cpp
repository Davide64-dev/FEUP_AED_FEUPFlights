//
// Created by Davide Teixeira on 27/12/2022.
//

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "FeupFlights.h"


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

void FeupFlights::showEdgesTest() {
    this->flights.printEdgesTest();
}
