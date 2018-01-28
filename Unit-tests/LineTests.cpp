#include "GlobalUnitTest.h"
#include "Line.h"

TEST_PROPERTY(LineClass, Line, IsMethod, true);
TEST_PROPERTY(LineClass, Line, MethodWasCalled, true);
TEST_PROPERTY(LineClass, Line, LineWasCalled, true);
TEST_PROPERTY(LineClass, Line, LineStatus, LineStatus::nonCalled);

TEST(LineClass, ReadWordTest)
{
    Line line;
    std::string gcovLine = "    23:   17:void WindowsService::RunApplication(wxString path, bool async)";
    WordData wordData = line.ReadWord(gcovLine);

    ASSERT_EQ(wordData.word, "    23");
    ASSERT_EQ(wordData.separator, ":");
    ASSERT_EQ(gcovLine, "   17:void WindowsService::RunApplication(wxString path, bool async)");

    wordData = line.ReadWord(gcovLine);
    ASSERT_EQ(wordData.word, "   17");
    ASSERT_EQ(wordData.separator, ":");
    ASSERT_EQ(gcovLine, "void WindowsService::RunApplication(wxString path, bool async)");

    wordData = line.ReadWord(gcovLine);
    ASSERT_EQ(wordData.word, "void");
    ASSERT_EQ(wordData.separator, " ");
    ASSERT_EQ(gcovLine, "WindowsService::RunApplication(wxString path, bool async)");

    wordData = line.ReadWord(gcovLine);
    ASSERT_EQ(wordData.word, "WindowsService");
    ASSERT_EQ(wordData.separator, "::");
    ASSERT_EQ(gcovLine, "RunApplication(wxString path, bool async)");

    wordData = line.ReadWord(gcovLine);
    ASSERT_EQ(wordData.word, "RunApplication");
    ASSERT_EQ(wordData.separator, "(");
    ASSERT_EQ(gcovLine, "wxString path, bool async)");

    wordData = line.ReadWord(gcovLine);
    ASSERT_EQ(wordData.word, "wxString");
    ASSERT_EQ(wordData.separator, " ");
    ASSERT_EQ(gcovLine, "path, bool async)");

    wordData = line.ReadWord(gcovLine);
    ASSERT_EQ(wordData.word, "path,");
    ASSERT_EQ(wordData.separator, " ");
    ASSERT_EQ(gcovLine, "bool async)");

    wordData = line.ReadWord(gcovLine);
    ASSERT_EQ(wordData.word, "bool");
    ASSERT_EQ(wordData.separator, " ");
    ASSERT_EQ(gcovLine, "async)");

    wordData = line.ReadWord(gcovLine);
    ASSERT_EQ(wordData.word, "async");
    ASSERT_EQ(wordData.separator, ")");
    ASSERT_EQ(gcovLine, "");
}

