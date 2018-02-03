#ifndef GLOBALUNITTEST_H_INCLUDED
#define GLOBALUNITTEST_H_INCLUDED

#include "windows.h"
#include "gtest/gtest.h"

#define TEST_PROPERTY(TestGroupName, ClassName, PropertyName, TestValue) \
    TEST(TestGroupName, PropertyName##PropertyTest)\
    {\
        ClassName classInstance;\
        classInstance.Set##PropertyName(TestValue);\
        ASSERT_EQ(classInstance.Get##PropertyName(), TestValue);\
    }

#endif // GLOBALUNITTEST_H_INCLUDED


std::string GetAppDir();
