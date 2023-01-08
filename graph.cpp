//
// Created by Pedro on 28/12/2022.
//

#include <iostream>
#include <queue>
#include "graph.h"
#include <algorithm>

using namespace std;

/**
 * Construtor da classe Grafo\n
 * Trata-se de um construtor que não recebe argumentos e cria um grafo sem vértices nem arestas
 */
Graph::Graph() {
    this->nodes.clear();
    this->n = 0;
}

/**
 * Construtor da classe Grafo\n
 * @param nodes Lista com os nós do grafo
 */
Graph::Graph(const list<string>& nodes) {
    setNodes(nodes);
}

/**
 * Complexidade: O(n)
 * @param nodes Lista com os nós que passarão a fazer parte do Grafo
 */
void Graph::setNodes(const list<string> &nodes) {
    this->nodes.clear();
    this->n = nodes.size();
    for(const string& source : nodes) {
        Node node;
        node.adj.clear();
        node.name = source;
        this->nodes.insert({source, node});
    }
}

/**
 * Adiciona um vértice ao grafo\n
 * Complexidade: O(1)
 * @param node Nó a ser adicionado
 */
void Graph::addNode(string node) {
    Node node1;
    node1.adj.clear();
    node1.name = node;
    this->nodes.insert({node, node1});
}

/**
 * Adiciona uma aresta ao grafo\n
 * Complexidade: O(1)
 * @param source Código em cujo nó será adicionada uma aresta
 * @param dest Código do nó de destino
 * @param airline Companhia aérea que irá realizar o voo
 */
void Graph::addEdge(const string& source, string dest, string airline) {
    if(nodes.find(source) != nodes.end())
        nodes[source].adj.push_back({dest, airline});
}

/**
 * Algoritmo BFS (Pesquisa em Largura) que nos permite percorrer todos os vértices do grafo por ordem de distância
 *  vértice escolhido\n
 *  Complexidade: O(|E|+|V|)
 * @param source Código do vértice sobre o qual se irá iniciar a pesquisa em largura
 */
void Graph::bfs(const vector<string>& source) {
    queue<Node> unvisited_nodes;

    for(auto& node : nodes) {
        node.second.visited = false;
        node.second.distance = -1;
        node.second.previous = "";
    }

    for(const string& airport : source) {
        nodes[airport].distance = 0;
        nodes[airport].visited = true;
        unvisited_nodes.push(nodes[airport]);
    }

    while(!unvisited_nodes.empty()) {
        Node nodeU = unvisited_nodes.front();
        unvisited_nodes.pop();
        list<Edge> neighborsU = nodeU.adj;
        for(const Edge& edgeW : neighborsU) {
            string nodeW = edgeW.dest;
            if(!nodes[nodeW].visited) {
                nodes[nodeW].visited = true;
                nodes[nodeW].distance = nodeU.distance + 1;
                nodes[nodeW].previous = nodeU.name;
                unvisited_nodes.push(nodes[nodeW]);
            }
        }
    }
}

/**
 * Algoritmo que recebe todas as possibilidades de partida, destino e de companhias aéreas e retorna todo o percurso
 *  entre um aeroporto e o outro - Percurso com menos escalas que obedeça a todas essas condições\n
 *  Complexidade: O(|E|+|V|)
 * @param source Vetor com todos os aeroportos que foram selecionados como possibilidades de partida
 * @param dest Vetor com todos os aeroportos que foram selecionados como possiblidades de chegada
 * @param airlines Vetor com todas as airlines que podem ser utilizadas no percurso - Se o vetor estiver vazio,
 * é assumido que se podem utilizar todas as companhias existentes
 * @return Vetor ordenado com o percurso de aeroportos de um ponto de partida a um ponto de chegada
 */