//TEST(LineClass, GetClassMethodNameTest)
//{
//    Line line;
//    std::string gcovLine = "    23:   17:void WindowsService::RunApplication(wxString path, bool async)";
//    line.Proccess(gcovLine);
//
//    std::string methodName = "WindowsService::RunApplication";
//    ASSERT_EQ(line.GetMethodName(), methodName);
//}
//
//TEST(LineClass, GetClassMethodName2Test)
//{
//    Line line;
//    std::string gcovLine = "    23:   17:void WindowsService::RunApplication()";
//    line.Proccess(gcovLine);
//
//    //std::string methodName = "WindowsService::RunApplication";
//    ASSERT_EQ(line.GetMethodName(), "WindowsService::RunApplication");
//}
//
//TEST(LineClass, GetGlobalMethodNameTest)
//{
//    Line line;
//    std::string gcovLine = "    23:   17:void RunApplication(wxString path, bool async)";
//    line.Proccess(gcovLine);
//
//    std::string methodName = "RunApplication";
//    ASSERT_EQ(line.GetMethodName(), methodName);
//}
//
//TEST(LineClass, ProccessCalledClassMethodString)
//{
//    Line line;
//    std::string gcovLine = "    23:   17:void WindowsService::RunApplication(wxString path, bool async)";
//    line.Proccess(gcovLine);
//
//    ASSERT_TRUE(line.GetIsMethod());
//    ASSERT_TRUE(line.GetMethodWasCalled());
//}
//
//TEST(LineClass, ProccessNonCalledClassMethodString)
//{
//    Line line;
//    std::string gcovLine = "    #####:   17:void WindowsService::RunApplication(wxString path, bool async)";
//    line.Proccess(gcovLine);
//
//    ASSERT_EQ(line.GetMethodName(), "WindowsService::RunApplication");
//    ASSERT_TRUE(line.GetIsMethod());
//    ASSERT_FALSE(line.GetMethodWasCalled());
//}
//
//TEST(LineClass, ProccessCalledGlobalMethodString)
//{
//    Line line;
//    std::string gcovLine = "    23:   17:void RunApplication(wxString path, bool async)";
//    line.Proccess(gcovLine);
//
//    ASSERT_TRUE(line.GetIsMethod());
//    ASSERT_TRUE(line.GetMethodWasCalled());
//}
//
//TEST(LineClass, ProccessNonCalledGlobalMethodString)
//{
//    Line line;
//    std::string gcovLine = "    #####:   17:void RunApplication(wxString path, bool async)";
//    line.Proccess(gcovLine);
//
//    ASSERT_TRUE(line.GetIsMethod());
//    ASSERT_FALSE(line.GetMethodWasCalled());
//}
//
//TEST(LineClass, ProccessCommentedClassMethodString)
//{
//    Line line;
//    std::string gcovLine = "    -:   17://void WindowsService::RunApplication(wxString path, bool async)";
//    line.Proccess(gcovLine);
//
//    ASSERT_FALSE(line.GetIsMethod());
//}
//
//TEST(LineClass, ProccessCommentedGlobalMethodString)
//{
//    Line line;
//    std::string gcovLine = "    -:   17://void RunApplication(wxString path, bool async)";
//    line.Proccess(gcovLine);
//
//    ASSERT_FALSE(line.GetIsMethod());
//}
//
//
//TEST(LineClass, ProccessCaledMacros)
//{
//    std::vector<std::string> macroses;
//    macroses.push_back("GETSET");
//
//    Line line;
//    line.SetMacroses(&macroses);
//    std::string gcovLine = "12:   36:        GETSET(wxString, projectPath, ProjectPath);";
//    line.Proccess(gcovLine);
//
//    ASSERT_TRUE(line.GetIsMethod());
//    ASSERT_TRUE(line.GetMethodWasCalled());
//}
//
//TEST(LineClass, ProccessNonCaledMacros)
//{
//    std::vector<std::string> macroses;
//    macroses.push_back("GETSET");
//
//    Line line;
//    line.SetMacroses(&macroses);
//    std::string gcovLine = "#####:   36:        GETSET(wxString, projectPath, ProjectPath);";
//    line.Proccess(gcovLine);
//
//    ASSERT_TRUE(line.GetIsMethod());
//    ASSERT_FALSE(line.GetMethodWasCalled());
//}

TEST(LineClass, LeftTrim)
{
    Line line;

    ASSERT_EQ(line.LeftTrim("  \t\t\t   asda  \t b"), "asda  \t b");
}


TEST(LineClass, IgnoreLineStatus)
{
    Line line;
    std::string gcovLine = " -: 0:Source:C:/Work/ООО Надежное ПО/Проект Запись видео/Source/src/ScriptCommandSetCursorPosition.cpp";
    line.Proccess(gcovLine);

    ASSERT_EQ(line.GetLineStatus(), LineStatus::ignore);
}

TEST(LineClass, CalledLineStatus)
{
    Line line;
    std::string gcovLine = "    1:   17:void WindowsService::RunApplication(wxString path, bool async)";
    line.Proccess(gcovLine);

    ASSERT_EQ(line.GetLineStatus(), LineStatus::called);
}

TEST(LineClass, NonCalledLineStatus)
{
    Line line;
    std::string gcovLine = "    #####:   17:void WindowsService::RunApplication(wxString path, bool async)";
    line.Proccess(gcovLine);

    ASSERT_EQ(line.GetLineStatus(), LineStatus::nonCalled);
}
