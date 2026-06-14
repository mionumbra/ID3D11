#include <buffers/UploadBuffer.hpp>
#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;

UploadBuffer::UploadBuffer(ID3D11Buffer* buffer, size_t size)
    : Buffer(buffer), Size(size) {}

UploadBuffer::~UploadBuffer() {}

bool UploadBuffer::Map()
{
    if (!Mapped)
    {
        Mapped = SUCCEEDED(g_Context->Map(Raw, 0, D3D11_MAP_WRITE_DISCARD, 0, &MapData));
        return Mapped;
    }
    return false;
}

bool UploadBuffer::Unmap()
{
    if (Mapped)
    {
        g_Context->Unmap(Raw, 0);
        Mapped = false;
        return true;
    }
    return false;
}

/// @func d3d11_upload_buffer_create(_size)
/// @desc 创建一个 Upload 缓冲区
GM_EXPORT ty_real d3d11_upload_buffer_create(ty_real _size)
{
    if (_size <= 0.0)
        return GMD3D11_ID_INVALID;

    UINT size = static_cast<UINT>(_size);

    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DYNAMIC; // 动态缓冲区，支持 CPU 写入
    desc.BindFlags = 0;               // 不直接绑定到管线
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.ByteWidth = size;

    ID3D11Buffer* buffer = nullptr;
    HRESULT hr = g_Device->CreateBuffer(&desc, nullptr, &buffer);
    if (FAILED(hr))
    {
        std::cout << "Failed to create Upload buffer!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new UploadBuffer(buffer, static_cast<size_t>(size)))->GetID());
}

/// @func d3d11_upload_buffer_map(_id)
GM_EXPORT ty_real d3d11_upload_buffer_map(ty_real _id)
{
    return Trackable::Get<UploadBuffer>(static_cast<size_t>(_id))->Map() ? GM_TRUE : GM_FALSE;
}

/// @func d3d11_upload_buffer_unmap(_id)
GM_EXPORT ty_real d3d11_upload_buffer_unmap(ty_real _id)
{
    return Trackable::Get<UploadBuffer>(static_cast<size_t>(_id))->Unmap() ? GM_TRUE : GM_FALSE;
}

/// @func d3d11_upload_buffer_get_size(_id)
GM_EXPORT ty_real d3d11_upload_buffer_get_size(ty_real _id)
{
    return Trackable::Get<UploadBuffer>(static_cast<size_t>(_id))->GetSize();
}

/// @func d3d11_upload_buffer_exists(_id)
GM_EXPORT ty_real d3d11_upload_buffer_exists(ty_real _id)
{
    return (_id != GMD3D11_ID_INVALID && Trackable::Exists<UploadBuffer>(static_cast<size_t>(_id))) ? GM_TRUE : GM_FALSE;
}

/// @func d3d11_upload_buffer_destroy(_id)
GM_EXPORT ty_real d3d11_upload_buffer_destroy(ty_real _id)
{
    delete Trackable::Get<UploadBuffer>(static_cast<size_t>(_id));
    return GM_TRUE;
}
