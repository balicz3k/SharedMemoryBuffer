#include <gtest/gtest.h>

#include <smb/HeapMemory.hpp>

TEST(HeapMemoryTest, CreateAndDestroy)
{
    EXPECT_NO_THROW({ smb::HeapMemory heapMemory("/test_memory", 1024); });
}