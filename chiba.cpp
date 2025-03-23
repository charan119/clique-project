#include "graph.h"
#include <algorithm>
#include <chrono>

class ChibaSimple {
private:
    const Graph& graph;
    std::vector<std::vector<int>> cliques;

    int getTotalVertices() {
        int total = graph.size();
        return total;
    }

    std::vector<int> makeZeroList(int length) {
        std::vector<int> zeros;
        int position = 0;
        while (position < length) {
            zeros.push_back(0);
            position = position + 1;
        }
        return zeros;
    }

    std::vector<bool> makeEmptyFlags(int length) {
        std::vector<bool> flags;
        int position = 0;
        while (position < length) {
            flags.push_back(false);
            position = position + 1;
        }
        return flags;
    }

    int countEdges(int vertex) {
        int edges = graph[vertex].size();
        return edges;
    }

    int hasValue(int number, std::vector<int> list) {
        int index = 0;
        while (index < list.size()) {
            if (list[index] == number) {
                return 1;
            }
            index = index + 1;
        }
        return 0;
    }

    int choosePivotVertex(std::vector<int> candidates) {
        int pivot = -1;
        int maxEdges = -1;
        int outer = 0;
        while (outer < candidates.size()) {
            int vertex = candidates[outer];
            int edgeCount = 0;
            int inner = 0;
            while (inner < candidates.size()) {
                int other = candidates[inner];
                int found = hasValue(other, graph[vertex]);
                if (found) {
                    edgeCount = edgeCount + 1;
                }
                inner = inner + 1;
            }
            if (edgeCount > maxEdges) {
                maxEdges = edgeCount;
                pivot = vertex;
            }
            outer = outer + 1;
        }
        return pivot;
    }

    std::vector<int> replicateList(std::vector<int> original) {
        std::vector<int> duplicate;
        int position = 0;
        while (position < original.size()) {
            duplicate.push_back(original[position]);
            position = position + 1;
        }
        return duplicate;
    }

    void deleteFromList(std::vector<int>& list, int value) {
        std::vector<int> revised;
        int position = 0;
        while (position < list.size()) {
            int current = list[position];
            if (current != value) {
                revised.push_back(current);
            }
            position = position + 1;
        }
        list = revised;
    }

    void addToList(std::vector<int>& list, int value) {
        list.push_back(value);
    }

    void removeLast(std::vector<int>& list) {
        list.pop_back();
    }

    int isListEmpty(std::vector<int> list) {
        int empty = 0;
        if (list.size() == 0) {
            empty = 1;
        }
        return empty;
    }

    void exploreCliques(std::vector<int>& current, std::vector<int>& excluded, std::vector<int>& candidates) {
        int candEmpty = isListEmpty(candidates);
        int exclEmpty = isListEmpty(excluded);
        int bothEmpty = candEmpty && exclEmpty;
        if (bothEmpty) {
            cliques.push_back(current);
            return;
        }

        int pivot = choosePivotVertex(candidates);
        std::vector<int> candCopy = replicateList(candidates);

        int index = 0;
        while (index < candCopy.size()) {
            int vertex = candCopy[index];
            int connected = hasValue(vertex, graph[pivot]);
            if (connected) {
                index = index + 1;
                continue;
            }

            addToList(current, vertex);

            std::vector<int> newCandidates;
            int candIndex = 0;
            while (candIndex < candidates.size()) {
                int candVertex = candidates[candIndex];
                int linked = hasValue(candVertex, graph[vertex]);
                if (linked) {
                    addToList(newCandidates, candVertex);
                }
                candIndex = candIndex + 1;
            }

            std::vector<int> newExcluded;
            int exclIndex = 0;
            while (exclIndex < excluded.size()) {
                int exclVertex = excluded[exclIndex];
                int linked = hasValue(exclVertex, graph[vertex]);
                if (linked) {
                    addToList(newExcluded, exclVertex);
                }
                exclIndex = exclIndex + 1;
            }

            exploreCliques(current, newExcluded, newCandidates);

            removeLast(current);
            deleteFromList(candidates, vertex);
            addToList(excluded, vertex);
            index = index + 1;
        }
    }

    std::vector<std::pair<int, int>> listVertexDegrees() {
        std::vector<std::pair<int, int>> degrees;
        int vertex = 0;
        while (vertex < graph.size()) {
            int edgeCount = countEdges(vertex);
            int hasEdges = edgeCount > 0;
            if (hasEdges) {
                std::pair<int, int> degreePair = std::make_pair(edgeCount, vertex);
                degrees.push_back(degreePair);
            }
            vertex = vertex + 1;
        }
        return degrees;
    }

    void sortDegrees(std::vector<std::pair<int, int>>& degrees) {
        std::sort(degrees.begin(), degrees.end());
    }

public:
    ChibaSimple(const Graph& inputGraph) : graph(inputGraph) {}

    std::vector<std::vector<int>> findAllCliques() {
        cliques.clear();
        std::vector<std::pair<int, int>> vertexDegrees = listVertexDegrees();
        sortDegrees(vertexDegrees);

        int pairIndex = 0;
        while (pairIndex < vertexDegrees.size()) {
            int vertex = vertexDegrees[pairIndex].second;
            std::vector<int> current;
            addToList(current, vertex);
            std::vector<int> candidates;
            std::vector<int> excluded;

            int neighborIndex = 0;
            while (neighborIndex < graph[vertex].size()) {
                int neighbor = graph[vertex][neighborIndex];
                int neighborEdges = countEdges(neighbor);
                int vertexEdges = countEdges(vertex);
                int moreEdges = neighborEdges > vertexEdges;
                int sameEdges = neighborEdges == vertexEdges;
                int higherVertex = neighbor > vertex;
                int lessEdges = neighborEdges < vertexEdges;
                int lowerVertex = neighbor < vertex;

                int addToCand = moreEdges || (sameEdges && higherVertex);
                int addToExcl = lessEdges || (sameEdges && lowerVertex);

                if (addToCand) {
                    addToList(candidates, neighbor);
                }
                if (addToExcl) {
                    addToList(excluded, neighbor);
                }
                neighborIndex = neighborIndex + 1;
            }

            exploreCliques(current, excluded, candidates);
            pairIndex = pairIndex + 1;
        }

        return cliques;
    }
};

std::pair<std::vector<std::vector<int>>, double> startChiba(const Graph& input) {
    ChibaSimple solver(input);
    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> cliqueList = solver.findAllCliques();
    std::chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
    int duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - begin).count();
    double timeTaken = duration / 1000.0;
    std::pair<std::vector<std::vector<int>>, double> resultPair = std::make_pair(cliqueList, timeTaken);
    return resultPair;
}
