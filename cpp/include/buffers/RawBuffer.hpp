#pragma once

#include <common.hpp>
#include <buffers/Buffer.hpp>
#include <views/SRV.hpp>
#include <views/UAV.hpp>
#include <d3d11.h>

/// @brief Raw buffer (unstructured).
class RawBuffer final : public Buffer
{
public:
    RawBuffer(ID3D11Buffer* buffer, size_t size);
    virtual ~RawBuffer();

    size_t GetSize() const { return Size; }

    SRV* CreateSRV() const;
    UAV* CreateUAV() const;

private:
    size_t Size = 0;
};
