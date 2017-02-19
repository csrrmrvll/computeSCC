#include <algorithm>
#include <iterator>
#include "Graph.h"
#include "Vertex.h"
#include "SCC.h"

using namespace std;

bool SCC::notExplored(const Vertex & v)
{
    return this->explored_.count(v) == 0;
}

void SCC::DFS(const Graph & g, const Vertex & v, const Vertex & s)
{
    this->explored_.insert(v);
    this->leaders_[v] = s;
    ++this->t_;
    this->finishingTimes_[v] = this->t_;
    const Edges & edges = g.edges(v);
    for_each(edges.first, edges.second,
             [&g, &v, this](const AdjacencyList::value_type & w)
             {
                if (this->notExplored(w.second))
                {
                    DFS(g, w.second, v);
                }
             });
}

void SCC::DFS_loop(const Graph & g)
{
    const AdjacencyList & map = g.map();
    Vertex s = Vertex();
    for_each(map.rbegin(), map.rend(),
            [&g,&s,this](const AdjacencyList::value_type & v)
            {
                if (this->notExplored(v.first))
                {
                    s = v.first;
                    DFS(g, v.first, s);
                }
             });
}

Graph && SCC::reverse(const Graph & g)
{
    const AdjacencyList & map = g.map();
    AdjacencyList result;
    for_each(begin(map), end(map),
             [&result](const AdjacencyList::value_type & v)
             {
                result.insert(make_pair(v.second, v.first));
             });
    return move(Graph(result));
}

Vector SCC::compute(const Graph & g)
{
    Vector sizes;
    const Graph gRev = reverse(g);
    DFS_loop(gRev);
    DFS_loop(g);
    return sizes;
}
