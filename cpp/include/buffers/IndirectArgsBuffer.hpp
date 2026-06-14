#pragma once

#include <common.hpp>
#include <buffers/Buffer.hpp>
#include <d3d11.h>

/// @brief Indirect arguments buffer.
class IndirectArgsBuffer final : public Buffer
{
public:
    IndirectArgsBuffer(ID3D11Buffer* buffer, size_t size);
    virtual ~IndirectArgsBuffer();

    size_t GetSize() const { return Size; }

private:
    size_t Size = 0;
};
