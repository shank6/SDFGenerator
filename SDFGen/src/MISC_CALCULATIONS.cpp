#include "MISC_CALCULATIONS.h"



void MISC_CALCULATIONS::generateRelationalList_Functions(std::ofstream* file, SDFGenerator* sdf, uint sdf_num, bool ignoreType )
{

    std::stringstream ss;
    // Write a seperate routine to print the Nodes, rather than modifying printNodes.
    for(std::vector<Node*>::iterator it = sdf->getNodeList()->begin(); it!= sdf->getNodeList()->end(); it++)
    {
        if(ignoreType)
        {
            *file <<  sdf_num << ',' <<(*it)->getNodeType() << std::endl;
        }
        else
            *file <<  sdf_num << ',' <<(*it)->getLabel() << std::endl;
    }

}

void MISC_CALCULATIONS::generateRelationalList_Composition(std::ofstream* file, SDFGenerator* sdf, uint sdf_num , bool ignoreType )
{
    std::stringstream ss;
    for(std::vector<Edge*>::iterator it = sdf->getEdgeList()->begin(); it!= sdf->getEdgeList()->end(); it++)
    {
        std::pair<Node*, Node*> node_pair = (*it)->getSourceAndDest();
        *file << sdf_num << ',' << node_pair.first->getNodeType() << "_" << node_pair.second->getNodeType() << "_" << (*it)->getTail() << std::endl;
    }

}


MISC_CALCULATIONS::MISC_CALCULATIONS()
{
    //ctor
}

MISC_CALCULATIONS::~MISC_CALCULATIONS()
{
    //dtor
}