list<string> Graph::leastFlights(const vector<string>& source, const vector<string>& dest, const vector<string>& airlines) {
    list<string> airports;
    string airport;
    int min = INT_MAX;

    //Chama bfs normal se não foram indicadas airlines.
    if(airlines.empty())
        bfs(source);
    else
        bfsAirLine(source, airlines);

    //Determina qual destino é oq tem menor voos
    for(const string& s : dest) {
        if(nodes[s].distance != -1 && nodes[s].distance < min) {
            airport = s;
            min = nodes[s].distance;
        }
    }

    if(airport.empty())
        return airports;


    while(nodes[airport].distance != 0) {
        airports.push_front(airport);
        airport = nodes[airport].previous;
    }
    airports.push_front(airport);

    return airports;
}

/**
 * Método bfs especifico que é utilizando quando se quer restringir as companhias aereas a serem utilizadas\n
 * Complexidade: O(|E|+|V|)
 * @param source Vetor com todas as possiblidades de partida
 * @param airlines Vetor com todas as companhias aeres que podem ser utilizadas
 */
void Graph::bfsAirLine(const vector<string>& source, const vector<string>& airlines) {
    queue<Node> unvisited_nodes;

    for(auto& node : nodes) {
        node.second.visited = false;
        node.second.distance = -1;
        node.second.previous = "";
    }

    unordered_map<string, Node> nodes = this->nodes;

    for(auto& node : nodes) {
        for(auto it = node.second.adj.begin(); it != node.second.adj.end();) {
            if(find(airlines.begin(), airlines.end(), it->airline) == airlines.end())
                it = node.second.adj.erase(it);
            else
                it++;
        }
    }

    for(const string& airport : source) {
        nodes[airport].distance = 0;
        nodes[airport].visited = true;

        this->nodes[airport].distance = 0;
        this->nodes[airport].visited = true;
        unvisited_nodes.push(nodes[airport]);
    }

    while(!unvisited_nodes.empty()) {
        Node nodeU = unvisited_nodes.front(); unvisited_nodes.pop();
        list<Edge> neighborsU = nodeU.adj;
        for(const Edge& edgeW : neighborsU) {
            string nodeW = edgeW.dest;
            if(!nodes[nodeW].visited) {
                nodes[nodeW].visited = true;
                nodes[nodeW].distance = nodeU.distance + 1;
                nodes[nodeW].previous = nodeU.name;

                this->nodes[nodeW].visited = true;
                this->nodes[nodeW].distance = nodeU.distance + 1;
                this->nodes[nodeW].previous = nodeU.name;
                unvisited_nodes.push(nodes[nodeW]);
            }
        }
    }
}

/**
 * Método que recebe o código de dois aeroportos e as companhias aereas que podem ser utilizadas e
 * retorna um vetor com todos os voos de um local para o outro\n
 * Complexidade: O(|E|)
 * @param cod1 Código do primeiro aeroporto
 * @param cod2 Código do segundo aeroporto
 * @param from Vetor com as companhias aereas que podem ser utilizadas
 * @return Todas as companhias aéreas que realizam o voo de um local para o outro;
 */
list<string> Graph::allFlightsFrom(string cod1, string cod2, vector<string> from) {
    list<string> res;
    Node node = nodes[cod1];
    for (auto i : node.adj){
        if (i.dest == cod2 && find(from.begin(), from.end(),i.airline) != from.end()){
            res.push_back(i.airline);
        }
    }
    return res;
}

/**
 * Método que recebe o código de dois aeroportos e retorna todas as companhias aereas que fazem o percurso\n
 * Complexidade: O(|E|)
 * @param cod1 Código do primeiro aeroporto
 * @param cod2 Código do segundo aeroporto
 * @return Todas as companhias aereas que realizam o percurso dado
 */
list<string> Graph::allFlights(string cod1, string cod2) {
    list<string> res;
    Node node = nodes[cod1];
    for (auto i : node.adj){
        if (i.dest == cod2){
            res.push_back(i.airline);
        }
    }
    return res;
}


