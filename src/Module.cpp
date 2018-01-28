#include "Module.h"
#include <fstream>
#include <iostream>
#include "WindowsOS.h"
#include "HTMLService.h"

Module::Module()
{
    SetCalledLinesCount(0);
    SetAnalysisLinesCount(0);
    macroses = NULL;
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
    if(!os.CheckFile(gcovFileName))
    {
        //std::cerr << "file" << gcovFileName << " not found" << std::endl;
        return;
    }
    else
    {
        //std::cerr << "file" << gcovFileName << " found" << std::endl;
    }

    std::string moduleName = os.ShortFileName(gcovFileName);
    moduleName = os.FileNameFromGcovFileName(moduleName);
    moduleName = os.ShortFileName(moduleName);
    SetModuleName(moduleName);

    std::ifstream file(gcovFileName);
    //std::cerr << "std::ifstream file(gcovFileName) - " << gcovFileName << std::endl;


    std::string gcovFileLine;
    while(std::getline(file, gcovFileLine))
    {
        //std::cerr << "getline - " << gcovFileLine << std::endl;
        Line line;
        line.SetModule(this);
        line.SetMacroses(macroses);
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

void Module::SetMacroses(std::vector<std::string>* macroses)
{
    this->macroses = macroses;
}

 void Module::GenerateHTMLReport(std::string outputDir)
 {
    HTMLService html;

    html.StartHTMLFile().Paragraph("Статистика по модулю " + GetModuleName()).StartTable().StartTableRow().
        TableColumn("Строка кода").EndTableRow();

    std::string coveragePercent = "";
    for(int index = 0; index <= GetLinesCount1() - 1; index++)
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
