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

    if(fileLine == "")
    {
        return;
    }

    while (fileLine != "")
    {
        WordData wordData = ReadWord(fileLine);
        words.push_back(wordData);
    }

    SetLineWasCalled(false);
    SetLineStatus(LineStatus::ignore);
    if (words[0].word.find("#####") == std::string::npos)
    {
        if (words[0].word.find("-") == std::string::npos)
        {
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
                    minSeparatorPosition = separatorPosition;
                    currentSeparator = *it;
                }
            }
        }
    }

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
