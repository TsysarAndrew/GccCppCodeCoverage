#ifndef WINDOWSOS_H
#define WINDOWSOS_H

#include "Global.h"
#include <vector>
#include <fstream>

class WindowsOS
{
    public:
        WindowsOS();
        virtual ~WindowsOS();

        bool CheckDir(const std::string& dirName);
        void CreateDir(const std::string& dirName);
        void DeleteDir(const std::string& dirName);

        bool CheckFile(std::string fileName);
        void RemoveFile(std::string fileName);

        std::string ShortFileName(std::string& fileName);
        std::string FileNameFromGcovFileName(std::string& fileName);
    protected:

    private:
};

#endif // WINDOWSOS_H
