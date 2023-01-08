//
// Created by Davide Teixeira on 27/12/2022.
//

#ifndef AED_PROJECT2_AIRLINE_H
#define AED_PROJECT2_AIRLINE_H

#include <string>

using namespace std;

/**
 * Esta classe pretende representar uma companhia aérea
 */
class Airline {

    /**
     * Código ICAO da companhia aérea
     */
    string cod;

    /**
     * Nome da companhia aérea
     */
    string name;

    /**
     * "Alcunha" da companhia aérea
     */
    string callSign;

    /**
     * País de origem
     */
    string country;

public:
    Airline(string cod, string name, string callSign, string country);
    string getCod() const;
    string getName() const;
    string getCallSign() const;
    string getCountry() const;
};

/**
 * Struct auxiliar utilizada no unordered_set "airlines" na classe "FeupFlights"
 */
struct HashAirline
{
    /**
     * Hash Function a ser utilizada no unordered_set\n
     * A Hash function recebe o código da companhia aérea (3 letras) e gera um número inteiro que consiste
     * na concatenação dos códigos ASCII de cada uma das letras do código, gerando um número inteiro único para cada código\n
     * Complexidade: O(1)
     * @param b Companhia aérea sobre a qual irá ser aplicada a função hash
     * @return Valor inteiro proveniente da concatenação dos códigos ASCII de cada um dos caracteres
     */
    int operator() (const Airline& b) const {
        string temp = "";
        for (unsigned i = 0; i < 3;i++){
            int num = int(b.getCod()[i]);
            temp = temp + to_string(num);
        }
        return stoi(temp);
    }

    /**
     * Equality Function a ser utilizada no unordered_set\n
     * A Equality Function recebe duas companhias aéreas e retorna a igualdade como verdadeira se e somente se
     *  os seus códigos ICAO sejam iguais\n
     *  Complexidade: O(1)
     * @param b1 Primeira Companhia Aérea
     * @param b2 Segunda Companhia Aérea
     * @return Valor boolean sobre a igualdade, ou diferença, das companhias aéreas
     */
    bool operator() (const Airline& b1, const Airline& b2) const {
        return b1.getCod() == b2.getCod();
    }
};


#endif //AED_PROJECT2_AIRLINE_H
