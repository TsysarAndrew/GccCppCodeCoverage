
#include "GlobalUnitTest.h"
#include "WindowsOS.h"
#include <vector>
#include <iostream>
#include <stdio.h>


TEST(WindowsOSClass, TestGetAppDir)
{
    ASSERT_EQ(GetAppDir(), "C:\\Work\\ООО Надежное ПО\\Проект Запись видео\\GccCppCodeCovering\\Unit-tests\\bin\\Debug");
}

TEST(WindowsOSClass, TestCheckDir)
{
    WindowsOS os;
    ASSERT_TRUE(os.CheckDir(GetAppDir()));
}

TEST(WindowsOSClass, TestCreateAndDeleteDir)
{
    WindowsOS os;
    std::string subDirName = GetAppDir() + "\\SubDir";

    os.CreateDir(subDirName);
    ASSERT_TRUE(os.CheckDir(subDirName));

    os.DeleteDir(subDirName);
    ASSERT_FALSE(os.CheckDir(subDirName));
}

void CreateFile(std::string fileName)
{
    std::ofstream file(fileName);
    file << "test";
    file.close();
}

TEST(WindowsOSClass, TestCreateAndCheckAndDeleteFile)
{
    WindowsOS os;
    std::string fileName = GetAppDir() + "\\test.log";

    CreateFile(fileName);
    ASSERT_TRUE(os.CheckFile(fileName));

    //std::cerr << "fileName" << fileName << std::endl;
    os.RemoveFile(fileName);
    ASSERT_FALSE(os.CheckFile(fileName));
}

TEST(WindowsOSClass, TestShortFileName)
{
    std::string fullPath = "C:\\Dir01\\SubDir02\\SubDir03\\test.txt";
    std::string shortFileName = "test.txt";

    WindowsOS os;
    ASSERT_EQ(os.ShortFileName(fullPath), shortFileName);
}

TEST(WindowsOSClass, TestFileNameFromGcovFileName)
{
    std::string gcovFileName = "C~#Work#ООО Надежное ПО#Проект Запись видео#Source#VideoRecApp.cpp.gcov";
    std::string normalFileName = "C:\\Work\\ООО Надежное ПО\\Проект Запись видео\\Source\\VideoRecApp.cpp";

    WindowsOS os;
    ASSERT_EQ(os.FileNameFromGcovFileName(gcovFileName), normalFileName);
}
