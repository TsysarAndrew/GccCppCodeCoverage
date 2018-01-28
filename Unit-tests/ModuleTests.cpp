#include "GlobalUnitTest.h"
#include "Module.h"
#include "Line.h"
#include "WindowsOS.h"
#include <stdio.h>

TEST_PROPERTY(ModuleClass, Module, AnalysisLinesCount, 4);
TEST_PROPERTY(ModuleClass, Module, CalledLinesCount, 6);

TEST(ModuleClass, Line_SetModuleTest)
{
    Module module;

    Line line;
    line.SetModule(&module);

    ASSERT_EQ(line.GetModule(), &module);
}

// NOTE (Андрей#1#): Дубль с методом в модуле WindowsOsTests
std::string GetAppDir1()
{
    char result[MAX_PATH];
    std::string appPath(result, GetModuleFileNameA(NULL, result, MAX_PATH));
    size_t lastSlashFound = appPath.find_last_of("/\\");

    return appPath.substr(0, lastSlashFound);
}

TEST(ModuleClass, ProccessTest)
{

    WindowsOS os;

    std::string subDir = GetAppDir1() + "\\SubDirModuleClass";
    os.CreateDir(subDir);

    std::string fileName = subDir + "\\file.gcov";
    std::ofstream file(fileName);
    file << "    23:   17:void WindowsService::RunApplication(wxString path, bool async)\n" ;
    file << "    #####:   17:void WindowsService::RunApplication1(wxString path, bool async)\n" ;
    file << "    -:   17:test";
    file.close();

    Module module;
    module.Proccess(fileName);
    ASSERT_EQ(module.GetAnalysisLinesCount(), 2);
    ASSERT_EQ(module.GetCalledLinesCount(), 1);

    os.RemoveFile(fileName);
    os.DeleteDir(subDir);
}
