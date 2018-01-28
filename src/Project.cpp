#include "Project.h"
#include <dirent.h>
#include "WindowsOS.h"
#include <iostream>
#include "HTMLService.h"

Project::Project()
{

}

Project::~Project()
{
    //dtor
}

void Project::ReadAppParams(int argc, char* argv[])
{

    if (argc > 1)
    {
        for (int index = 1; index < argc; index ++)
        {
            std::string value(argv[index]);

            //std::cerr << "param = " << value << std::endl;

            if((value == "-inputDir") || (value == "-i"))
            {
                SetInputDir(std::string(argv[index + 1]));
            }

            if((value == "-outputDir") || (value == "-o"))
            {
                SetOutputDir(std::string(argv[index + 1]));
            }

            if((value == "-macrosesList") || (value == "-m"))
            {
                SetMacrosesListFileName(std::string(argv[index + 1]));
            }
        }
    }
}

void Project::ReadMacrosesList()
{
    if(GetMacrosesListFileName() == "")
    {
        return;
    }

    macroses.clear();

    std::ifstream file(GetMacrosesListFileName());

    std::string macrosName;
    while(std::getline(file, macrosName))
    {
        macroses.push_back(macrosName);
    }
}

void Project::Proccess()
{
     DIR           *d;
     struct dirent *dir;
     d = opendir(GetInputDir().c_str());
     if (d)
     {
         while ((dir = readdir(d)) != NULL)
         {
            if( strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0 )
            {
                continue;
            }

           //std::cerr << "dir->d_name = " << GetInputDir() + "\\" + dir->d_name << std::endl;

            Module module;
            module.SetMacroses(&macroses);
            module.Proccess(GetInputDir() + "\\" + dir->d_name);
            modules.push_back(module);
        }
    }
}

void Project::CreateOutPutFolder()
{
    std::string outputDir_ = GetOutputDir();
    std::string currentDir = "";

    WindowsOS os;
    size_t slashPosition = 0;
    while (outputDir_ != "")
    {
        slashPosition = outputDir_.find("\\");
        if(slashPosition == std::string::npos)
        {
            currentDir += outputDir_;
            outputDir_ = "";
        }
        else
        //if(currentDir == "")
        //{
        {
            currentDir += outputDir_.substr(0, slashPosition) + "\\";
            outputDir_ = outputDir_.substr(slashPosition + 1, outputDir_.size() - slashPosition);
        }
            //continue;
        //}
        if(!os.CheckDir(currentDir))
        {
            os.CreateDir(currentDir);
            //std::cerr << "need create dir - " << currentDir << std::endl;
        }
    }
}


std::string Project::CoveragePercent(int value, int total)
{
    if(total == 0)
    {
        return "-";
    }

    float percent = (float) value / total * 100;
    return std::to_string((int) percent);
}

void Project::GenerateHTMLReport()
{
    HTMLService html;

    html.StartHTMLFile().Paragraph("Статистика по проекту").StartTable().StartTableRow().TableColumn("Модуль").
        TableColumn("Строк всего").TableColumn("Покрытых тестами строк").TableColumn("%").EndTableRow();

    int linesCount = 0;
    int calledLinessCount = 0;

    std::string coveragePercent = "";
    for(int index = 0; index <= GetModulesCount() - 1; index++)
    {
        Module currentModule = GetModule(index);
        currentModule.GenerateHTMLReport(GetOutputDir());

        coveragePercent = CoveragePercent(currentModule.GetCalledLinesCount(), currentModule.GetAnalysisLinesCount());

        if (currentModule.GetCalledLinesCount() == currentModule.GetAnalysisLinesCount())
        {
            html.StartTableRow("#b3ffb3");
        }
        else
        {
            html.StartTableRow("#ffb3b3");
        }

        html.TableCell(html.HyperLinkTag(currentModule.GetModuleName(), currentModule.GetModuleName() + ".html")).
           TableCell(std::to_string(currentModule.GetAnalysisLinesCount())).
           TableCell(std::to_string(currentModule.GetCalledLinesCount())).TableCell(coveragePercent).EndTableRow();

        linesCount += currentModule.GetAnalysisLinesCount();
        calledLinessCount += currentModule.GetCalledLinesCount();
    }

    coveragePercent = CoveragePercent(calledLinessCount, linesCount);
    html.StartTableRow().TableCell("Всего").TableCell(std::to_string(linesCount)).
           TableCell(std::to_string(calledLinessCount)).TableCell(coveragePercent).EndTableRow();

    html.EndTable().EndHTMLFile();

    std::ofstream file(GetOutputDir() + "\\index.html");
    file << html.GetHTML();
    file.close();
}


unsigned int Project::GetModulesCount()
{
    return modules.size();
}

Module Project::GetModule(int index)
{
    return modules[index];
}

