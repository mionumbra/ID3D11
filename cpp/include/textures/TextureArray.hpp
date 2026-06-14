#pragma once

#include <d3d11.h>
#include <Trackable.hpp>

class TextureArray : public Trackable
{
public:
    TextureArray(ID3D11Texture2D* texture2DArray);
    ~TextureArray();

    ID3D11Texture2D* GetTexture2D() const { return Raw2D; }

private:
    ID3D11Texture2D* Raw2D = nullptr;
};
