//
// Created by Davide Teixeira on 27/12/2022.
//

#include "Airport.h"
using namespace std;

/**
 * Construtor da classe Airport
 * @param cod Código IATA
 * @param name Nome
 * @param city Cidade de localização
 * @param country País de localização
 * @param latitude Latitude da localização
 * @param longitude Longitude da localização
 */
Airport::Airport(string cod, string name, string city, string country,float latitude, float longitude):
    cod(cod), name(name), city(city), country(country),latitude(latitude), longitude(longitude){};

/**
 * Complexidade: O(1)
 * @return Retorna o código IATA do aeroporto
 */
string Airport::getCod() const {
    return cod;
}

/**
 * Complexidade: O(1)
 * @return Retorna o nome do aeroporto
 */
string Airport::getName() const {
    return name;
}

/**
 * Complexidade: O(1)
 * @return Retorna a cidade de localização do aeroporto
 */
string Airport::getCity() const {
    return city;
}

/**
 * Complexidade: O(1)
 * @return Retorna o país de localização do aeroporto
 */
string Airport::getCountry() const {
    return country;
}

/**
 * Complexidade: O(1)
 * @return Retorna a Latitude da localização do aeroporto
 */
float Airport::getLatitude() const{
    return latitude;
}

/**
 * Complexidade: O(1)
 * @return Retorna a Longitude da localização do aeroporto
 */
float Airport::getLongitude() const {
    return longitude;
}


