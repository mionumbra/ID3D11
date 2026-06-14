#pragma once

#include <common.hpp>
#include <textures/Texture.hpp>
#include <views/SRV.hpp>
#include <views/UAV.hpp>
#include <d3d11.h>

/// @brief Texture2D array wrapper.
class TextureArray final : public Texture
{
public:
    TextureArray(ID3D11Texture2D* texture, size_t width, size_t height, size_t count);
    virtual ~TextureArray();

    ID3D11Texture2D* GetTexture() const { return Raw; }

    SRV* CreateSRV() const;
    UAV* CreateUAV() const;

private:
    ID3D11Texture2D* Raw = nullptr;
    size_t Width = 0;
    size_t Height = 0;
    size_t Count = 0;
};
