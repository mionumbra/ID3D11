#pragma once

#include <common.hpp>
#include <buffers/Buffer.hpp>
#include <d3d11.h>

/// @brief Upload buffer (CPU → GPU staging).
class UploadBuffer final : public Buffer
{
public:
    UploadBuffer(ID3D11Buffer* buffer, size_t size);
    virtual ~UploadBuffer();

    size_t GetSize() const { return Size; }

    bool IsMapped() const { return Mapped; }
    bool Map();
    void* GetMappedData() const { return MapData.pData; }
    bool Unmap();

private:
    size_t Size = 0;
    D3D11_MAPPED_SUBRESOURCE MapData{};
    bool Mapped = false;
};
