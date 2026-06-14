#pragma once

#include <common.hpp>
#include <shaders/Shader.hpp>
#include <d3d11.h>

/// @brief Domain shader.
class DomainShader final : public Shader
{
public:
    DomainShader(ID3D11DomainShader* shader, ID3DBlob* blob);
    virtual ~DomainShader();

    ID3D11DomainShader* GetShader() const { return Raw; }

private:
    ID3D11DomainShader* Raw = nullptr;
};
