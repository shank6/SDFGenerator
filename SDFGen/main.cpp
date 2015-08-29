/***
****** Author : Shankar Kartik Jawahar
        Embedded Systems Lab,
        Northeastern University
******
    Random Graph Generator v0.1
    Main Program
    Connected Classes - Node, Edge, SDFGenerator

*****

***/





#include <iostream>

#include "AnalysisSDF.h"

#define MAX_NODES   20
#define MIN_NODES   5
#define MAX_EDGES   (4*MAX_NODES)

using namespace std;


int main()
{
    const string filePath = "graph";
    ofstream *obj;
    obj = new ofstream(filePath.c_str(), ios::out);

    try
    {
        AnalysisSDF::Initialize();
    }
    catch(const string& s)
    {
        cout << s << endl;
    }
    catch(...)
    {
        cout << " Something went wrong" << endl;
    }


    uint nodes = rand() % MAX_NODES + MIN_NODES;
    uint edges = rand() % MAX_EDGES + MIN_NODES - 1;

    try
    {
        SDFGenerator g1(nodes, edges);
        g1.buildGraph();
        g1.printTheGraphinDot(PrintOp::File, obj);

    }
    catch(exception ex)
    {
        cout << ex.what() << std::endl;
    }



    obj->close();
    return 0;
}
