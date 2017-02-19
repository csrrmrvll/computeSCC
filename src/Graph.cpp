#include "AdjacencyList.h"
#include "Graph.h"
#include "Vertex.h"

using namespace std;

Graph::Graph(AdjacencyList && al)
:   map_(al)
{
}

Graph::Graph(const AdjacencyList & al)
:   map_(al)
{
}

Edges Graph::edges(const Vertex & v) const
{
    return this->map_.equal_range(v);
}

