#include <iostream>
#include <fstream>
#include "Project.h"
#include "WindowsOS.h"
#include "HTMLService.h"
#include <clocale>
#include <windows.h>

using namespace std;

int main(int argc, char* argv[])
{
    //setlocale(LC_ALL, "Russian");

    Project project;
    project.ReadAppParams(argc, argv);

    if((project.GetInputDir() == std::string("")) || (project.GetOutputDir() == std::string("")))
    {
        std::cerr << "usage: GccCppCodeCovering.exe -i[nputDir] <dir with *.gcov files> -o[utputDir] <dir for html report>" << std::endl;
        std::cerr << "If outputDir does't exist, the will be created." << std::endl;

        return 1;
    }

    project.Proccess();

    if(project.GetModulesCount() == 0)
    {
        return 1;
    }

    project.GenerateHTMLReport();
    return 1;
}
