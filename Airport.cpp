//
// Created by Davide Teixeira on 27/12/2022.
//

#include "Airport.h"
using namespace std;

Airport::Airport(string cod, string name, string city, string country,float latitude, float longitude):
    cod(cod), name(name), city(city), country(country),latitude(latitude), longitude(longitude){};

string Airport::getCod() const {
    return cod;
}

string Airport::getName() const {
    return name;
}

string Airport::getCity() const {
    return city;
}

string Airport::getCountry() const {
    return country;
}

float Airport::getLatitude() const{
    return latitude;
}

float Airport::getLongitude() const {
    return longitude;
}


