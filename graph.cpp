//
// Created by Pedro on 28/12/2022.
//

#include "graph.h"

using namespace std;

Graph::Graph() {
    this->nodes.clear();
    this->n = 0;
}

Graph::Graph(const list<string>& nodes) {
    setNodes(nodes);
}

void Graph::setNodes(const list<string> &nodes) {
    this->nodes.clear();
    this->n = nodes.size();
    for(const string& source : nodes) {
        Node node;
        node.adj.clear();
        this->nodes.insert({source, node});
    }
}

void Graph::addEdge(const string& source, string dest, string airline) {
    if(nodes.find(source) != nodes.end())
        nodes[source].adj.push_back({dest, airline});
}



