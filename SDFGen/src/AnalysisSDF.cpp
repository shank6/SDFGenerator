#include "AnalysisSDF.h"

int AnalysisSDF::counter = 0;
void AnalysisSDF::Initialize() throw(std::string)
{

    bool ret_value = Node::buildDataBase(MAX_POSSIBLE_NODES);   // build the Node database
//    std::srand(time(NULL)); // initialize the random seed

    if(!ret_value)
    {
        throw std::string("Initialization Failed");
    }

    return;

}

bool AnalysisSDF::checkMinEdges(uint nodes, uint edges)
{
    if(edges < nodes - 1)
        return false;
    return true;

}

void AnalysisSDF::dottyFontFix(std::ofstream *obj)
{
    std::stringstream ss;
    ss << " graph [fontname=\"fixed\"]; \n node [fontname=\"fixed\"] \n edge [fontname=\"fixed\"] " <<std::endl;

    *obj << ss.str();
}


AnalysisSDF::AnalysisSDF()
{
    //ctor
}

AnalysisSDF::~AnalysisSDF()
{
    //dtor
}


void AnalysisSDF::PrintRounds()
{
    AnalysisSDF::counter++;
    std::cout << " Tries " << AnalysisSDF::counter << std::endl;
}
