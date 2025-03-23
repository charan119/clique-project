#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

typedef std::vector<std::vector<int>> Graph;

Graph readGraph(const std::string& filename);
int countEdges(const Graph& graph);

#endif // GRAPH_H
