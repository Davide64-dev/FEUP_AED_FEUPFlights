//
// Created by Pedro on 28/12/2022.
//

#ifndef AED_PROJECT2_GRAPH_H
#define AED_PROJECT2_GRAPH_H

#include <string>
#include <list>
#include <unordered_map>

using namespace std;

class Graph {
    struct Edge {
        string dest;
        string airline;
    };

    struct Node {
        list<Edge> adj;
        bool visited;
    };

    int n;
    unordered_map<string, Node> nodes;

public:
    Graph();

    Graph(const list<string>& nodes);

    void setNodes(const list<string>& nodes);

    void addEdge(const string& source, string dest, string airline);

};
#endif //AED_PROJECT2_GRAPH_H
