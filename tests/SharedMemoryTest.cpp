#include <gtest/gtest.h>

#include <complex>
#include <cstring>
#include <iostream>
#include <memory>
#include <smb/SharedMemory.hpp>

namespace smb
{
class SharedMemoryTest : public ::testing::Test
{
protected:
    void SetUp() override { shm_unlink(shmName.data()); }
    void TearDown() override { shm_unlink(shmName.data()); }
    static constexpr std::string_view shmName = "/test_shm";
};

TEST_F(SharedMemoryTest, basicScenario)
{
    uint64_t sampleData{12345u};
    SharedMemory sharedMemory(shmName.data(), sizeof(sampleData));
    auto schearedData{sharedMemory.getData()};
    const auto schearedDataSize{sharedMemory.size()};

    ASSERT_NE(schearedData, nullptr);
    EXPECT_EQ(schearedDataSize, sizeof(sampleData));

    std::memcpy(schearedData, &sampleData, sizeof(sampleData));
    const auto* fetchedData = std::bit_cast<const uint64_t*>(schearedData);
    EXPECT_EQ(sampleData, *fetchedData);
}
}  // namespace smb