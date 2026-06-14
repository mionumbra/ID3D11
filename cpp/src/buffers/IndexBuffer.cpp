#include <buffers/IndexBuffer.hpp>
#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;

IndexBuffer::IndexBuffer(ID3D11Buffer* buffer, size_t indexSize, size_t numIndices)
    : Buffer(buffer), IndexSize(indexSize), NumIndices(numIndices) {}

IndexBuffer::~IndexBuffer() {}

/// @func d3d11_index_buffer_create(_indexSize, _numIndices)
/// @desc 创建一个索引缓冲区
GM_EXPORT ty_real d3d11_index_buffer_create(ty_real _indexSize, ty_real _numIndices)
{
    if ((_indexSize != 2.0 && _indexSize != 4.0) || _numIndices <= 0.0)
        return GMD3D11_ID_INVALID;

    UINT size = static_cast<UINT>(_indexSize) * static_cast<UINT>(_numIndices);

    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.ByteWidth = size;

    ID3D11Buffer* buffer = nullptr;
    HRESULT hr = g_Device->CreateBuffer(&desc, nullptr, &buffer);

    if (FAILED(hr))
    {
        std::cout << "Failed to create index buffer!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new IndexBuffer(buffer, static_cast<size_t>(_indexSize), static_cast<size_t>(_numIndices)))->GetID());
}

/// @func d3d11_index_buffer_write(_id, _data)
/// @desc 写入数据到索引缓冲区
GM_EXPORT ty_real d3d11_index_buffer_write(ty_real _id, ty_string _data)
{
    g_Context->UpdateSubresource(
        Trackable::Get<IndexBuffer>(static_cast<size_t>(_id))->GetBuffer(),
        0,
        nullptr,
        (void*)_data,
        0,
        0);
    return GM_TRUE;
}

/// @func d3d11_index_buffer_set(_id)
/// @desc 绑定索引缓冲区到输入汇编阶段
GM_EXPORT ty_real d3d11_index_buffer_set(ty_real _id)
{
    IndexBuffer* ib = Trackable::Get<IndexBuffer>(static_cast<size_t>(_id));
    ID3D11Buffer* buffer = ib->GetBuffer();
    DXGI_FORMAT format = (ib->GetIndexSize() == 2) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
    g_Context->IASetIndexBuffer(buffer, format, 0);
    return GM_TRUE;
}

/// @func d3d11_index_buffer_exists(_id)
GM_EXPORT ty_real d3d11_index_buffer_exists(ty_real _id)
{
    return (_id != GMD3D11_ID_INVALID && Trackable::Exists<IndexBuffer>(static_cast<size_t>(_id))) ? GM_TRUE : GM_FALSE;
}

/// @func d3d11_index_buffer_destroy(_id)
GM_EXPORT ty_real d3d11_index_buffer_destroy(ty_real _id)
{
    delete Trackable::Get<IndexBuffer>(static_cast<size_t>(_id));
    return GM_TRUE;
}
