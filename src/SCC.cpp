#include <algorithm>
#include <iterator>
#include "SCC.h"

using namespace std;

SCC::SCC(Graph && graph)
:   explored_(),
    finishingTimes_(),
    graph_(graph),
    sccs_(),
    t_()
{
}

bool SCC::notExplored(const Vertex & v)
{
    return this->explored_.count(v) == 0;
}

void SCC::DFS1(const NodeIterator first, const NodeIterator last, const Vertex & v)
{
    this->explored_.insert(v);
    this->finishingTimes_[v] = ++this->t_;
    for_each(first, last,
             [this](const Edge & e)
             {
                const Vertex & w = e.second;
                if (this->notExplored(w))
                {
                    const Edges edges = this->graph_.equal_range(w);
                    DFS1(edges.first, edges.second, w);
                }
             });
}

void SCC::DFS2(const NodeIterator first, const NodeIterator last, const Vertex & v, const Vertex & s)
{
    this->explored_.insert(v);
    this->sccs_[s].insert(v);
    for_each(first, last,
             [&s, this](const Edge & e)
             {
                const Vertex & w = e.second;
                if (this->notExplored(w))
                {
                    const Edges edges = this->graph_.equal_range(w);
                    DFS2(edges.first, edges.second, w, s);
                }
             });
}

void SCC::DFS_loop1()
{
    size_t size = this->graph_.size();
    for (Vertex i = --size; i > 0; --i)
    {
        const NodeIterator nit = this->graph_.lower_bound(i);
        const Vertex & v = nit->first;
        if (this->notExplored(v))
        {
            DFS1(nit, this->graph_.upper_bound(i), v);
        }
    }
}

void SCC::DFS_loop2()
{
    Vertex s = Vertex();
    for (auto & ft : this->finishingTimes_)
    {
        const Vertex & v = ft.second;
        if (this->notExplored(v))
        {
            s = v;
            const Edges edges = this->graph_.equal_range(v);
            DFS2(edges.first, edges.second, v, s);
        }
    }
}

Vector SCC::compute()
{
    DFS_loop1();
    this->explored_.clear();
    DFS_loop2();
    Vector sccSizes;
    for (auto & v : this->sccs_)
    {
        sccSizes.emplace_back(v.second.size());
    }
    return sccSizes;
}
