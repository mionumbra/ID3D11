#pragma once

#include <common.hpp>
#include <buffers/Buffer.hpp>
#include <d3d11.h>

/// @brief Vertex buffer.
class VertexBuffer final : public Buffer
{
public:
    VertexBuffer(ID3D11Buffer* buffer, size_t stride, size_t numVertices);
    virtual ~VertexBuffer();

    size_t GetSize() const { return Stride * NumVertices; }
    size_t GetStride() const { return Stride; }
    size_t GetNumVertices() const { return NumVertices; }

private:
    size_t Stride = 0;
    size_t NumVertices = 0;
};
