#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <limits>
#include <iostream>
#include <queue>

struct Edge {
    int destination;
    int weight;
};

class Graph {
private:
    int numVertices;
    std::vector<std::vector<Edge>> adjacencyList;

public:
    Graph(int vertices);
    void addEdge(int source, int destination, int weight);
    void loadFromFile(const std::string& filename);
    void dijkstra(int start, int end);

    void printGraph(); 
};

#endif
