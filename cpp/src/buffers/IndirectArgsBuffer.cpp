#include <buffers/IndirectArgsBuffer.hpp>
#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;

IndirectArgsBuffer::IndirectArgsBuffer(ID3D11Buffer* buffer, size_t size)
    : Buffer(buffer), Size(size) {}

IndirectArgsBuffer::~IndirectArgsBuffer() {}

/// @func d3d11_indirect_args_buffer_create(_size)
/// @desc 创建一个间接参数缓冲区
GM_EXPORT ty_real d3d11_indirect_args_buffer_create(ty_real _size)
{
    if (_size <= 0.0)
        return GMD3D11_ID_INVALID;

    UINT size = static_cast<UINT>(_size);

    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
    desc.ByteWidth = size;
    desc.MiscFlags = D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS;

    ID3D11Buffer* buffer = nullptr;
    HRESULT hr = g_Device->CreateBuffer(&desc, nullptr, &buffer);
    if (FAILED(hr))
    {
        std::cout << "Failed to create Indirect Args buffer!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new IndirectArgsBuffer(buffer, static_cast<size_t>(size)))->GetID());
}

/// @func d3d11_indirect_args_buffer_write(_id, _data)
/// @desc 写入数据到间接参数缓冲区
GM_EXPORT ty_real d3d11_indirect_args_buffer_write(ty_real _id, ty_string _data)
{
    g_Context->UpdateSubresource(
        Trackable::Get<IndirectArgsBuffer>(static_cast<size_t>(_id))->GetBuffer(),
        0,
        nullptr,
        (void*)_data,
        0,
        0);
    return GM_TRUE;
}

/// @func d3d11_indirect_args_buffer_exists(_id)
GM_EXPORT ty_real d3d11_indirect_args_buffer_exists(ty_real _id)
{
    return (_id != GMD3D11_ID_INVALID && Trackable::Exists<IndirectArgsBuffer>(static_cast<size_t>(_id))) ? GM_TRUE : GM_FALSE;
}

/// @func d3d11_indirect_args_buffer_destroy(_id)
GM_EXPORT ty_real d3d11_indirect_args_buffer_destroy(ty_real _id)
{
    delete Trackable::Get<IndirectArgsBuffer>(static_cast<size_t>(_id));
    return GM_TRUE;
}
