#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include "SCC.h"

using namespace std;

Graphs read()
{
    Graph g, gRev;
    ifstream is;
    is.open("/home/csr/dev/computeSCC/SCC.txt",ios::in);
//    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\computeSCC\\tc1.txt",ios::in);
//    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\computeSCC\\tc2.txt",ios::in);
//    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\computeSCC\\tc3.txt",ios::in);
//    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\computeSCC\\tc4.txt",ios::in);
//    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\computeSCC\\tc5.txt",ios::in);
    if (is.is_open())
    {
        string line;
        while (getline(is,line))
        {
            using Vector = vector<int>;
            Vector v;
            istringstream iss(line);
            copy(istream_iterator<int>(iss),istream_iterator<int>(), back_insert_iterator<Vector>(v));
            g.insert(make_pair(Vertex(v[0]), Vertex(v[1])));
            gRev.insert(make_pair(Vertex(v[1]), Vertex(v[0])));
        }
    }
    else
    {
        throw runtime_error("File is not open!!");
    }
    is.close();
    return make_pair(g, gRev);
}

ostream & operator<<(ostream & out, const SCCSizes & v)
{
    copy(begin(v), end(v), ostream_iterator<int>(cout,","));
    return out;
}

int main()
{
    SCC scc(read());
    const SCCSizes sizes = scc.compute();
    cout << "SCC sizes: " << sizes << endl;
    return 0;
}
