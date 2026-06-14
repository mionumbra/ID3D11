#include "textures/TextureArray.hpp"

#include <views/DSV.hpp>
#include <views/RTV.hpp>
#include <views/SRV.hpp>
#include <views/UAV.hpp>

#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;

TextureArray::TextureArray(ID3D11Texture2D* texture2DArray)
    : Trackable()
    , Raw2D(texture2DArray)
{
}

TextureArray::~TextureArray()
{
    if (Raw2D)
    {
        Raw2D->Release();
        Raw2D = nullptr;
    }
}

/// @func d3d11_texturearray_create_impl(_buffer, _pSysMem, _memPitch, _memSlicePitch)
///
/// @desc Creates a new Texture2D array.
///
/// @param {Pointer} _buffer A pointer to a buffer containing serialized {@link D3D11_TEXTURE2D_DESC} (ArraySize > 1).
/// @param {Pointer} _pSysMem
/// @param {Real} _memPitch
/// @param {Real} _memSlicePitch
///
/// @return {Real} The ID of the created texture array or {@link GMD3D11_ID_INVALID} on fail.
GM_EXPORT ty_real d3d11_texturearray_create_impl(ty_string _buffer, ty_string _pSysMem, ty_real _memPitch, ty_real _memSlicePitch)
{
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = ReadBuffer<UINT>(_buffer);
    desc.Height = ReadBuffer<UINT>(_buffer);
    desc.MipLevels = ReadBuffer<UINT>(_buffer);
    desc.ArraySize = ReadBuffer<UINT>(_buffer); // must be > 1 for array
    desc.Format = static_cast<DXGI_FORMAT>(ReadBuffer<uint32_t>(_buffer));
    desc.SampleDesc.Count = ReadBuffer<UINT>(_buffer);
    desc.SampleDesc.Quality = ReadBuffer<UINT>(_buffer);
    desc.Usage = static_cast<D3D11_USAGE>(ReadBuffer<uint32_t>(_buffer));
    desc.BindFlags = ReadBuffer<UINT>(_buffer);
    desc.CPUAccessFlags = ReadBuffer<UINT>(_buffer);
    desc.MiscFlags = ReadBuffer<UINT>(_buffer);

    D3D11_SUBRESOURCE_DATA data = {};
    data.pSysMem = _pSysMem;
    data.SysMemPitch = static_cast<UINT>(_memPitch);
    data.SysMemSlicePitch = static_cast<UINT>(_memSlicePitch);

    ID3D11Texture2D* texture = nullptr;
    HRESULT hr = g_Device->CreateTexture2D(&desc, &data, &texture);

    if (FAILED(hr) || !texture)
    {
        std::cout << "Failed to create a Texture2D array!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new TextureArray(texture))->GetID());
}

/// @func d3d11_texturearray_exists(_id)
GM_EXPORT ty_real d3d11_texturearray_exists(ty_real _id)
{
    return (_id != GMD3D11_ID_INVALID && Trackable::Exists<TextureArray>(static_cast<size_t>(_id))) ? GM_TRUE : GM_FALSE;
}

/// @func d3d11_texturearray_destroy(_id)
GM_EXPORT ty_real d3d11_texturearray_destroy(ty_real _id)
{
    delete Trackable::Get<TextureArray>(static_cast<size_t>(_id));
    return GM_TRUE;
}
