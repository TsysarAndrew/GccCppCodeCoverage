#include <iostream>

#include "GlobalUnitTest.h"

using namespace std;

int main(int argc, char** argv)
{
    //--gtest_filter=LineClass.GetClassMethodName2Test
    testing::InitGoogleTest(&argc, argv);

    RUN_ALL_TESTS();
}
