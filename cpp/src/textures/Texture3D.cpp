#include <textures/Texture3D.hpp>
#include <iostream>

extern ID3D11Device* g_Device;

Texture3D::Texture3D(ID3D11Texture3D* texture, size_t width, size_t height, size_t depth)
    : Raw(texture), Width(width), Height(height), Depth(depth) {}

Texture3D::~Texture3D()
{
    if (Raw) Raw->Release();
}

SRV* Texture3D::CreateSRV() const
{
    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
    desc.Texture3D.MostDetailedMip = 0;
    desc.Texture3D.MipLevels = -1;

    ID3D11ShaderResourceView* srv = nullptr;
    HRESULT hr = g_Device->CreateShaderResourceView(Raw, &desc, &srv);
    if (FAILED(hr))
    {
        std::cout << "Failed to create SRV for 3D texture!" << std::endl;
        return nullptr;
    }
    return new SRV(srv);
}

UAV* Texture3D::CreateUAV() const
{
    D3D11_UNORDERED_ACCESS_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE3D;
    desc.Texture3D.MipSlice = 0;

    ID3D11UnorderedAccessView* uav = nullptr;
    HRESULT hr = g_Device->CreateUnorderedAccessView(Raw, &desc, &uav);
    if (FAILED(hr))
    {
        std::cout << "Failed to create UAV for 3D texture!" << std::endl;
        return nullptr;
    }
    return new UAV(uav);
}

/// @func d3d11_texture3d_create(_w, _h, _d)
GM_EXPORT ty_real d3d11_texture3d_create(ty_real _w, ty_real _h, ty_real _d)
{
    D3D11_TEXTURE3D_DESC desc = {};
    desc.Width = static_cast<UINT>(_w);
    desc.Height = static_cast<UINT>(_h);
    desc.Depth = static_cast<UINT>(_d);
    desc.MipLevels = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;

    ID3D11Texture3D* texture = nullptr;
    HRESULT hr = g_Device->CreateTexture3D(&desc, nullptr, &texture);
    if (FAILED(hr))
    {
        std::cout << "Failed to create 3D texture!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new Texture3D(texture, static_cast<size_t>(_w), static_cast<size_t>(_h), static_cast<size_t>(_d)))->GetID());
}
