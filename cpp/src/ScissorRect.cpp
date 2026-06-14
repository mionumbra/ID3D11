#include <pipeline/ScissorRect.hpp>
#include <iostream>

extern ID3D11DeviceContext* g_Context;

ScissorRect::ScissorRect(int left, int top, int right, int bottom)
{
    Rect.left   = left;
    Rect.top    = top;
    Rect.right  = right;
    Rect.bottom = bottom;
}

ScissorRect::~ScissorRect() {}

/// @func d3d11_scissor_rect_set(_left, _top, _right, _bottom)
GM_EXPORT ty_real d3d11_scissor_rect_set(ty_real _left, ty_real _top, ty_real _right, ty_real _bottom)
{
    D3D11_RECT rect{};
    rect.left   = static_cast<LONG>(_left);
    rect.top    = static_cast<LONG>(_top);
    rect.right  = static_cast<LONG>(_right);
    rect.bottom = static_cast<LONG>(_bottom);

    g_Context->RSSetScissorRects(1, &rect);
    return GM_TRUE;
}
