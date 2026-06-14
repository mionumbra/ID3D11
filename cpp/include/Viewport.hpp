#pragma once

#include <common.hpp>
#include <d3d11.h>

/// @brief Viewport wrapper.
class Viewport final
{
public:
    Viewport(float x, float y, float width, float height, float minDepth = 0.0f, float maxDepth = 1.0f);
    ~Viewport();

    D3D11_VIEWPORT GetDesc() const { return Desc; }

private:
    D3D11_VIEWPORT Desc{};
};
