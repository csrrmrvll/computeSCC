#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <map>
#include <utility>

class Vertex;
using AdjacencyList = std::multimap<Vertex,Vertex>;
using Edge = AdjacencyList::value_type;
using node_iterator = AdjacencyList::const_iterator;
using Edges = std::pair<node_iterator,node_iterator>;

#endif // ADJACENCYLIST_H
