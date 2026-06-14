#include <shaders/DomainShader.hpp>
#include <utils.hpp>
#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;

DomainShader::DomainShader(ID3D11DomainShader* shader, ID3DBlob* blob)
    : Shader(blob), Raw(shader) {}

DomainShader::~DomainShader()
{
    if (Raw) Raw->Release();
}

/// @func d3d11_domain_shader_create(_source, _entry)
/// @desc Compiles and creates a Domain Shader
GM_EXPORT ty_real d3d11_domain_shader_create(ty_string _source, ty_string _entry)
{
    ID3DBlob* blob = nullptr;
    LPCWSTR path = ConvertCharArrayToLPCWSTR(_source);
    HRESULT hr = CompileShader(path, _entry, "ds_5_0", &blob);
    delete[] path;
    if (FAILED(hr))
        return GMD3D11_ID_INVALID;

    ID3D11DomainShader* shader = nullptr;
    hr = g_Device->CreateDomainShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
    if (FAILED(hr))
    {
        std::cout << "Failed to create Domain Shader!" << std::endl;
        blob->Release();
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new DomainShader(shader, blob))->GetID());
}

/// @func d3d11_domain_shader_set(_id)
/// @desc 绑定 Domain Shader 到管线
GM_EXPORT ty_real d3d11_domain_shader_set(ty_real _id)
{
    DomainShader* ds = Trackable::Get<DomainShader>(static_cast<size_t>(_id));
    g_Context->DSSetShader(ds->GetShader(), nullptr, 0);
    return GM_TRUE;
}

/// @func d3d11_domain_shader_exists(_id)
GM_EXPORT ty_real d3d11_domain_shader_exists(ty_real _id)
{
    return (_id != GMD3D11_ID_INVALID && Trackable::Exists<DomainShader>(static_cast<size_t>(_id))) ? GM_TRUE : GM_FALSE;
}

/// @func d3d11_domain_shader_destroy(_id)
GM_EXPORT ty_real d3d11_domain_shader_destroy(ty_real _id)
{
    delete Trackable::Get<DomainShader>(static_cast<size_t>(_id));
    return GM_TRUE;
}
