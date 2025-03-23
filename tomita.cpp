#include "graph.h"
#include <algorithm>
#include <chrono>

class TomitaAlgorithm {
private:
    const Graph& graph;
    std::vector<std::vector<int>> maximalCliques;
    
    void expand(std::vector<int>& R, std::vector<int>& P, std::vector<int>& X) {
        if (P.empty() && X.empty()) {
            maximalCliques.push_back(R);
            return;
        }
        
        int pivot = -1;
        int maxCount = -1;
        
        for (int u : P) {
            int count = 0;
            for (int v : P) {
                if (std::binary_search(graph[u].begin(), graph[u].end(), v)) {
                    ++count;
                }
            }
            if (count > maxCount) {
                maxCount = count;
                pivot = u;
            }
        }
        
        std::vector<int> P_copy = P;
        
        for (int v : P_copy) {
            if (std::binary_search(graph[pivot].begin(), graph[pivot].end(), v)) {
                continue;
            }
            
            R.push_back(v);
            
            std::vector<int> newP, newX;
            for (int u : P) {
                if (std::binary_search(graph[v].begin(), graph[v].end(), u)) {
                    newP.push_back(u);
                }
            }
            for (int u : X) {
                if (std::binary_search(graph[v].begin(), graph[v].end(), u)) {
                    newX.push_back(u);
                }
            }
            
            expand(R, newP, newX);
            
            R.pop_back();
            P.erase(std::remove(P.begin(), P.end(), v), P.end());
            X.push_back(v);
        }
    }
    
public:
    TomitaAlgorithm(const Graph& g) : graph(g) {}
    
    std::vector<std::vector<int>> enumerateMaximalCliques() {
        maximalCliques.clear();
        std::vector<int> R, P, X;
        
        for (size_t v = 0; v < graph.size(); ++v) {
            if (!graph[v].empty()) {
                P.push_back(v);
            }
        }
        
        expand(R, P, X);
        
        return maximalCliques;
    }
};

std::pair<std::vector<std::vector<int>>, double> runTomita(const Graph& graph) {
    TomitaAlgorithm tomita(graph);
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> cliques = tomita.enumerateMaximalCliques();
    auto end = std::chrono::high_resolution_clock::now();
    
    double time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
    
    return std::make_pair(cliques, time);
}
