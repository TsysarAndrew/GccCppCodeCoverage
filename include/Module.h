#ifndef MODULE_H
#define MODULE_H

#include "Global.h"
#include <vector>
#include "Line.h"

class Line;
class Module
{
    public:
        Module();
        virtual ~Module();

        void Proccess(std::string gcovFileName);
        unsigned int GetLinesCount1();
        Line GetLine(int index);

        void IncAnalysisLinesCount();
        void IncCalledLinesCount();

        void SetMacroses(std::vector<std::string>* macroses);

        void GenerateHTMLReport(std::string outputDir);

        GETSET(int, calledLinesCount, CalledLinesCount);
        GETSET(int, analysisdLinesCount, AnalysisLinesCount);
        GETSET(std::string, moduleName, ModuleName);
    protected:

    private:
        std::vector<Line> lines;
        std::vector<std::string>* macroses;
};

#endif // MODULE_H
