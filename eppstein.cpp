#include "graph.h"
#include <algorithm>
#include <chrono>
#include <limits>

class EppsteinAlgorithm {
private:
    const Graph& graph;
    std::vector<std::vector<int>> maximalCliques;
    
    std::vector<int> calculateDegeneracyOrdering() {
        int n = graph.size();
        std::vector<int> ordering;
        ordering.reserve(n);
        
        std::vector<int> degree(n);
        std::vector<bool> removed(n, false);
        
        for (int v = 0; v < n; ++v) {
            degree[v] = graph[v].size();
        }
        
        for (int i = 0; i < n; ++i) {
            int minDegree = std::numeric_limits<int>::max();
            int minVertex = -1;
            
            for (int v = 0; v < n; ++v) {
                if (!removed[v] && !graph[v].empty() && degree[v] < minDegree) {
                    minDegree = degree[v];
                    minVertex = v;
                }
            }
            
            if (minVertex == -1) break;
            
            ordering.push_back(minVertex);
            removed[minVertex] = true;
            
            for (int u : graph[minVertex]) {
                if (!removed[u]) {
                    degree[u]--;
                }
            }
        }
        
        std::reverse(ordering.begin(), ordering.end());
        return ordering;
    }
    
    void bronKerboschPivot(std::vector<int>& R, std::vector<int>& P, std::vector<int>& X) {
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
            
            bronKerboschPivot(R, newP, newX);
            
            R.pop_back();
            P.erase(std::remove(P.begin(), P.end(), v), P.end());
            X.push_back(v);
        }
    }
    
public:
    EppsteinAlgorithm(const Graph& g) : graph(g) {}
    
    std::vector<std::vector<int>> enumerateMaximalCliques() {
        maximalCliques.clear();
        
        std::vector<int> ordering = calculateDegeneracyOrdering();
        
        for (size_t i = 0; i < ordering.size(); ++i) {
            int v = ordering[i];
            
            if (graph[v].empty()) continue;
            
            std::vector<int> R = {v};
            std::vector<int> P, X;
            
            for (int u : graph[v]) {
                if (std::find(ordering.begin() + i + 1, ordering.end(), u) != ordering.end()) {
                    P.push_back(u);
                } else if (std::find(ordering.begin(), ordering.begin() + i, u) != ordering.begin() + i) {
                    X.push_back(u);
                }
            }
            
            bronKerboschPivot(R, P, X);
        }
        
        return maximalCliques;
    }
};

std::pair<std::vector<std::vector<int>>, double> runEppstein(const Graph& graph) {
    EppsteinAlgorithm eppstein(graph);
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> cliques = eppstein.enumerateMaximalCliques();
    auto end = std::chrono::high_resolution_clock::now();
    
    double time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
    
    return std::make_pair(cliques, time);
}
