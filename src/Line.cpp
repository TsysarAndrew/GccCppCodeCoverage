#include "Line.h"
#include "iostream"
#include <algorithm>

Line::Line()
{
    separators.push_back("::");
    separators.push_back("//");
    separators.push_back(":");
    separators.push_back(" ");
    separators.push_back("(");
    separators.push_back(")");

    module = NULL;

    macroses = NULL;
}

Line::~Line()
{
    //dtor
}


void Line::Proccess(std::string &fileLine)
{
    SetIsMethod(false);
    SetMethodWasCalled(false);

    sourceLine = fileLine;

    if((fileLine == "") /*|| (fileLine.find(".") != std::string::npos)*/)
    {
        return;
    }

    while (fileLine != "")
    {
        WordData wordData = ReadWord(fileLine);
        words.push_back(wordData);
    }


    //std::cerr << "sourceLine = " << sourceLine << std::endl;
    SetLineWasCalled(false);
    SetLineStatus(LineStatus::ignore);
    if (words[0].word.find("#####") == std::string::npos)
    {
        //std::cerr << "not find words[0].word.find(\"#####\")" << std::endl;
        if (words[0].word.find("-") == std::string::npos)
        {
            //std::cerr << "not find words[0].word.find(\"-\")" << std::endl;
            SetLineWasCalled(true);
            SetLineStatus(LineStatus::called);

            if(module != NULL)
            {
                module->IncCalledLinesCount();
                module->IncAnalysisLinesCount();
            }
        }
    }
    else
    {
        //std::cerr << "find words[0].word.find(\"#####\")" << std::endl;
        SetLineStatus(LineStatus::nonCalled);
        if(module != NULL)
        {
            module->IncAnalysisLinesCount();
        }
    }
}


WordData Line::ReadWord(std::string &fileLine)
{
    WordData result;

    size_t minSeparatorPosition = 0;
    std::string currentSeparator = "";
    size_t separatorPosition = 0;
    bool wordWasFinded = false;
    for (std::vector<std::string>::iterator it = separators.begin(); it != separators.end(); ++it)
    {
        //std::cerr << "___minSeparatorPosition " << minSeparatorPosition << std::endl;
        //std::cerr << "___separatorPosition " << minSeparatorPosition << std::endl;

        separatorPosition = fileLine.find(*it);
        if((separatorPosition != std::string::npos) && (separatorPosition != 0))
        {

            wordWasFinded = true;


            if(minSeparatorPosition == 0)
            {
                minSeparatorPosition = separatorPosition;
                currentSeparator = *it;
            }
            else
            {
                if(separatorPosition < minSeparatorPosition)
                {
                    //std::cerr << "separatorPosition < minSeparatorPosition "<<separatorPosition<< "<" << minSeparatorPosition << std::endl;
                    minSeparatorPosition = separatorPosition;
                    currentSeparator = *it;
                }
            }
        }
    }

    //std::cerr << "___result__minSeparatorPosition " << minSeparatorPosition << std::endl;

    if(!wordWasFinded)
    {
        result.word = fileLine;
        fileLine.clear();
    }
    else
    {
        result.word = fileLine.substr(0, minSeparatorPosition);
        result.separator = currentSeparator;
        fileLine = fileLine.substr(minSeparatorPosition + result.separator.length(), fileLine.length() - minSeparatorPosition - 1);
    }

//        std::cerr << "wordData.word " <<  result.word << std::endl;
//        std::cerr << "wordData.separator " <<  result.separator << std::endl;
//        std::cerr << "fileLine " <<  fileLine << std::endl;
//        std::cerr << "-------------------" << std::endl;

    if(result.separator == "")
    {
        result.separator = result.word;
    }

    return result;
}

std::string Line::GetSourceLine()
{
    return sourceLine;
}

void Line::SetMacroses(std::vector<std::string>* macroses)
{
    this->macroses = macroses;
}


std::string Line::LeftTrim(std::string value)
{
    std::string result = value;
    size_t startpos = result.find_first_not_of(" \t");
    if(startpos != std::string::npos)
    {
        result = result.substr(startpos);
    }

    return result;
}
