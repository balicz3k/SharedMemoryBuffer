#pragma once

#include <string>
#include <vector>

#include "IMemory.hpp"

namespace smb
{
class HeapMemory : public IMemory
{
public:
    HeapMemory([[maybe_unused]] const std::string name, const size_t bufferSize)
        : bufferData(bufferSize), bufferName(std::move(name))
    {
    }

    [[nodiscard]] const std::byte* getData() const final { return &bufferData[0]; };
    [[nodiscard]] std::byte* getData() final { return &bufferData[0]; };
    [[nodiscard]] size_t size() const final { return bufferData.size(); };

    HeapMemory() = delete;
    HeapMemory(HeapMemory& other) = delete;
    HeapMemory(HeapMemory&& other) = delete;
    HeapMemory& operator=(const HeapMemory& other) = delete;
    HeapMemory& operator=(HeapMemory&& other) = delete;
    ~HeapMemory() final = default;

private:
    std::string bufferName{};
    std::vector<std::byte> bufferData{};
};
}  // namespace smb
