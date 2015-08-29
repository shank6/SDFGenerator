#ifndef ANALYSISSDF_H
#define ANALYSISSDF_H

#include "SDFGenerator.h"



class AnalysisSDF
{
    public:
        static int counter;
        static void PrintRounds(); // A function to print the loop iteration count
        static void dottyFontFix(std::ofstream *obj); // A fix for dotty format to see the labels
        static void Initialize() throw(std::string); // Initializes the Database
        static bool checkMinEdges(uint, uint); // Check for a possibility of a SDF
        static bool checkSDFPath();
        AnalysisSDF();

        virtual ~AnalysisSDF();
    protected:
    private:
};

#endif // ANALYSISSDF_H
