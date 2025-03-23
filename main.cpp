#include "graph.h"
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <string>
#include <chrono>

std::pair<std::vector<std::vector<int>>, double> runTomita(const Graph& graph);
std::pair<std::vector<std::vector<int>>, double> launchEppstein(const Graph& graph);
std::pair<std::vector<std::vector<int>>, double> startChiba(const Graph& graph);

void analyzeCliques(const std::vector<std::vector<int>>& cliques) {
    int maxSize = 0;
    std::unordered_map<int, int> sizeDistribution;
    
    for (const auto& clique : cliques) {
        sizeDistribution[clique.size()]++;
        if (static_cast<int>(clique.size()) > maxSize) {
            maxSize = clique.size();
        }
    }
    
    std::cout << "Total number of maximal cliques: " << cliques.size() << std::endl;
    std::cout << "Largest clique size: " << maxSize << std::endl;
    std::cout << "Clique size distribution:" << std::endl;
    
    for (int i = 2; i <= maxSize; ++i) {
        if (sizeDistribution[i] > 0) {
            std::cout << "Size " << i << ": " << sizeDistribution[i] << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <graph_file>" << std::endl;
        return 1;
    }
    
    std::string filename = argv[1];
    std::cout << "Reading graph from " << filename << "..." << std::endl;
    
    Graph graph = readGraph(filename);
    
    int nodeCount = 0;
    for (const auto& neighbors : graph) {
        if (!neighbors.empty()) {
            nodeCount++;
        }
    }
    
    std::cout << "Graph loaded with " << nodeCount << " non-isolated nodes." << std::endl;
    std::cout << "Graph has " << countEdges(graph) << " edges." << std::endl;
    std::cout << "\nRunning Tomita algorithm..." << std::endl;
    std::pair<std::vector<std::vector<int>>, double> t_result = runTomita(graph);
    std::vector<std::vector<int>> t_cliques = t_result.first;
    double t_time = t_result.second;
    
    std::cout << "\nRunning Eppstein algorithm..." << std::endl;
    std::pair<std::vector<std::vector<int>>, double> e_result = launchEppstein(graph);
    std::vector<std::vector<int>> e_cliques = e_result.first;
    double e_time = e_result.second;
    
    std::cout << "\nRunning Chiba algorithm..." << std::endl;
    std::pair<std::vector<std::vector<int>>, double> c_result = startChiba(graph);
    std::vector<std::vector<int>> c_cliques = c_result.first;
    double c_time = c_result.second;
    
    std::cout << "\n=========== Results ===========" << std::endl;
    std::cout << "Tomita algorithm: " << t_cliques.size() 
              << " cliques in " << std::fixed << std::setprecision(2) << t_time << " seconds" << std::endl;
    std::cout << "Eppstein algorithm: " << e_cliques.size() 
              << " cliques in " << std::fixed << std::setprecision(2) << e_time << " seconds" << std::endl;
    std::cout << "Chiba algorithm: " << c_cliques.size() 
              << " cliques in " << std::fixed << std::setprecision(2) << c_time << " seconds" << std::endl;
    
    std::cout << "\n=========== Analysis ===========" << std::endl;
    analyzeCliques(t_cliques);
    return 0;
}
