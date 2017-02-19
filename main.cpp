#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include "AdjacencyList.h"
#include "Graph.h"
#include "SCC.h"
#include "Vertex.h"

using namespace std;
using Vector = vector<int>;

AdjacencyList read()
{
    AdjacencyList al;
    ifstream is;
    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\computeSCC\\SCC.txt",ios::in);
//    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\computeSCC\\tc1.txt",ios::in);
//    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\computeSCC\\tc2.txt",ios::in);
//    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\computeSCC\\tc3.txt",ios::in);
//    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\computeSCC\\tc4.txt",ios::in);
//    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\computeSCC\\tc5.txt",ios::in);
//    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\computeSCC\\tc6.txt",ios::in);
    if (is.is_open())
    {
        string line;
        while (getline(is,line))
        {
            Vector v;
            istringstream iss(line);
            copy(istream_iterator<int>(iss),istream_iterator<int>(), back_insert_iterator<Vector>(v));
//            copy(begin(v),end(v),ostream_iterator<int>(cout, " "));
//            cout << endl;
            const Vertex vertex{v[0]};
            al.insert(make_pair(Vertex(v[0]), Vertex(v[1])));
        }
    }
    else
    {
        throw runtime_error("File is not open!!");
    }
    is.close();
    return al;
}

ostream & operator<<(ostream & out, const Vector & v)
{
    copy(begin(v), end(v), ostream_iterator<int>(cout));
    return out;
}

int main()
{
    const Graph g{read()};
    SCC scc;
    const Vector sizes = scc.compute(g);
    cout << "SCC sizes: " << sizes << endl;
    return 0;
}
