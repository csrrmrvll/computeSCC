#ifndef VERTEX_H
#define VERTEX_H

#include <ostream>
#include <vector>

class Vertex
{
public:
    Vertex() : id_(-1) {}
    Vertex(int id);
    int id() const;

private:
    int id_;
};

bool operator==(const Vertex & a, const Vertex & b);
bool operator<(const Vertex & a, const Vertex & b);
std::ostream & operator<<(std::ostream & os, const Vertex & v);

#endif // VERTEX_H
