#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <map>
#include <vector>

class Vertex;
using VVector = std::vector<Vertex>;
using AdjacencyList = std::map<Vertex,VVector>;

#endif // ADJACENCYLIST_H
