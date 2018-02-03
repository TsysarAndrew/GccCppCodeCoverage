#include "GlobalUnitTest.h"

std::string GetAppDir()
{
    char result[MAX_PATH];
    std::string appPath(result, GetModuleFileNameA(NULL, result, MAX_PATH));
    size_t lastSlashFound = appPath.find_last_of("/\\");

    return appPath.substr(0, lastSlashFound);
}
