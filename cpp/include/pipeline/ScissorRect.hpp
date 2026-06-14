#pragma once

#include <common.hpp>
#include <d3d11.h>

/// @brief Scissor rectangle wrapper.
class ScissorRect final
{
public:
    ScissorRect(int left, int top, int right, int bottom);
    ~ScissorRect();

    D3D11_RECT GetDesc() const { return Rect; }

private:
    D3D11_RECT Rect{};
};
