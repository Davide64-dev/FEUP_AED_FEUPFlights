//
// Created by Davide Teixeira on 27/12/2022.
//

#include "Airline.h"

Airline::Airline(string cod, string name, string callSign, string country):
    cod(cod), name(name), callSign(callSign), country(country){};

string Airline::getCod() const {
    return cod;
}

string Airline::getName() const {
    return name;
}

string Airline::getCallSign() const {
    return callSign;
}

string Airline::getCountry() const {
    return country;
}