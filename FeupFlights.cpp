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

/**
 * Construtor da classe FeupFlights;
 */
FeupFlights::FeupFlights() = default;

/**
 * Método que lê o ficheiro airlines.csv, cria os objetos da classe Airline e adiciona-os ao unordered_set
 *  airlines\n
 *  Complexidade: O(n)
 */
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

/**
 * Método que lê o ficheiro airports.csv, cria os objetos da classe Airport, adiciona-os ao unordered_set airports
 * , para além de criar os vértices do grafo flights\n
 * Complexidade: O(n)
 */
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

/**
 * Método que lê o ficheiro flights.csv e cria as arestas do grafo flights\n
 * Complexidade: O(n)
 */
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

    result = flights.leastFlights({"OPO"}, {"LHR"}, {"TAP"});
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
 /**
  * Método que recebe as coordenadas geográficas de dois locais e calcula a distância entre eles\n
  * Complexiade: O(1)
  * @param lat1 Latitude do primeiro local
  * @param lon1 Longitude do primeiro local
  * @param lat2 Latitude do segundo local
  * @param lon2 Longitude do segundo local
  * @return Distância entre os locais
  */
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

/**
 * Método que recebe um valor x e dois valores que representam as coordenadas gepfráfias de um local e reotrna um vetor
 * com todos os aeroportos que se encontram a uma distância inferior a x km\n
 * Complexidade: O(n)
 * @param x Máxima distância que é permitida na pesquisa, inclusive
 * @param lat Latitude da localização
 * @param lon Longitude da localização
 * @return Retorna um vetor com todos os aeroportos a menos de x km
 */
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

/**
 * Método que recebe o nome de uma cidade e o país onde se encontra essa mesma cidade e retorna um vetor com todos
 * os aeroportos que se encontram nessa mesma cidade\n
 * Complexidade: O(n)
 * Nota: É necessário passar o país como argumento porque há cidades com o mesmo nome em países diferentes
 * @param city Nome da cidade
 * @param country Nome do país
 * @return Retorna um vetor com todos os aeroportos que se encontram na cidade dada
 */
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

Airport FeupFlights::findAirport(std::string cod) {
    Airport temp = Airport(cod, "cdws", "fdasdv", "dvs", 234, 1234);
    Airport res = *airports.find(temp);
    return res;
}

Airline FeupFlights::findAirline(std::string cod) {
    Airline temp = Airline(cod, "xvsd", "dfsx", "dfsvx");
    Airline res = *airlines.find(temp);
    return res;
}
/**
 * Método que recebe o nome de um país e retorna um vetor com todos
 * os aeroportos que se encontram nesse mesmo país\n
 * Complexidade: O(n)
 * @param country Nome do país
 * @return Retorna um vetor com todos os aeroportos que se encontram nesse país
 */
vector<string> FeupFlights::allAirportsFromCountry(string country) {
    vector<string> res;
    unordered_set<Airport>::iterator it;
    for (it = airports.begin(); it != airports.end();it++){
        if ( it->getCountry() == country){
            res.push_back(it->getCod());
        }
    }
    return res;
}

/**
 * Método que recebe o nome de uma cidade e retorna um vetor com todos
 * os aeroportos que se encontram nessa mesma cidade\n
 * Complexidade: O(n)
 * @param country Nome do país
 * @return Retorna um vetor com todos os aeroportos que se encontram nessa cidade
 */
vector<string> FeupFlights::allAirportsFromCity(string city) {
    vector<string> res;
    unordered_set<Airport>::iterator it;
    for (it = airports.begin(); it != airports.end();it++){
        if ( it->getCity() == city){
            res.push_back(it->getCod());
        }
    }
    return res;
}

/**
 * Método que recebe o nome de um país e retorna um vetor com todas
 * as companhias aereas desse mesmo país\n
 * Complexidade: O(n)
 * @param country Nome do país
 * @return Retorna um vetor com todas as companhias aereas desse mesmo país
 */
vector<string> FeupFlights::allAirlinesFromCountry(string country){
    vector<string> res;
    unordered_set<Airline>::iterator it;
    for (it = airlines.begin(); it != airlines.end();it++){
        if ( it->getCountry() == country){
            res.push_back(it->getCod());
        }
    }
    return res;
}

int FeupFlights::manyFlights(string airport) {
    return flights.nodes[airport].adj.size();
}

int FeupFlights::differentAirlines(string airport) {
    unordered_map<string, int>temp;
    auto it = flights.nodes[airport].adj.begin();
    while(it != flights.nodes[airport].adj.end()){
        temp[it->airline]++;
        it++;
    }
    return temp.size();
}

int FeupFlights::differentDestenies(string airport) {
    unordered_map<string, int>temp;
    auto it = flights.nodes[airport].adj.begin();
    while(it != flights.nodes[airport].adj.end()){
        Airport aero = Airport(it->dest, "d", "d", "d", 1, 1);
        temp[airports.find(aero)->getCity()]++;
        it++;
    }
    return temp.size();
}

int FeupFlights::differentCountries(string airport) {
    unordered_map<string, int>temp;
    auto it = flights.nodes[airport].adj.begin();
    while(it != flights.nodes[airport].adj.end()){
        Airport aero = Airport(it->dest, "d", "d", "d", 1, 1);
        temp[airports.find(aero)->getCountry()]++;
        it++;
    }
    return temp.size();
}

int FeupFlights::airportsLessThanY(string airport, int y) {
    int count = 0;
    vector<string> ini;
    ini.push_back(airport);
    flights.bfs(ini);
    auto it = airports.begin();
    for (auto it : flights.nodes){
        if (it.second.distance <= y){
            count++;
        }
    }
    return count;
}

int FeupFlights::citiesLessThanY(string airport, int y) {
    unordered_map<string, int> count;
    vector<string> ini;
    ini.push_back(airport);
    flights.bfs(ini);
    auto it = airports.begin();
    for (auto it : flights.nodes){
        if (it.second.distance <= y){
            string nome = it.second.name;
            Airport aero = Airport(nome, "d", "d", "d", 1, 1);
            Airport oi = *airports.find(aero);
            count[oi.getCity()]++;
        }
    }
    return count.size();
}

int FeupFlights::countriesLessThanY(string airport, int y) {
    unordered_map<string, int> count;
    vector<string> ini;
    ini.push_back(airport);
    flights.bfs(ini);
    auto it = airports.begin();
    for (auto it : flights.nodes){
        if (it.second.distance <= y){
            string nome = it.second.name;
            Airport aero = Airport(nome, "d", "d", "d", 1, 1);
            Airport oi = *airports.find(aero);
            count[oi.getCountry()]++;
        }
    }
    return count.size();
}