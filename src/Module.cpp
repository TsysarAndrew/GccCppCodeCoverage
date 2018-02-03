#include "Module.h"
#include <fstream>
#include <iostream>
#include "WindowsOS.h"
#include "HTMLService.h"
#include "windows.h"
#include <exception>

Module::Module()
{
    SetCalledLinesCount(0);
    SetAnalysisLinesCount(0);
}

Module::~Module()
{
    //dtor
}

unsigned int Module::GetLinesCount1()
{
    return lines.size();
}

Line Module::GetLine(int index)
{
    return lines[index];
}

void Module::Proccess(std::string gcovFileName)
{

    WindowsOS os;

    std::string moduleName = os.ShortFileName(gcovFileName);
    moduleName = os.FileNameFromGcovFileName(moduleName);
    moduleName = os.ShortFileName(moduleName);

    SetModuleName(moduleName);

    std::ifstream file_;
    file_.open(gcovFileName.c_str());

    std::string gcovFileLine;
    while(std::getline(file_, gcovFileLine))
    {
        Line line;
        line.SetModule(this);
        line.Proccess(gcovFileLine);
        lines.push_back(line);
    }
}

void Module::IncAnalysisLinesCount()
{
    SetAnalysisLinesCount(GetAnalysisLinesCount() + 1);
}

void Module::IncCalledLinesCount()
{
    SetCalledLinesCount(GetCalledLinesCount() + 1);
}

 void Module::GenerateHTMLReport(std::string outputDir)
 {
     if(GetLinesCount1() == 0)
     {
         return;
     }

    HTMLService html;

    html.StartHTMLFile().Paragraph("Статистика по модулю " + GetModuleName()).StartTable().StartTableRow().
        TableColumn("Строка кода").EndTableRow();

    std::string coveragePercent = "";

    for(unsigned int index = 0; index <= GetLinesCount1() - 1; index++)
    {
        Line currentLine = GetLine(index);

        if (currentLine.GetLineStatus() == LineStatus::ignore)
        {
            html.StartTableRow("#d9d9d9");

        }
        else
        {
            if (currentLine.GetLineStatus() == LineStatus::called)
            {
                html.StartTableRow("#b3ffb3");
            }
            else
            {
                html.StartTableRow("#ffb3b3");
            }
        }

        html.TableCell(currentLine.GetSourceLine()).EndTableRow();
    }

    html.EndTable().EndHTMLFile();

    std::ofstream file(outputDir + "\\" + GetModuleName() + ".html");
    file << html.GetHTML();
    file.close();
 }
