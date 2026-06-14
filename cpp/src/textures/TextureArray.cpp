#include <textures/TextureArray.hpp>
#include <iostream>

extern ID3D11Device* g_Device;

TextureArray::TextureArray(ID3D11Texture2D* texture, size_t width, size_t height, size_t count)
    : Raw(texture), Width(width), Height(height), Count(count) {}

TextureArray::~TextureArray()
{
    if (Raw) Raw->Release();
}

SRV* TextureArray::CreateSRV() const
{
    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
    desc.Texture2DArray.MostDetailedMip = 0;
    desc.Texture2DArray.MipLevels = -1;
    desc.Texture2DArray.FirstArraySlice = 0;
    desc.Texture2DArray.ArraySize = static_cast<UINT>(Count);

    ID3D11ShaderResourceView* srv = nullptr;
    HRESULT hr = g_Device->CreateShaderResourceView(Raw, &desc, &srv);
    if (FAILED(hr))
    {
        std::cout << "Failed to create SRV for Texture Array!" << std::endl;
        return nullptr;
    }
    return new SRV(srv);
}

UAV* TextureArray::CreateUAV() const
{
    D3D11_UNORDERED_ACCESS_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
    desc.Texture2DArray.MipSlice = 0;
    desc.Texture2DArray.FirstArraySlice = 0;
    desc.Texture2DArray.ArraySize = static_cast<UINT>(Count);

    ID3D11UnorderedAccessView* uav = nullptr;
    HRESULT hr = g_Device->CreateUnorderedAccessView(Raw, &desc, &uav);
    if (FAILED(hr))
    {
        std::cout << "Failed to create UAV for Texture Array!" << std::endl;
        return nullptr;
    }
    return new UAV(uav);
}

/// @func d3d11_texture_array_create(_w, _h, _count)
GM_EXPORT ty_real d3d11_texture_array_create(ty_real _w, ty_real _h, ty_real _count)
{
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = static_cast<UINT>(_w);
    desc.Height = static_cast<UINT>(_h);
    desc.MipLevels = 1;
    desc.ArraySize = static_cast<UINT>(_count);
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;

    ID3D11Texture2D* texture = nullptr;
    HRESULT hr = g_Device->CreateTexture2D(&desc, nullptr, &texture);
    if (FAILED(hr))
    {
        std::cout << "Failed to create Texture Array!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new TextureArray(texture, static_cast<size_t>(_w), static_cast<size_t>(_h), static_cast<size_t>(_count)))->GetID());
}
