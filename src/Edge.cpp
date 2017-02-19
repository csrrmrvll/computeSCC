#include <algorithm>
#include "Edge.h"
#include "Vertex.h"

using namespace std;

Edge::Edge(const Vertex & a, const Vertex & b)
:   endpoints_(std::make_pair(a,b))
{
}

Edge::Edge(const Endpoints & endpoints)
:   Edge(endpoints.first,endpoints.second)
{
}

Endpoints & Edge::endpoints() { return this->endpoints_; }

