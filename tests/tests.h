#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

extern "C"
{
#include "../src/server.h"
}

TEST(Finder, Test_1)
{
    char *request = NULL;
    request = (char *)malloc(sizeof(char) * 256);
    memccpy(request, "/echo/test", sizeof(char), 12);

    char *ptr = finder((char *)"/echo/", request);

    EXPECT_TRUE(ptr != nullptr);
}

TEST(Finder,Test_2)
{
    char *request = NULL;
    request = (char *)malloc(sizeof(char) * 256);
    memccpy(request, "/echo/test", sizeof(char), 12);

    char *ptr = finder((char *)"/echo/", request);

    ASSERT_EQ(strlen(ptr) , 4);
}

TEST(Finder, Test_3)
{
    char *request = NULL;
    request = (char *)malloc(sizeof(char) * 256);
    memccpy(request, (char *) "/ec1ho/123", sizeof(char), 11);

    char *ptr = finder((char *) "/echo/", request);

    ASSERT_EQ(ptr , nullptr);
}

TEST(OpenFile, Test_1)
{
    char *buffer = (char *)malloc(sizeof(char) * 256);
    buffer=((char *)"/mnt/",(char *)"THERE_IS_NOTHING");
    if (*buffer=='\0')
    {
        SUCCEED();
    }

}
