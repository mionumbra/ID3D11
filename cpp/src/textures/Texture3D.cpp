#include "textures/Texture3D.hpp"

#include <views/DSV.hpp>
#include <views/RTV.hpp>
#include <views/SRV.hpp>
#include <views/UAV.hpp>

#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;

Texture3D::Texture3D(ID3D11Texture3D* texture3D)
    : Trackable()
    , Raw3D(texture3D)
{
}

Texture3D::~Texture3D()
{
    if (Raw3D)
    {
        Raw3D->Release();
        Raw3D = nullptr;
    }
}

/// @func d3d11_texture3d_create_impl(_buffer, _pSysMem, _memPitch, _memSlicePitch)
///
/// @desc Creates a new 3D texture.
///
/// @param {Pointer} _buffer A pointer to a buffer containing serialized {@link D3D11_TEXTURE3D_DESC}.
/// @param {Pointer} _pSysMem
/// @param {Real} _memPitch
/// @param {Real} _memSlicePitch
///
/// @return {Real} The ID of the created 3D texture or {@link GMD3D11_ID_INVALID} on fail.
GM_EXPORT ty_real d3d11_texture3d_create_impl(ty_string _buffer, ty_string _pSysMem, ty_real _memPitch, ty_real _memSlicePitch)
{
    D3D11_TEXTURE3D_DESC desc = {};
    desc.Width = ReadBuffer<UINT>(_buffer);
    desc.Height = ReadBuffer<UINT>(_buffer);
    desc.Depth = ReadBuffer<UINT>(_buffer);
    desc.MipLevels = ReadBuffer<UINT>(_buffer);
    desc.Format = static_cast<DXGI_FORMAT>(ReadBuffer<uint32_t>(_buffer));
    desc.Usage = static_cast<D3D11_USAGE>(ReadBuffer<uint32_t>(_buffer));
    desc.BindFlags = ReadBuffer<UINT>(_buffer);
    desc.CPUAccessFlags = ReadBuffer<UINT>(_buffer);
    desc.MiscFlags = ReadBuffer<UINT>(_buffer);

    D3D11_SUBRESOURCE_DATA data = {};
    data.pSysMem = _pSysMem;
    data.SysMemPitch = static_cast<UINT>(_memPitch);
    data.SysMemSlicePitch = static_cast<UINT>(_memSlicePitch);

    ID3D11Texture3D* texture = nullptr;
    HRESULT hr = g_Device->CreateTexture3D(&desc, &data, &texture);

    if (FAILED(hr) || !texture)
    {
        std::cout << "Failed to create a 3D texture!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new Texture3D(texture))->GetID());
}

/// @func d3d11_texture3d_exists(_id)
GM_EXPORT ty_real d3d11_texture3d_exists(ty_real _id)
{
    return (_id != GMD3D11_ID_INVALID && Trackable::Exists<Texture3D>(static_cast<size_t>(_id))) ? GM_TRUE : GM_FALSE;
}

/// @func d3d11_texture3d_destroy(_id)
GM_EXPORT ty_real d3d11_texture3d_destroy(ty_real _id)
{
    delete Trackable::Get<Texture3D>(static_cast<size_t>(_id));
    return GM_TRUE;
}
