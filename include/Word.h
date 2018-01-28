#ifndef WORD_H
#define WORD_H

#include "Global.h"

class Word
{
    public:
        Word();
        virtual ~Word();

        GETSET(std::string, word, Word);
        GETSET(std::string, separator, Separator);
    protected:

    private:
};

#endif // WORD_H
