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

// NOTE (Андрей#1#): Необходимо решить как тестировать закрытые поля. В даннам случае необходим только метод SetModule для поля module. Может быть можно будет сделать через фейковый макрос FRIEND_TEST в основном проекте
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
};

#endif // LINE_H
