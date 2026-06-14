#pragma once

#include <common.hpp>
#include <buffers/Buffer.hpp>
#include <d3d11.h>

/// @brief Index buffer.
class IndexBuffer final : public Buffer
{
public:
    IndexBuffer(ID3D11Buffer* buffer, size_t indexSize, size_t numIndices);
    virtual ~IndexBuffer();

    size_t GetSize() const { return IndexSize * NumIndices; }
    size_t GetIndexSize() const { return IndexSize; }
    size_t GetNumIndices() const { return NumIndices; }

private:
    size_t IndexSize = 0;   // 每个索引的字节数 (2 或 4)
    size_t NumIndices = 0;  // 索引数量
};
