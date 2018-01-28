#ifndef LINE_H
#define LINE_H

#include "Global.h"
#include <vector>
#include "Module.h"

struct WordData{
    std::string word;
    std::string separator;
};

enum LineStatus{ignore, called, nonCalled};

class Module;
class Line
{
    public:

// NOTE (������#1#): ���������� ������ ��� ����������� �������� ����. � ������ ������ ��������� ������ ����� SetModule ��� ���� module. ����� ���� ����� ����� ������� ����� �������� ������ FRIEND_TEST � �������� �������
    //friend Module;
        Line();
        virtual ~Line();

        void Proccess(std::string &fileLine);
        WordData ReadWord(std::string &fileLine);
        std::string GetSourceLine();

        void SetMacroses(std::vector<std::string>* macroses);

        std::string LeftTrim(std::string value);

        GETSET(bool, isMethod, IsMethod);
        GETSET(bool, methodWasCalled, MethodWasCalled);
        GETSET(bool, lineWasCalled, LineWasCalled);
        GETSET(Module*, module, Module);
        GETSET(LineStatus, lineStatus, LineStatus);
    protected:

    private:
        std::vector<std::string> separators;
        std::vector<WordData> words;
        std::string sourceLine;
        std::vector<std::string>* macroses;
};

#endif // LINE_H
