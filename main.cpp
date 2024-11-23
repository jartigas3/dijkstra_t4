#include "Graph.hpp"
#include <iostream>

int main() {
    Graph graph(0);

    std::string command;
    std::cout << "--- Bienvenido al programa Dijkstra ---\n";

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "loadGraph") {
            std::string filename;
            std::cin >> filename;
            try {
                graph.loadFromFile(filename);
                std::cout << "Grafo cargado exitosamente.\n";
            } catch (const std::exception& e) {
                std::cerr << e.what() << "\n";
            }
        } else if (command == "dijkstra") {
            int start, end;
            std::cin >> start >> end;
            graph.dijkstra(start, end);
        } else if (command == "exit") {
            std::cout << "Cerrando el programa...\n";
            break;
        } else {
            std::cout << "Comando no reconocido.\n";
        }
    }

    
    return 0;
}
