#pragma once

#include <gmock/gmock.h>

#include <smb/IMemory.hpp>

namespace smb
{
class MockMemory : public smb::IMemory
{
public:
    MOCK_METHOD(std::byte*, getData, (), (override));
    MOCK_METHOD(const std::byte*, getData, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
};
}  // namespace smb
