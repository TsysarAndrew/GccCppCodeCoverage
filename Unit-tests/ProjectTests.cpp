#include "GlobalUnitTest.h"
#include "Project.h"
#include "WindowsOS.h"

TEST_PROPERTY(ProjectClass, Project, InputDir, "Test input dir");
TEST_PROPERTY(ProjectClass, Project, OutputDir, "Test output dir");

TEST(ProjectClass, TestReadingAppParams)
{
    int argc = 9;
    char** argv = (char**) malloc(argc * sizeof(char*));

    char* param1 = "sad";
    argv[0] = param1;

    char* param2 = "ggg";
    argv[1] = param2;

    char* param3 = "ccc";
    argv[2] = param3;

    char* param4 = "-inputDir";
    argv[3] = param4;

    char* param5 = "Test input dir";
    argv[4] = param5;

    char* param6 = "-outputDir";
    argv[5] = param6;

    char* param7 = "Test output dir";
    argv[6] = param7;

    char* param8 = "-macrosesList";
    argv[7] = param8;

    char* param9 = "macroses.txt";
    argv[8] = param9;

    Project* project = new Project();
    project->ReadAppParams(argc, argv);

    ASSERT_EQ(project->GetInputDir(), "Test input dir");
    ASSERT_EQ(project->GetOutputDir(), "Test output dir");
}

TEST(ProjectClass, TestReadingAppParamsShortNames)
{
    int argc = 9;
    char** argv = (char**) malloc(argc * sizeof(char*));

    char* param1 = "sad";
    argv[0] = param1;

    char* param2 = "ggg";
    argv[1] = param2;

    char* param3 = "ccc";
    argv[2] = param3;

    char* param4 = "-i";
    argv[3] = param4;

    char* param5 = "Test input dir";
    argv[4] = param5;

    char* param6 = "-o";
    argv[5] = param6;

    char* param7 = "Test output dir";
    argv[6] = param7;

    char* param8 = "-m";
    argv[7] = param8;

    char* param9 = "macroses.txt";
    argv[8] = param9;

    Project* project = new Project();
    project->ReadAppParams(argc, argv);

    ASSERT_EQ(project->GetInputDir(), "Test input dir");
    ASSERT_EQ(project->GetOutputDir(), "Test output dir");
}


TEST(ProjectClass, TestReadingAppParamsEmptyParams)
{
    int argc = 1;
    char** argv = (char**) malloc(1 * sizeof(char*));

    char* param1 = "sad";
    argv[0] = param1;


    Project* project = new Project();
    project->ReadAppParams(argc, argv);

    ASSERT_EQ(project->GetInputDir(), "");
    ASSERT_EQ(project->GetOutputDir(), "");
}

TEST(ProjectClass, TestProccess)
{
    WindowsOS os;

    std::string subDir = GetAppDir() + "\\SubDirProjectClass";
    os.CreateDir(subDir);

    std::string fileName1 = subDir + "\\file.gcov";
    std::ofstream file(fileName1);
    file << "    23:   17:void WindowsService::RunApplication(wxString path, bool async)\n" ;
    file << "    23:   17:test";
    file.close();

    std::string fileName2 = subDir + "\\file2.gcov";
    std::ofstream file2(fileName2);
    file2 << "    23:   17:test\n" ;
    file2 << "    23:   17:test";
    file2.close();

    Project project;
    project.SetInputDir(subDir);
    project.Proccess();

    ASSERT_EQ(project.GetModulesCount(), 2);

    os.RemoveFile(fileName1);
    os.RemoveFile(fileName2);
    os.DeleteDir(subDir);

}

TEST(ProjectClass, TestCreateOutPutFolder)
{
    std::string subDir = GetAppDir() + "\\SubDirProjectClassTestCreateOutPutFolder\\Sub\\Sub\\HTML";

    WindowsOS os;
    Project project;
    project.SetOutputDir(subDir);
    project.CreateOutPutFolder();

    ASSERT_TRUE(os.CheckDir(GetAppDir() + "\\SubDirProjectClassTestCreateOutPutFolder\\Sub\\Sub\\HTML"));
    os.DeleteDir(GetAppDir() + "\\SubDirProjectClassTestCreateOutPutFolder\\Sub\\Sub\\HTML");

    ASSERT_TRUE(os.CheckDir(GetAppDir() + "\\SubDirProjectClassTestCreateOutPutFolder\\Sub\\Sub"));
    os.DeleteDir(GetAppDir() + "\\SubDirProjectClassTestCreateOutPutFolder\\Sub\\Sub");

    ASSERT_TRUE(os.CheckDir(GetAppDir() + "\\SubDirProjectClassTestCreateOutPutFolder\\Sub"));
    os.DeleteDir(GetAppDir() + "\\SubDirProjectClassTestCreateOutPutFolder\\Sub");

    ASSERT_TRUE(os.CheckDir(GetAppDir() + "\\SubDirProjectClassTestCreateOutPutFolder"));
    os.DeleteDir(GetAppDir() + "\\SubDirProjectClassTestCreateOutPutFolder");
}


TEST(ProjectClass, TestCoveragePercent)
{
    Project project;
    ASSERT_EQ(project.CoveragePercent(3, 4), "75");
    ASSERT_EQ(project.CoveragePercent(0, 22), "0");
    ASSERT_EQ(project.CoveragePercent(0, 0), "-");
}
