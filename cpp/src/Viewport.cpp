#include <pipeline/Viewport.hpp>
#include <iostream>

extern ID3D11DeviceContext* g_Context;

Viewport::Viewport(float x, float y, float width, float height, float minDepth, float maxDepth)
{
    Desc.TopLeftX = x;
    Desc.TopLeftY = y;
    Desc.Width    = width;
    Desc.Height   = height;
    Desc.MinDepth = minDepth;
    Desc.MaxDepth = maxDepth;
}

Viewport::~Viewport() {}

/// @func d3d11_viewport_set(_x, _y, _w, _h, _minDepth, _maxDepth)
GM_EXPORT ty_real d3d11_viewport_set(ty_real _x, ty_real _y, ty_real _w, ty_real _h, ty_real _minDepth, ty_real _maxDepth)
{
    D3D11_VIEWPORT vp{};
    vp.TopLeftX = static_cast<FLOAT>(_x);
    vp.TopLeftY = static_cast<FLOAT>(_y);
    vp.Width    = static_cast<FLOAT>(_w);
    vp.Height   = static_cast<FLOAT>(_h);
    vp.MinDepth = static_cast<FLOAT>(_minDepth);
    vp.MaxDepth = static_cast<FLOAT>(_maxDepth);

    g_Context->RSSetViewports(1, &vp);
    return GM_TRUE;
}
