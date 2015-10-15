#ifndef MISC_CALCULATIONS_H
#define MISC_CALCULATIONS_H

#include "AnalysisSDF.h"

class MISC_CALCULATIONS
{
    public:
        MISC_CALCULATIONS();
        virtual ~MISC_CALCULATIONS();

        static void generateRelationalList_Functions(std::ofstream* file, SDFGenerator* sdf, uint sdf_num, bool ignoreType = false); // Generates an input file for apriory algorithm
        static void generateRelationalList_Composition(std::ofstream* file, SDFGenerator* sdf, uint sdf_num, bool ignoreType = false);
    protected:
    private:
};

#endif // MISC_CALCULATIONS_H
