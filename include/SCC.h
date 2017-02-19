#ifndef SCC_H
#define SCC_H

#include <map>
#include <vector>
#include <set>

class Graph;

using FinishingTimes = std::map<Vertex, int>;
using Leaders = std::map<Vertex, Vertex>;
using Vector = std::vector<int>;
using Set = std::set<Vertex>;

class SCC
{
public:
    Vector compute(const Graph & graph);

private:
    bool notExplored(const Vertex & v);
    void DFS(const Graph & g, const Vertex & v, const Vertex & s);
    void DFS_loop(const Graph & g);
    static Graph reverse(const Graph & g);

    FinishingTimes finishingTimes_;
    Leaders leaders_;
    Set explored_;
    size_t t_;
};

#endif // SCC_H
