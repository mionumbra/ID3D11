#include <buffers/VertexBuffer.hpp>
#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;

VertexBuffer::VertexBuffer(ID3D11Buffer* buffer, size_t stride, size_t numVertices)
    : Buffer(buffer), Stride(stride), NumVertices(numVertices) {}

VertexBuffer::~VertexBuffer() {}

/// @func d3d11_vertex_buffer_create(_stride, _numVertices)
GM_EXPORT ty_real d3d11_vertex_buffer_create(ty_real _stride, ty_real _numVertices)
{
    if (_stride <= 0.0 || _numVertices <= 0.0)
        return GMD3D11_ID_INVALID;

    UINT size = static_cast<UINT>(_stride) * static_cast<UINT>(_numVertices);

    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.ByteWidth = size;

    ID3D11Buffer* buffer = nullptr;
    HRESULT hr = g_Device->CreateBuffer(&desc, nullptr, &buffer);

    if (FAILED(hr))
    {
        std::cout << "Failed to create vertex buffer!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new VertexBuffer(buffer, static_cast<size_t>(_stride), static_cast<size_t>(_numVertices)))->GetID());
}

/// @func d3d11_vertex_buffer_write(_id, _data)
GM_EXPORT ty_real d3d11_vertex_buffer_write(ty_real _id, ty_string _data)
{
    g_Context->UpdateSubresource(
        Trackable::Get<VertexBuffer>(static_cast<size_t>(_id))->GetBuffer(),
        0,
        nullptr,
        (void*)_data,
        0,
        0);
    return GM_TRUE;
}

/// @func d3d11_vertex_buffer_set(_slot, _id, _offset)
GM_EXPORT ty_real d3d11_vertex_buffer_set(ty_real _slot, ty_real _id, ty_real _offset)
{
    VertexBuffer* vb = Trackable::Get<VertexBuffer>(static_cast<size_t>(_id));
    ID3D11Buffer* buffer = vb->GetBuffer();
    UINT stride = static_cast<UINT>(vb->GetStride());
    UINT offset = static_cast<UINT>(_offset);
    g_Context->IASetVertexBuffers(static_cast<UINT>(_slot), 1, &buffer, &stride, &offset);
    return GM_TRUE;
}

/// @func d3d11_vertex_buffer_exists(_id)
GM_EXPORT ty_real d3d11_vertex_buffer_exists(ty_real _id)
{
    return (_id != GMD3D11_ID_INVALID && Trackable::Exists<VertexBuffer>(static_cast<size_t>(_id))) ? GM_TRUE : GM_FALSE;
}

/// @func d3d11_vertex_buffer_destroy(_id)
GM_EXPORT ty_real d3d11_vertex_buffer_destroy(ty_real _id)
{
    delete Trackable::Get<VertexBuffer>(static_cast<size_t>(_id));
    return GM_TRUE;
}
