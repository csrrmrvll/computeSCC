#include "AdjacencyList.h"
#include "Graph.h"

using namespace std;

Graph::Graph(const AdjacencyList & al)
{
    for (const AdjacencyList::value_type & v : al)
    {
        const Vertex & first = v.first;
        this->vertices_.push_back(first);
        const VVector & adjacentVertices = v.second;
        for (const Vertex & second : adjacentVertices)
        {
            if (first < second)
            {
                const Edge edge(first, second);
                this->edges_.push_back(edge);
            }
        }
    }
}

Vertices & Graph::vertices() { return this->vertices_; }
const Vertices & Graph::vertices() const { return this->vertices_; }
Edges & Graph::edges() { return this->edges_; }
const Edges & Graph::edges() const { return this->edges_; }

ostream & operator<<(ostream & os, Edges & edges)
{
    os << "[";
    Edges::iterator itLast = --end(edges);
    for (Edges::iterator it = begin(edges); it != itLast; ++it)
    {
        const Endpoints & endpoints = it->endpoints();
        os << "(" << endpoints.first << "," << endpoints.second << "),";
    }
    Edge & last = *itLast;
    const Endpoints & endpoints = last.endpoints();
    os << "(" << endpoints.first << "," << endpoints.second << ")]" << endl;
    return os;
}

ostream & operator<<(ostream & os, Vertices & vertices)
{
    os << "[";
    Vertices::iterator itLast = --end(vertices);
    for (Vertices::iterator it = begin(vertices); it != itLast; ++it)
    {
        os << *it << ",";
    }
    Vertex & last = *itLast;
    os << last << "]" << endl;
    return os;
}
