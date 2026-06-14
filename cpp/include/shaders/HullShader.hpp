#pragma once

#include <common.hpp>
#include <shaders/Shader.hpp>
#include <d3d11.h>

/// @brief Hull shader.
class HullShader final : public Shader
{
public:
    HullShader(ID3D11HullShader* shader, ID3DBlob* blob);
    virtual ~HullShader();

    ID3D11HullShader* GetShader() const { return Raw; }

private:
    ID3D11HullShader* Raw = nullptr;
};
