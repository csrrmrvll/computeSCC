#include <algorithm>
#include <iterator>
#include <stack>
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

bool SCC::notExplored(Vertex v)
{
    return this->explored_.count(v) == 0;
}

void SCC::DFS1(Vertex v)
{
    stack<int> s;
    s.push(v);
    while (s.empty() == false)
    {
        v = s.top();
        s.pop();
        if (this->notExplored(v))
        {
            this->explored_.insert(v);
            s.push(v);
            const Edges edges = this->gRev_.equal_range(v);
            for (auto it = edges.first; it != edges.second; ++it)
            {
                Vertex w = it->second;
                if (this->notExplored(w))
                {
                    s.push(w);
                }
            }
        }
        else
        {
            this->finishingTimes_[++this->t_] = v;
        }
    }
}

void SCC::DFS2(Vertex v)
{
    stack<int> s;
    s.push(v);
    Vertex leader = v;
    while (s.empty() == false)
    {
        v = s.top();
        s.pop();
        if (this->notExplored(v))
        {
            this->explored_.insert(v);
            s.push(v);
            ++this->sccs_[leader];
            const Edges edges = this->g_.equal_range(v);
            for (auto it = edges.first; it != edges.second; ++it)
            {
                Vertex w = it->second;
                if (this->notExplored(w))
                {
                    s.push(w);
                }
            }
        }
    }
}

void SCC::DFS_loop1()
{
    for (auto rnit = rbegin(this->gRev_); rnit != rend(this->gRev_); ++rnit)
    {
        const Vertex v = rnit->first;
        if (this->notExplored(v))
        {
            DFS1(v);
        }
    }
}

void SCC::DFS_loop2()
{
    for (auto rit = rbegin(this->finishingTimes_); rit != rend(this->finishingTimes_); ++rit)
    {
        const Vertex v = rit->second;
        if (this->notExplored(v))
        {
            DFS2(v);
        }
    }
}

SCCSizes SCC::compute()
{
    DFS_loop1();
    this->explored_.clear();
    DFS_loop2();
    SCCSizes sccSizes;
    int count = 5;
    for (auto & v : this->sccs_)
    {
        if (count-- == 0) break;
        sccSizes.insert(v.second);
    }
    while (count-- > 0)
    {
        sccSizes.insert(0);
    }
    return sccSizes;
}
