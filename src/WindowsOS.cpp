#include "WindowsOS.h"
#include "windows.h"
#include "dirent.h"
#include <iostream>
#include <stdio.h>
#include <io.h>

WindowsOS::WindowsOS()
{
    //ctor
}

WindowsOS::~WindowsOS()
{
    //dtor
}

bool WindowsOS::CheckDir(const std::string& dirName)
{
    DWORD fileType = GetFileAttributesA(dirName.c_str());
    if (fileType == INVALID_FILE_ATTRIBUTES)
    {
       return false;
    }

    if (fileType & FILE_ATTRIBUTE_DIRECTORY)
    {
       return true;
    }

    return false;
}


void WindowsOS::CreateDir(const std::string& dirName)
{
    CreateDirectory(dirName.c_str(), NULL);
}

void WindowsOS::DeleteDir(const std::string& dirName)
{
    RemoveDirectory(dirName.c_str());
}

bool WindowsOS::CheckFile(std::string fileName)
{
    return access(fileName.c_str(), 0) != -1;
}

std::string WindowsOS::ShortFileName(std::string& fileName)
{
    size_t lastSlashFound = fileName.find_last_of("/\\");

    return fileName.substr(lastSlashFound + 1);
}

std::string WindowsOS::FileNameFromGcovFileName(std::string& fileName)
{
    std::string result = fileName;

    size_t start_pos = result.find("~");
    if(start_pos != std::string::npos)
    {
      result.replace(start_pos, 1, ":");
    }

    start_pos = result.find("#");
    while(start_pos != std::string::npos)
    {
      result.replace(start_pos, 1, "\\");
      start_pos = result.find("#");
    }

    size_t lastDot = result.find_last_of("/.");

    return result.substr(0, lastDot);
}

void WindowsOS::RemoveFile(std::string fileName)
{
    remove(fileName.c_str());
}
