#pragma once

#include <string>
#include <vector>

namespace smb
{
class HeapMemory
{
public:
    HeapMemory([[maybe_unused]] std::string name, size_t bufferSize)
        : bufferData(bufferSize), bufferName(std::move(name))
    {
    }

    [[nodiscard]] size_t size() const { return bufferData.size(); };
    [[nodiscard]] std::byte* getData() { return &bufferData[0]; };

    HeapMemory() = delete;
    HeapMemory(HeapMemory& other) = delete;
    HeapMemory(HeapMemory&& other) = delete;
    HeapMemory& operator=(const HeapMemory& other) = delete;
    HeapMemory& operator=(HeapMemory&& other) = delete;
    ~HeapMemory() = default;

private:
    std::string bufferName{};
    std::vector<std::byte> bufferData{};
};
}  // namespace smb
