#pragma once

#include <cstddef>

namespace smb
{
class IMemory
{
public:
    virtual ~IMemory() = default;

    [[nodiscard]] virtual std::byte* getData() = 0;
    [[nodiscard]] virtual const std::byte* getData() const = 0;
    [[nodiscard]] virtual size_t size() const = 0;

    IMemory() = default;
    IMemory(const IMemory&) = delete;
    IMemory(IMemory&&) = delete;
    IMemory& operator=(const IMemory&) = delete;
    IMemory& operator=(IMemory&&) = delete;
};
}  // namespace smb
