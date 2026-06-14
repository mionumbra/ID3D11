#pragma once

#include <common.hpp>
#include <textures/Texture.hpp>
#include <views/SRV.hpp>
#include <views/UAV.hpp>
#include <d3d11.h>

/// @brief 3D texture wrapper.
class Texture3D final : public Texture
{
public:
    Texture3D(ID3D11Texture3D* texture, size_t width, size_t height, size_t depth);
    virtual ~Texture3D();

    ID3D11Texture3D* GetTexture() const { return Raw; }

    SRV* CreateSRV() const;
    UAV* CreateUAV() const;

private:
    ID3D11Texture3D* Raw = nullptr;
    size_t Width = 0;
    size_t Height = 0;
    size_t Depth = 0;
};
