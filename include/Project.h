#ifndef PROJECT_H
#define PROJECT_H

#include "Global.h"
#include "Module.h"
#include <vector>

class Project
{
    public:
        Project();
        virtual ~Project();

        void ReadAppParams(int argc, char* argv[]);
        void Proccess();

        unsigned int GetModulesCount();
        Module GetModule(int index);

        void CreateOutPutFolder();

        std::string CoveragePercent(int value, int total);

        void GenerateHTMLReport();

        GETSET(std::string, inputDir, InputDir);
        GETSET(std::string, outputDir, OutputDir);
    protected:

    private:
        std::vector<Module> modules;
};

#endif // PROJECT_H
