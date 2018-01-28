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
    //setlocale(LC_CTYPE, "");
    setlocale(LC_ALL, "Russian");
    //SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    //SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

    Project project;

    project.ReadAppParams(argc, argv);

//    project.SetInputDir("C:\\Work\\ООО Надежное ПО\\Проект Запись видео\\Source\\Unit-Tests\\Unit-tests\\obj\\coverage1");
//    project.SetOutputDir("C:\\Work\\ООО Надежное ПО\\Проект Запись видео\\Source\\Unit-Tests\\Unit-tests\\obj\\html");

 //   std::cerr << "GetInputDir = " << project.GetInputDir() << std::endl;
 //   std::cerr << "GetOutputDir = " << project.GetOutputDir() << std::endl;

    if((project.GetInputDir() == std::string("")) || (project.GetOutputDir() == std::string("")))
    {
        std::cerr << "usage: GccCppCodeCovering.exe -i[nputDir] <dir with *.gcov files> -o[utputDir] <dir for html report> -m[acrosesList] <path to file with macroses list>" << std::endl;
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
