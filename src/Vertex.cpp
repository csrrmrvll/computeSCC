#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(int id)
:   id_(id)
{
}

int Vertex::id() const { return this->id_; }

bool operator==(const Vertex & a, const Vertex & b)
{
    return a.id() == b.id();
}

bool operator<(const Vertex & a, const Vertex & b)
{
    return a.id() < b.id();
}

std::ostream & operator<<(std::ostream & os, const Vertex & v)
{
    os << v.id();
    return os;
}
