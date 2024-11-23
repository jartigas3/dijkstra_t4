#include "Graph.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <utility>

Graph::Graph(int vertices) : numVertices(vertices) {
    adjacencyList.resize(vertices);
}

void Graph::addEdge(int source, int destination, int weight) {
    adjacencyList[source].push_back({destination, weight});
    adjacencyList[destination].push_back({source, weight}); // Si es un grafo no dirigido
}

void Graph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("n_vertex:") == 0) {
            numVertices = std::stoi(line.substr(9));
            adjacencyList.resize(numVertices);
        } else if (line.find("edge_") == 0) {
            std::istringstream edgeLine(line.substr(line.find(":") + 1));
            int source, destination, weight;
            edgeLine >> source >> destination >> weight;
            addEdge(source, destination, weight);
        }
    }
}


void Graph::dijkstra(int start, int end) {
    std::vector<int> distances(numVertices, std::numeric_limits<int>::max());
    std::vector<int> previous(numVertices, -1);
    distances[start] = 0;
    using Node = std::pair<int, int>; 
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> minHeap;
    minHeap.push({0, start});
    while (!minHeap.empty()) {
        int currentDistance = minHeap.top().first;
        int currentVertex = minHeap.top().second;
        minHeap.pop();
        if (currentDistance > distances[currentVertex]) {
            continue;
        }
        for (const auto& edge : adjacencyList[currentVertex]) {
            int neighbor = edge.destination;
            int weight = edge.weight;
            int newDistance = currentDistance + weight;
            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                previous[neighbor] = currentVertex;
                minHeap.push({newDistance, neighbor});
            }
        }
    }
    std::vector<int> path;
    for (int at = end; at != -1; at = previous[at]) {
        path.insert(path.begin(), at);
    }
    if (distances[end] == std::numeric_limits<int>::max()) {
        std::cout << "No hay camino entre " << start << " y " << end << ".\n";
    } else {
        std::cout << "Camino más corto: ";
        for (int vertex : path) {
            std::cout << vertex << " ";
        }
        std::cout << "\nCosto: " << distances[end] << "\n";
    }
}

void Graph::printGraph() {
    for (int i = 0; i < adjacencyList.size(); ++i) {
        std::cout << i << ": ";
        for (const auto& edge : adjacencyList[i]) {
            std::cout << "(" << edge.destination << ", " << edge.weight << ") ";
        }
        std::cout << "\n";
    }
}
