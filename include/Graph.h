#ifndef GRAPH_H
#define GRAPH_H

#include <utility>
#include "AdjacencyList.h"

using Edges = std::pair<AdjacencyList::const_iterator, AdjacencyList::const_iterator>;

class Vertex;

class Graph
{
public:
    Graph(AdjacencyList && al);
    Graph(const AdjacencyList & al);
    Edges edges(const Vertex & v) const;
    const AdjacencyList & map() const { return this->map_; }

private:
    AdjacencyList map_;
};

#endif // GRAPH_H
