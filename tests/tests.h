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

TEST(Finder, Test_2)
{
    char *request = NULL;
    request = (char *)malloc(sizeof(char) * 256);
    memccpy(request, "/echo/test", sizeof(char), 12);

    char *ptr = finder((char *)"/echo/", request);

    ASSERT_EQ(strlen(ptr), 4);
}

TEST(Finder, Test_3)
{
    char *request = NULL;
    request = (char *)malloc(sizeof(char) * 256);
    memccpy(request, (char *)"/ec1ho/123", sizeof(char), 11);

    char *ptr = finder((char *)"/echo/", request);

    ASSERT_EQ(ptr, nullptr);
}

TEST(check_dir, Test_1)
{

    char *argv_[] = {"./server", "--directory", "/tmp"};
    char *buffer = check_dir_option(3, argv_);
    ASSERT_EQ(buffer, "/tmp");
}

TEST(check_dir, Test_2)
{

    char *argv_[] = {(char *) "./server_fake",(char *) "--directory",(char *)"./NOTHING_DIR"};
    char *buffer = check_dir_option(2, argv_);
    ASSERT_EQ(buffer, (char *)'\0');
}
