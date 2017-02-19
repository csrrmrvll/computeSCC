#include <algorithm>
#include <iterator>
#include "SCC.h"

using namespace std;

SCC::SCC(Graphs && graphs)
:   explored_(),
    finishingTimes_(),
    g_(move(graphs.first)),
    gRev_(move(graphs.second)),
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
    for_each(first, last,
             [this](const Edge & e)
             {
                const Vertex & w = e.second;
                if (this->notExplored(w))
                {
                    const Edges edges = this->gRev_.equal_range(w);
                    DFS1(edges.first, edges.second, w);
                }
             });
    this->finishingTimes_[++this->t_] = v;
}

void SCC::DFS2(const NodeIterator first, const NodeIterator last, const Vertex & v, const Vertex & s)
{
    this->explored_.insert(v);
    this->sccs_[s].insert(v);
    for (NodeIterator it = first ; it != last; ++it)
    {
        const Vertex & w = it->second;
        if (this->notExplored(w))
        {
            const Edges edges = this->g_.equal_range(w);
            DFS2(edges.first, edges.second, w, s);
        }
    }
}

void SCC::DFS_loop1()
{
    for (auto rnit = rbegin(this->gRev_); rnit != rend(this->gRev_); ++rnit)
    {
        const Vertex & v = rnit->first;
        const NodeIterator nit = this->gRev_.lower_bound(v);
        if (this->notExplored(v))
        {
            DFS1(nit, this->gRev_.upper_bound(v), v);
        }
    }
}

void SCC::DFS_loop2()
{
    Vertex s = Vertex();
    for (auto rit = rbegin(this->finishingTimes_); rit != rend(this->finishingTimes_); ++rit)
    {
        const Vertex & v = rit->second;
        if (this->notExplored(v))
        {
            s = v;
            const Edges edges = this->g_.equal_range(v);
            DFS2(edges.first, edges.second, v, s);
        }
    }
}

SCCSizes SCC::compute()
{
    DFS_loop1();
    this->explored_.clear();
    DFS_loop2();
    SCCSizes sccSizes;
    for (auto & v : this->sccs_)
    {
        sccSizes.emplace_back(v.second.size());
    }
    return sccSizes;
}
