/***
****** Author : Shankar Kartik Jawahar
        Embedded Systems Lab,
        Northeastern University
        current version - v0.2
******
    Random SDF Generator v0.1
    Main Program
    Connected Classes - Node, Edge, SDFGenerator

*****
    Random SDF Generator v0.2
    Main Program
    Updates
    Generate SDF's for the given count
    Create "inputFile.txt" - which contains the 'Transaction(SDF) , Node' format for apriori
***/





#include <iostream>

#include "MISC_CALCULATIONS.h"

#define MAX_NODES   10
#define MIN_NODES   5
#define MAX_EDGES   (2*MAX_NODES)
#define SDF_COUNT   4
#define SDF_IN_FILE true
#define FLOATING_NODES  false

/* Notes : for FLOATING_NODES implementation _ modify SDFGenerator 383 and dependencies */

using namespace std;

int main()
{
    uint count_sdf;
    ofstream* inputFile, *edgeFile;
    inputFile = new ofstream("FunctionList", ofstream::out);
    edgeFile = new ofstream("CompositonList", ofstream::out);
    srand(time(NULL));
    for(count_sdf=0; count_sdf < SDF_COUNT; count_sdf++)
    {

        stringstream ss;
        ss << "sdf" << count_sdf;

        // Modify this to read from command line
        bool option_to_write_in_file = SDF_IN_FILE;

        const string filePath = ss.str();
        ofstream *obj;

        if(option_to_write_in_file)
        {

            obj = new ofstream(filePath.c_str(), ios::out);
        }
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
        uint edges = rand() % MAX_EDGES + nodes - 1;

        cout << "graph N: " << nodes << " E: " << edges << endl;

        try
        {
            SDFGenerator g1(nodes, edges);
            g1.buildGraph();

            if(option_to_write_in_file)
            {
                g1.printTheGraphinDot(PrintOp::File, obj);
            }
            cout << " Generating : SDF " << count_sdf << endl;
            MISC_CALCULATIONS::generateRelationalList_Functions(inputFile, &g1, count_sdf+1, true);
            MISC_CALCULATIONS::generateRelationalList_Composition(edgeFile, &g1, count_sdf+1);


        }
        catch(exception ex)
        {
            cout << ex.what() << std::endl;
        }


        if(option_to_write_in_file)
        {
            obj->close();
        }
    }
    inputFile->close();
    return 0;
}
