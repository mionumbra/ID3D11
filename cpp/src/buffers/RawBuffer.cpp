#include <buffers/RawBuffer.hpp>
#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;

RawBuffer::RawBuffer(ID3D11Buffer* buffer, size_t size)
    : Buffer(buffer), Size(size) {}

RawBuffer::~RawBuffer() {}

SRV* RawBuffer::CreateSRV() const
{
    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R32_TYPELESS; // Raw buffer SRV 格式
    desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
    desc.BufferEx.FirstElement = 0;
    desc.BufferEx.NumElements = static_cast<UINT>(Size / 4); // 以 4 字节为单位
    desc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;

    ID3D11ShaderResourceView* srv = nullptr;
    HRESULT hr = g_Device->CreateShaderResourceView(Raw, &desc, &srv);
    if (FAILED(hr))
    {
        std::cout << "Failed to create SRV for Raw buffer!" << std::endl;
        return nullptr;
    }
    return new SRV(srv);
}

UAV* RawBuffer::CreateUAV() const
{
    D3D11_UNORDERED_ACCESS_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R32_TYPELESS; // Raw buffer UAV 格式
    desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    desc.Buffer.FirstElement = 0;
    desc.Buffer.NumElements = static_cast<UINT>(Size / 4);
    desc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;

    ID3D11UnorderedAccessView* uav = nullptr;
    HRESULT hr = g_Device->CreateUnorderedAccessView(Raw, &desc, &uav);
    if (FAILED(hr))
    {
        std::cout << "Failed to create UAV for Raw buffer!" << std::endl;
        return nullptr;
    }
    return new UAV(uav);
}

/// @func d3d11_raw_buffer_create(_size)
GM_EXPORT ty_real d3d11_raw_buffer_create(ty_real _size)
{
    if (_size <= 0.0)
        return GMD3D11_ID_INVALID;

    UINT size = static_cast<UINT>(_size);

    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
    desc.ByteWidth = size;
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;

    ID3D11Buffer* buffer = nullptr;
    HRESULT hr = g_Device->CreateBuffer(&desc, nullptr, &buffer);
    if (FAILED(hr))
    {
        std::cout << "Failed to create Raw buffer!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new RawBuffer(buffer, static_cast<size_t>(size)))->GetID());
}

/// @func d3d11_raw_buffer_write(_id, _data)
GM_EXPORT ty_real d3d11_raw_buffer_write(ty_real _id, ty_string _data)
{
    g_Context->UpdateSubresource(
        Trackable::Get<RawBuffer>(static_cast<size_t>(_id))->GetBuffer(),
        0,
        nullptr,
        (void*)_data,
        0,
        0);
    return GM_TRUE;
}

/// @func d3d11_raw_buffer_create_srv(_id)
GM_EXPORT ty_real d3d11_raw_buffer_create_srv(ty_real _id)
{
    if (SRV* srv = Trackable::Get<RawBuffer>(static_cast<size_t>(_id))->CreateSRV())
        return static_cast<ty_real>(srv->GetID());
    return GMD3D11_ID_INVALID;
}

/// @func d3d11_raw_buffer_create_uav(_id)
GM_EXPORT ty_real d3d11_raw_buffer_create_uav(ty_real _id)
{
    if (UAV* uav = Trackable::Get<RawBuffer>(static_cast<size_t>(_id))->CreateUAV())
        return static_cast<ty_real>(uav->GetID());
    return GMD3D11_ID_INVALID;
}

/// @func d3d11_raw_buffer_exists(_id)
GM_EXPORT ty_real d3d11_raw_buffer_exists(ty_real _id)
{
    return (_id != GMD3D11_ID_INVALID && Trackable::Exists<RawBuffer>(static_cast<size_t>(_id))) ? GM_TRUE : GM_FALSE;
}

/// @func d3d11_raw_buffer_destroy(_id)
GM_EXPORT ty_real d3d11_raw_buffer_destroy(ty_real _id)
{
    delete Trackable::Get<RawBuffer>(static_cast<size_t>(_id));
    return GM_TRUE;
}
