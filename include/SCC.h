#ifndef SCC_H
#define SCC_H

#include <vector>

class Graph;

using Vector = std::vector<int>;
class SCC
{
public:
    static Vector compute(const Graph & graph);
};

#endif // SCC_H
