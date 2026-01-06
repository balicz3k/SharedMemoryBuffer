#pragma once

#include <fcntl.h>
#include <sys/mman.h>

#include <atomic>
#include <print>
#include <string>
#include <system_error>

namespace smb
{
static constexpr uint64_t SIGNATURE{0x1234ABCD};

class SharedMemory
{
    struct ControlBlock
    {
        uint64_t signature{SIGNATURE};
        std::atomic<uint16_t> refCnt;
    };

public:
    SharedMemory(std::string name, size_t dataSize)
        : bufferName(std::move(name)), dataBufferSize(dataSize), totalBufferSize(dataBufferSize + sizeof(ControlBlock))
    {
        fileDescriptor = shm_open(bufferName.c_str(), O_CREAT | O_EXCL | O_RDWR, 0666);
        bool isNewBuffer{false};

        if (fileDescriptor >= 0)
        {
            if (ftruncate(fileDescriptor, static_cast<long>(totalBufferSize)) == -1)
            {
                throw std::system_error(errno, std::generic_category());
            }
            isNewBuffer = true;
        }
        else
        {
            fileDescriptor = shm_open(name.c_str(), O_RDWR, 0666);
            if (fileDescriptor == -1)
            {
                throw std::system_error(errno, std::generic_category());
            }
        }

        bufferPtr = mmap(nullptr, totalBufferSize, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0);
        if (bufferPtr == MAP_FAILED) throw std::system_error(errno, std::generic_category());
        dataPtr = std::next(static_cast<std::byte*>(bufferPtr), sizeof(ControlBlock));

        auto* controlBlock = static_cast<ControlBlock*>(bufferPtr);

        if (isNewBuffer)
        {
            new (&controlBlock->refCnt) std::atomic<uint16_t>(1u);
        }
        else
        {
            if (controlBlock->signature not_eq SIGNATURE)
            {
                munmap(bufferPtr, totalBufferSize);
                close(fileDescriptor);
                throw std::runtime_error("SHM Name Collision: Memory exists but signature mismatch!");
            }
            controlBlock->refCnt.fetch_add(1u);
        }
    }

    [[nodiscard]] std::byte* getData() const { return dataPtr; }
    [[nodiscard]] size_t size() const { return dataBufferSize; };

    ~SharedMemory()
    {
        auto* controlBlock{static_cast<ControlBlock*>(bufferPtr)};
        controlBlock->refCnt.fetch_sub(1);
        if (controlBlock->refCnt == 0u)
        {
            shm_unlink(bufferName.c_str());
        }

        munmap(bufferPtr, totalBufferSize);
        if (fileDescriptor != -1)
        {
            close(fileDescriptor);
        };
    }
    SharedMemory() = delete;
    SharedMemory(SharedMemory& other) = delete;
    SharedMemory(SharedMemory&& other) = delete;
    SharedMemory& operator=(const SharedMemory& other) = delete;
    SharedMemory& operator=(SharedMemory&& other) = delete;

private:
    std::string bufferName{};
    int fileDescriptor{-1};
    size_t dataBufferSize{};
    size_t totalBufferSize{};
    void* bufferPtr{nullptr};
    std::byte* dataPtr{nullptr};
};
}  // namespace smb
