//
// Created by Pedro on 28/12/2022.
//

#ifndef AED_PROJECT2_GRAPH_H
#define AED_PROJECT2_GRAPH_H

#include <string>
#include <list>
#include <unordered_map>
#include "airport.h"

using namespace std;

/**
 * Esta classe é utilizada para representar um grafo, com todos os atributos necessários para representar
 *  cada um dos voos nas arestas do grafo e cada um dos aeroportos nos vértices\n
 * Esta classe é uma estensão da classe Graph que nos foi providenciada nas aulas TP desta UC
 */
class Graph {

    /**
     * Struct auxiliar que pretende representar uma aresta do grafo ou, adptando ao problema, um voo
     */
    struct Edge {

        /**
         * Código do vértice de destino, ou seja, o código IATA do aeroporto de destino
         */
        string dest;

        /**
         * Código ICAO da companhia aérea que realiza o voo
         */
        string airline;
    };

    /**
     * Struct auxiliar que pretende representar um véritce do grafo ou, adpatando ao problema, um aeroporto
     */
    struct Node {

        /**
         * Código IATA do aeroporto
         */
        string name;

        /**
         * Lista com todas as arestas que têm como origem o dado vértice, ou seja, lista de todos os voos que partem do
         * aeroporto em questão
         */
        list<Edge> adj;

        /**
         * Boolean que auxilia na pesquisa em largura (BFS) afirmando se o dado vértice já foi, ou não, visitado
         */
        bool visited;

        /**
         * Inteiro que auxilia na pesquisa em largura (BFS) que nos diz a que distancia o dado nó está do nó
         * em que foi iniciada a pesquisa
         */
        int distance;

        /**
         * String que auxilia na pesquisa em largura (BFS) e permite ao vértice saber qual foi o vértice
         *  que lhe precedeu na pesquisa
         */
        string previous;
    };

    /**
     * Número de vértices do grafo
     */
    int n;

public:

    /**
     * Unordered_map que nos permite aceder ao nó que quisermos apenas utilizando o código IATA do aeroporto que
     *  queremos pesquisar no grafo
     */
    unordered_map<string, Node> nodes;

    Graph();

    Graph(const list<string>& nodes);

    void setNodes(const list<string>& nodes);

    void addNode(string node);

    void addEdge(const string& source, string dest, string airline);

    void printEdgesTest();


    void bfs(const vector<string>& source);

    list<string> leastFlights(const vector<string>& source, const vector<string>& dest, const vector<string>& airlines = {});

    void bfsAirLine(const vector<string> &source, const vector<string> &airlines);

    list<string> allFlightsFrom(string cod1, string cod2, list<string> from);

    list<string> allFlights(string cod1, string cod2);

};
#endif //AED_PROJECT2_GRAPH_H
