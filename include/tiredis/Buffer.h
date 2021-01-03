#pragma once

#include <cassert>
#include <cstring>
#include <vector>
#include <string>
#include <sys/uio.h>
#include <atomic>

struct BufferSequence
{
    static const std::size_t kMaxIovec = 16;

    iovec buffers[kMaxIovec];

    std::size_t count;

    std::size_t TotalBytes() const 
    {
        assert (count <= kMaxIovec);
        std::size_t nBytes = 0;
        for (std::size_t i = 0; i < count; ++i)
            nBytes += buffers[i].iov_len;

        return nBytes;
    }
};

inline std::size_t RoundUp2Power(std::size_t size)
{
    if (0 == size) return 0;

    std::size_t roundSize = 1;
    while (roundSize < size)
        roundSize <<= 1;

    return roundSize;
}


