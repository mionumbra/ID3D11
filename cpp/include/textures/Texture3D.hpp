#pragma once

#include <d3d11.h>
#include <Trackable.hpp>

class Texture3D : public Trackable
{
public:
    Texture3D(ID3D11Texture3D* texture3D);
    ~Texture3D();

    ID3D11Texture3D* GetTexture3D() const { return Raw3D; }

private:
    ID3D11Texture3D* Raw3D = nullptr;
};
