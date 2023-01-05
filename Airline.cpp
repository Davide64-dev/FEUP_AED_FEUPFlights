//
// Created by Davide Teixeira on 27/12/2022.
//

#include "Airline.h"

/**
 * Construtor da classe Airline
 * @param cod Código ICAO
 * @param name Nome "oficial"
 * @param callSign "Alcunha"
 * @param country País de origem
 */
Airline::Airline(string cod, string name, string callSign, string country):
    cod(cod), name(name), callSign(callSign), country(country){};

/**
 * Complexidade: O(1)
 * @return Retorna o código ICAO da companhia aérea
 */
string Airline::getCod() const {
    return cod;
}

/**
 * Complexidade: O(1)
 * @return Retorna o nome da companhia aérea
 */
string Airline::getName() const {
    return name;
}

/**
 * Complexiade: O(1)
 * @return Retorna a "alcunha" da companhia aérea
 */
string Airline::getCallSign() const {
    return callSign;
}

/**
 * Complexidade: O(1)
 * @return Retorna o país de origem da companhia aérea
 */
string Airline::getCountry() const {
    return country;
}