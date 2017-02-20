#ifndef SCC_H
#define SCC_H

#include <map>
#include <set>
#include <utility>

using Vertex = int;
using Nodes = std::set<Vertex>;
using ExploredNodes = Nodes;
using Graph = std::multimap<Vertex,Vertex>;
using Graphs = std::pair<Graph,Graph>;
using Edge = Graph::value_type;
using NodeIterator = Graph::const_iterator;
using Edges = std::pair<NodeIterator,NodeIterator>;
using FinishingTimes = std::map<Vertex, int>;
using SCCs = std::map<Vertex, size_t>;
using SCCSizes = std::multiset<size_t,std::greater<size_t>>;

class SCC
{
public:
    SCC(Graphs && graphs);
    SCCSizes compute();

private:
    bool notExplored(Vertex v);
    void DFS1(Vertex v);
    void DFS2(Vertex v);
    void DFS_loop1();
    void DFS_loop2();

    ExploredNodes explored_;
    FinishingTimes finishingTimes_;
    const Graph g_;
    const Graph gRev_;
    SCCs sccs_;
    size_t t_;
};

#endif // SCC_H
