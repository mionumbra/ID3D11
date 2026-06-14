#include <buffers/AppendConsumeBuffer.hpp>
#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;

AppendConsumeBuffer::AppendConsumeBuffer(ID3D11Buffer* buffer, size_t stride, size_t numElements)
    : Buffer(buffer), Stride(stride), NumElements(numElements) {}

AppendConsumeBuffer::~AppendConsumeBuffer() {}

SRV* AppendConsumeBuffer::CreateSRV() const
{
    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_UNKNOWN;
    desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
    desc.Buffer.NumElements = NumElements;

    ID3D11ShaderResourceView* srv = nullptr;
    HRESULT hr = g_Device->CreateShaderResourceView(Raw, &desc, &srv);
    if (FAILED(hr))
    {
        std::cout << "Failed to create SRV for Append/Consume buffer!" << std::endl;
        return nullptr;
    }
    return new SRV(srv);
}

UAV* AppendConsumeBuffer::CreateUAV() const
{
    D3D11_UNORDERED_ACCESS_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_UNKNOWN;
    desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    desc.Buffer.NumElements = NumElements;
    desc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_APPEND; // 关键标志位

    ID3D11UnorderedAccessView* uav = nullptr;
    HRESULT hr = g_Device->CreateUnorderedAccessView(Raw, &desc, &uav);
    if (FAILED(hr))
    {
        std::cout << "Failed to create UAV for Append/Consume buffer!" << std::endl;
        return nullptr;
    }
    return new UAV(uav);
}

/// @func d3d11_append_buffer_create(_stride, _numElements)
GM_EXPORT ty_real d3d11_append_buffer_create(ty_real _stride, ty_real _numElements)
{
    if (_stride <= 0.0 || _numElements <= 0.0)
        return GMD3D11_ID_INVALID;

    UINT size = static_cast<UINT>(_stride) * static_cast<UINT>(_numElements);

    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
    desc.ByteWidth = size;
    desc.StructureByteStride = static_cast<UINT>(_stride);
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

    ID3D11Buffer* buffer = nullptr;
    HRESULT hr = g_Device->CreateBuffer(&desc, nullptr, &buffer);
    if (FAILED(hr))
    {
        std::cout << "Failed to create Append/Consume buffer!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new AppendConsumeBuffer(buffer, static_cast<size_t>(_stride), static_cast<size_t>(_numElements)))->GetID());
}

/// @func d3d11_append_buffer_create_srv(_id)
GM_EXPORT ty_real d3d11_append_buffer_create_srv(ty_real _id)
{
    if (SRV* srv = Trackable::Get<AppendConsumeBuffer>(static_cast<size_t>(_id))->CreateSRV())
        return static_cast<ty_real>(srv->GetID());
    return GMD3D11_ID_INVALID;
}

/// @func d3d11_append_buffer_create_uav(_id)
GM_EXPORT ty_real d3d11_append_buffer_create_uav(ty_real _id)
{
    if (UAV* uav = Trackable::Get<AppendConsumeBuffer>(static_cast<size_t>(_id))->CreateUAV())
        return static_cast<ty_real>(uav->GetID());
    return GMD3D11_ID_INVALID;
}

/// @func d3d11_append_buffer_exists(_id)
GM_EXPORT ty_real d3d11_append_buffer_exists(ty_real _id)
{
    return (_id != GMD3D11_ID_INVALID && Trackable::Exists<AppendConsumeBuffer>(static_cast<size_t>(_id))) ? GM_TRUE : GM_FALSE;
}

/// @func d3d11_append_buffer_destroy(_id)
GM_EXPORT ty_real d3d11_append_buffer_destroy(ty_real _id)
{
    delete Trackable::Get<AppendConsumeBuffer>(static_cast<size_t>(_id));
    return GM_TRUE;
}
