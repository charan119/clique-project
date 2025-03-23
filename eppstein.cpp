#include "graph.h"
#include <algorithm>
#include <chrono>

class EppsteinBasic {
private:
    const Graph& graph;
    std::vector<std::vector<int>> cliques;

    int findGraphSize() {
        int size = 0;
        size = graph.size();
        return size;
    }

    std::vector<int> createNumberList(int size) {
        std::vector<int> numbers;
        int index = 0;
        while (index < size) {
            numbers.push_back(0);
            index = index + 1;
        }
        return numbers;
    }

    std::vector<bool> createFalseList(int size) {
        std::vector<bool> flags;
        int index = 0;
        while (index < size) {
            flags.push_back(false);
            index = index + 1;
        }
        return flags;
    }

    int countVertexLinks(int vertex) {
        int links = 0;
        links = graph[vertex].size();
        return links;
    }

    int pickSmallestVertex(int size, std::vector<int> degrees, std::vector<bool> removed) {
        int smallest = 1000000; // Big number instead of max
        int chosen = -1;
        int index = 0;
        while (index < size) {
            int noLinks = 0;
            if (graph[index].size() == 0) {
                noLinks = 1;
            }
            if (removed[index] == false && noLinks == 0 && degrees[index] < smallest) {
                smallest = degrees[index];
                chosen = index;
            }
            index = index + 1;
        }
        return chosen;
    }

    void lowerDegrees(int vertex, std::vector<int>& degrees, std::vector<bool> removed) {
        int index = 0;
        while (index < graph[vertex].size()) {
            int neighbor = graph[vertex][index];
            if (removed[neighbor] == false) {
                degrees[neighbor] = degrees[neighbor] - 1;
            }
            index = index + 1;
        }
    }

    void flipList(std::vector<int>& list) {
        std::vector<int> flipped;
        int index = list.size() - 1;
        while (index >= 0) {
            flipped.push_back(list[index]);
            index = index - 1;
        }
        list = flipped;
    }

    std::vector<int> buildOrder() {
        int total = findGraphSize();
        std::vector<int> order;
        std::vector<int> degrees = createNumberList(total);
        std::vector<bool> removed = createFalseList(total);

        int step = 0;
        while (step < total) {
            degrees[step] = countVertexLinks(step);
            step = step + 1;
        }

        step = 0;
        while (step < total) {
            int vertex = pickSmallestVertex(total, degrees, removed);
            if (vertex == -1) {
                break;
            }
            order.push_back(vertex);
            removed[vertex] = true;
            lowerDegrees(vertex, degrees, removed);
            step = step + 1;
        }

        flipList(order);
        return order;
    }

    int checkIfPresent(int value, std::vector<int> list) {
        int index = 0;
        while (index < list.size()) {
            if (list[index] == value) {
                return 1;
            }
            index = index + 1;
        }
        return 0;
    }

    int selectPivot(std::vector<int> possible) {
        int pivot = -1;
        int maxLinks = -1;
        int index = 0;
        while (index < possible.size()) {
            int current = possible[index];
            int links = 0;
            int count = 0;
            while (count < possible.size()) {
                int other = possible[count];
                if (checkIfPresent(other, graph[current])) {
                    links = links + 1;
                }
                count = count + 1;
            }
            if (links > maxLinks) {
                maxLinks = links;
                pivot = current;
            }
            index = index + 1;
        }
        return pivot;
    }

    std::vector<int> duplicateList(std::vector<int> source) {
        std::vector<int> copy;
        int index = 0;
        while (index < source.size()) {
            copy.push_back(source[index]);
            index = index + 1;
        }
        return copy;
    }

    void dropFromList(std::vector<int>& list, int value) {
        std::vector<int> updated;
        int index = 0;
        while (index < list.size()) {
            if (list[index] != value) {
                updated.push_back(list[index]);
            }
            index = index + 1;
        }
        list = updated;
    }

    void searchClique(std::vector<int>& current, std::vector<int>& excluded, std::vector<int>& possible) {
        int possEmpty = possible.size() == 0;
        int exclEmpty = excluded.size() == 0;
        if (possEmpty && exclEmpty) {
            cliques.push_back(current);
            return;
        }

        int pivotVertex = selectPivot(possible);
        std::vector<int> possCopy = duplicateList(possible);

        int index = 0;
        while (index < possCopy.size()) {
            int vertex = possCopy[index];
            int skipIt = checkIfPresent(vertex, graph[pivotVertex]);
            if (skipIt) {
                index = index + 1;
                continue;
            }

            current.push_back(vertex);

            std::vector<int> newPoss;
            int posIdx = 0;
            while (posIdx < possible.size()) {
                if (checkIfPresent(possible[posIdx], graph[vertex])) {
                    newPoss.push_back(possible[posIdx]);
                }
                posIdx = posIdx + 1;
            }

            std::vector<int> newExcl;
            int exclIdx = 0;
            while (exclIdx < excluded.size()) {
                if (checkIfPresent(excluded[exclIdx], graph[vertex])) {
                    newExcl.push_back(excluded[exclIdx]);
                }
                exclIdx = exclIdx + 1;
            }

            searchClique(current, newExcl, newPoss);

            current.pop_back();
            dropFromList(possible, vertex);
            excluded.push_back(vertex);
            index = index + 1;
        }
    }

public:
    EppsteinBasic(const Graph& inputGraph) : graph(inputGraph) {}

    std::vector<std::vector<int>> listCliques() {
        cliques.clear();
        std::vector<int> order = buildOrder();

        int index = 0;
        while (index < order.size()) {
            int vertex = order[index];
            int noLinks = graph[vertex].size() == 0;
            if (noLinks) {
                index = index + 1;
                continue;
            }

            std::vector<int> current;
            current.push_back(vertex);
            std::vector<int> possible;
            std::vector<int> excluded;

            int linkIdx = 0;
            while (linkIdx < graph[vertex].size()) {
                int neighbor = graph[vertex][linkIdx];
                int isAfter = 0;
                int isBefore = 0;
                int orderIdx = 0;
                while (orderIdx < order.size()) {
                    if (order[orderIdx] == neighbor && orderIdx > index) {
                        isAfter = 1;
                    }
                    if (order[orderIdx] == neighbor && orderIdx < index) {
                        isBefore = 1;
                    }
                    orderIdx = orderIdx + 1;
                }
                if (isAfter) {
                    possible.push_back(neighbor);
                }
                if (isBefore) {
                    excluded.push_back(neighbor);
                }
                linkIdx = linkIdx + 1;
            }

            searchClique(current, excluded, possible);
            index = index + 1;
        }

        return cliques;
    }
};

std::pair<std::vector<std::vector<int>>, double> launchEppstein(const Graph& input) {
    EppsteinBasic solver(input);
    auto startTime = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> results = solver.listCliques();
    auto endTime = std::chrono::high_resolution_clock::now();
    double seconds = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / 1000.0;
    return std::make_pair(results, seconds);
}
