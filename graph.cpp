//
// Created by Pedro on 28/12/2022.
//

#include <iostream>
#include <queue>
#include "graph.h"

using namespace std;

/**
 * Construtor da classe Grafo\n
 * Trata-se de um construtor que não recebe argumentos e criar um grafo sem vértices nem arestas
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

void Graph::printEdgesTest() {
    for (auto node : nodes){
        for (auto dest : node.second.adj){
            cout << node.first << "," << dest.dest << "," << dest.airline << endl;
        }
    }
}

/**
 * Algoritmo BFS (Pesquisa em Largura) que nos permite percorrer todos os vértices do grafo por ordem de distância
 *  vértice escolhido\n
 *  Complexidade: O(|E|+|V|)
 * @param source Código do vértice sobre o qual se irá iniciar a pesquisa em largura
 */
void Graph::bfs(const string& source) {
    queue<Node> unvisited_nodes;

    for(auto& node : nodes) {
        node.second.visited = false;
        node.second.distance = -1;
        node.second.previous = "";
    }
    nodes[source].distance = 0;
    unvisited_nodes.push(nodes[source]);

    while(!unvisited_nodes.empty()) {
        Node nodeU = unvisited_nodes.front(); unvisited_nodes.pop();
        list<Edge> neighborsU = nodeU.adj;
        for(const Edge& edgeW : neighborsU) {
            string nodeW = edgeW.dest;
            if(!nodes[nodeW].visited) {
                unvisited_nodes.push(nodes[nodeW]);
                nodes[nodeW].visited = true;
                nodes[nodeW].distance = nodeU.distance + 1;
                nodes[nodeW].previous = nodeU.name;
            }
        }
    }
}

list<string> Graph::leastFlights(const string& source, const string& dest) {
    list<string> airports;

    bfs(source);
    if(nodes[dest].distance == -1)
        return airports;

    string airport = dest;
    while(airport != source) {
        airports.push_front(airport);
        airport = nodes[airport].previous;
    }
    airports.push_front(airport);

    return airports;
}



