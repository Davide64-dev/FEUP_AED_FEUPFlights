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

public:

    unordered_map<string, Node> nodes;

    Graph();

    Graph(const list<string>& nodes);

    void setNodes(const list<string>& nodes);

    void addNode(string node);

    void addEdge(const string& source, string dest, string airline);

    void printEdgesTest();
};
#endif //AED_PROJECT2_GRAPH_H
