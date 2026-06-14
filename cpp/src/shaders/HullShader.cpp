#include <shaders/HullShader.hpp>

#include <utils.hpp>

#include <d3dcompiler.h>
#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;
extern char* g_ErrorString;

HullShader::HullShader(ID3D11HullShader* shader, ID3DBlob* blob)
    : Shader(blob)
    , Raw(shader)
{
}

HullShader::~HullShader()
{
    if (Raw)
    {
        Raw->Release();
    }
}

static HullShader* CompileHS(char* file, char* entryPoint, char* profile)
{
    ID3DBlob* blob = nullptr;
    LPCWSTR path = ConvertCharArrayToLPCWSTR(file);
    HRESULT hr = CompileShader(path, static_cast<LPCSTR>(entryPoint), static_cast<LPCSTR>(profile), &blob);
    delete[] path;

    if (FAILED(hr))
    {
        std::cout << "Failed compiling HS " << file << "!" << std::endl;
        return nullptr;
    }

    ID3D11HullShader* hs = nullptr;
    hr = g_Device->CreateHullShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &hs);

    if (FAILED(hr))
    {
        std::cout << "Failed creating HS " << file << "!" << std::endl;
        return nullptr;
    }

    std::cout << "Compiled HS " << file << std::endl;

    return new HullShader(hs, blob);
}

/// @func d3d11_shader_compile_hs(_file, _entryPoint, _profile)
///
/// @desc Compiles a hull shader from file.
///
/// @param {String} _file The path to file to compile.
/// @param {String} _entryPoint The name of the entry point function, e.g. "main".
/// @param {String} _profile The hull shader profile, e.g. "hs_5_0".
///
/// @return {Real} The ID of the hull shader or {@link GMD3D11_ID_INVALID} on fail.
GM_EXPORT ty_real d3d11_shader_compile_hs(ty_string _file, ty_string _entryPoint, ty_string _profile)
{
    if (HullShader* shader = CompileHS(_file, _entryPoint, _profile))
    {
        return static_cast<ty_real>(shader->GetID());
    }
    return GMD3D11_ID_INVALID;
}

/// @func d3d11_shader_load_hs(_file)
///
/// @desc Loads a compiled hull shader from a file.
///
/// @param {String} _file The path to the compiled hull shader.
///
/// @return {Real} The ID of the hull shader or {@link GMD3D11_ID_INVALID} on fail.
GM_EXPORT ty_real d3d11_shader_load_hs(ty_string _file)
{
    std::vector<char> bytecode = Shader::LoadBlob(_file);
    if (bytecode.empty())
    {
        std::cout << "Failed loading HS " << _file << "!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    ID3D11HullShader* hs = nullptr;
    HRESULT hr = g_Device->CreateHullShader(bytecode.data(), bytecode.size(), nullptr, &hs);

    if (FAILED(hr))
    {
        std::cout << "Failed creating loaded HS " << _file << "!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    ID3DBlob* blob = nullptr;
    hr = D3DCreateBlob(bytecode.size(), &blob);

    if (FAILED(hr))
    {
        std::cout << "Failed creating blob for loaded HS " << _file << "!" << std::endl;
        hs->Release();
        return GMD3D11_ID_INVALID;
    }

    memcpy(blob->GetBufferPointer(), bytecode.data(), bytecode.size());

    std::cout << "Loaded HS " << _file << std::endl;

    return static_cast<ty_real>((new HullShader(hs, blob))->GetID());
}

/// @func d3d11_shader_set_hs(_hs)
///
/// @desc Changes the current hull shader.
///
/// @param {Real} _hs The ID of the shader or {@link GMD3D11_ID_INVALID} to disable the hull stage.
GM_EXPORT ty_real d3d11_shader_set_hs(ty_real _hs)
{
    ID3D11HullShader* shader = (_hs != GMD3D11_ID_INVALID) ? ((HullShader*)Trackable::Get<Shader>(static_cast<size_t>(_hs)))->GetShader() : nullptr;
    g_Context->HSSetShader(shader, nullptr, 0);
    return GM_TRUE;
}