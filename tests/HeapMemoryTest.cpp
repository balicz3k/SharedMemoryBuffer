#include <gtest/gtest.h>

#include <smb/HeapMemory.hpp>

namespace smb
{
TEST(HeapMemoryTest, CreateAndDestroy)
{
    EXPECT_NO_THROW({ HeapMemory heapMemory("/test_memory", 1024); });
}
}  // namespace smb
