//
// Created by Davide Teixeira on 27/12/2022.
//

#include <vector>
#include <fstream>
#include <sstream>
#include "FeupFlights.h"


FeupFlights::FeupFlights() = default;

void FeupFlights::readAirlines() {
    vector<string> lineV(3);
    ifstream in("../dataset/airlines.csv");
    string cod, name, callSign, country;
    string line, word;
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