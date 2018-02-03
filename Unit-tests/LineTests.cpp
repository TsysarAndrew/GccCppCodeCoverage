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
