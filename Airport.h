//
// Created by Davide Teixeira on 27/12/2022.
//

#ifndef AED_PROJECT2_AIRPORT_H
#define AED_PROJECT2_AIRPORT_H

#include <string>

using namespace std;

/**
 * Esta classe pretende representar um aeroporto
 */
class Airport {

    /**
     * Código IATA do areoporto
     */
    string cod;

    /**
     * Nome do aeroporto
     */
    string name;

    /**
     * Cidade onde se localiza o aeroporto
     */

    string city;

    /**
     * País onde se localiza o aeroporto
     */
    string country;

    /**
     * Latitude da localização
     */
    float latitude;

    /**
     * Longitude da localização
     */
    float longitude;

public:
    Airport(string cod, string name, string city, string country,float latitude, float longitude);
    string getCod() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;
};

/**
 * Struct auxliar utilizada no unordered_set "airports" na classe "FeupFlights"
 */
struct HashAirport
{
    /**
     * Hash Function a ser utilizada no unordered_set\n
     * A Hash function recebe o código do aeroporto (3 letras) e gera um número inteiro que consiste
     * na concatenação dos códigos ASCII de cada uma das letras do código, gerando um número inteiro único para cada código\n
     * Complexidade: O(1)
     * @param b Aeroporto sobre o qual irá ser aplicada a função hash
     * @return Valor inteiro proveniente da concatenaçãodos códigos ASCII de cada um dos caracteres
     */
    int operator() (const Airport& b) const {
        string temp = "";
        for (unsigned i = 0; i < 3;i++){
            int num = int(b.getCod()[i]);
            temp = temp + to_string(num);
        }
        return stoi(temp);
    }

    /**
     * Equality Function a ser utilizada no unordered_set\n
     * A Equality Function recebe dois aeroportos e retorna a igualdade como verdadeira se e somente se
     *  os seus cósigos IATA sejam iguais\n
     *  Complexidade: O(1)
     * @param b1 Primeiro Aeroporto
     * @param b2 Segundo Aeroporto
     * @return Valor boolean sobre a igualdade, ou diferença, dos aeroportos
     */
    bool operator() (const Airport& b1, const Airport& b2) const {
        return b1.getCod() == b2.getCod();
    }
};

#endif //AED_PROJECT2_AIRPORT_H
