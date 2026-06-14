#include <shaders/HullShader.hpp>
#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;

HullShader::HullShader(ID3D11HullShader* shader, ID3DBlob* blob)
    : Shader(blob), Raw(shader) {}

HullShader::~HullShader()
{
    if (Raw) Raw->Release();
}

/// @func d3d11_hull_shader_create(_source, _entry)
GM_EXPORT ty_real d3d11_hull_shader_create(ty_string _source, ty_string _entry)
{
    ID3DBlob* blob = nullptr;
    if (!CompileShader(_source, _entry, "hs_5_0", &blob))
        return GMD3D11_ID_INVALID;

    ID3D11HullShader* shader = nullptr;
    HRESULT hr = g_Device->CreateHullShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
    if (FAILED(hr))
    {
        std::cout << "Failed to create Hull Shader!" << std::endl;
        blob->Release();
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new HullShader(shader, blob))->GetID());
}

/// @func d3d11_hull_shader_set(_id)
GM_EXPORT ty_real d3d11_hull_shader_set(ty_real _id)
{
    HullShader* hs = Trackable::Get<HullShader>(static_cast<size_t>(_id));
    g_Context->HSSetShader(hs->GetShader(), nullptr, 0);
    return GM_TRUE;
}

/// @func d3d11_hull_shader_exists(_id)
GM_EXPORT ty_real d3d11_hull_shader_exists(ty_real _id)
{
    return (_id != GMD3D11_ID_INVALID && Trackable::Exists<HullShader>(static_cast<size_t>(_id))) ? GM_TRUE : GM_FALSE;
}

/// @func d3d11_hull_shader_destroy(_id)
GM_EXPORT ty_real d3d11_hull_shader_destroy(ty_real _id)
{
    delete Trackable::Get<HullShader>(static_cast<size_t>(_id));
    return GM_TRUE;
}
