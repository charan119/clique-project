#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

Graph readGraph(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        exit(1);
    }

    std::string line;
    std::vector<std::pair<int, int>> edges;
    std::unordered_map<int, int> vertexMap;
    int nextIndex = 0;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);
        int src, dst;
        iss >> src >> dst;
        
        if (vertexMap.find(src) == vertexMap.end()) {
            vertexMap[src] = nextIndex++;
        }
        if (vertexMap.find(dst) == vertexMap.end()) {
            vertexMap[dst] = nextIndex++;
        }
        
        edges.push_back(std::make_pair(src, dst));
    }

    int n = vertexMap.size();
    Graph graph(n);
    
    for (const auto& edge : edges) {
        int src = vertexMap[edge.first];
        int dst = vertexMap[edge.second];
        
        if (src != dst) {
            graph[src].push_back(dst);
            graph[dst].push_back(src);
        }
    }

    for (auto& neighbors : graph) {
        std::sort(neighbors.begin(), neighbors.end());
        neighbors.erase(std::unique(neighbors.begin(), neighbors.end()), neighbors.end());
    }

    std::cout << "Converted " << edges.size() << " directed edges to " 
              << countEdges(graph) << " undirected edges" << std::endl;
    std::cout << "Mapped " << vertexMap.size() << " original vertices to 0-based indices" << std::endl;

    return graph;
}

int countEdges(const Graph& graph) {
    int count = 0;
    for (const auto& neighbors : graph) {
        count += neighbors.size();
    }
    return count / 2;
}
