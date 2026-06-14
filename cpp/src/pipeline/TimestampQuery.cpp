#include <pipeline/TimestampQuery.hpp>
#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;

TimestampQuery::TimestampQuery(ID3D11Query* query)
    : Raw(query) {}

TimestampQuery::~TimestampQuery()
{
    if (Raw) Raw->Release();
}

/// @func d3d11_timestamp_query_create()
GM_EXPORT ty_real d3d11_timestamp_query_create()
{
    D3D11_QUERY_DESC desc = {};
    desc.Query = D3D11_QUERY_TIMESTAMP;
    desc.MiscFlags = 0;

    ID3D11Query* query = nullptr;
    HRESULT hr = g_Device->CreateQuery(&desc, &query);
    if (FAILED(hr))
    {
        std::cout << "Failed to create Timestamp Query!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new TimestampQuery(query))->GetID());
}

/// @func d3d11_timestamp_query_end(_id)
GM_EXPORT ty_real d3d11_timestamp_query_end(ty_real _id)
{
    g_Context->End(Trackable::Get<TimestampQuery>(static_cast<size_t>(_id))->GetQuery());
    return GM_TRUE;
}

/// @func d3d11_timestamp_query_get_data(_id)
GM_EXPORT ty_real d3d11_timestamp_query_get_data(ty_real _id)
{
    UINT64 timestamp = 0;
    while (g_Context->GetData(Trackable::Get<TimestampQuery>(static_cast<size_t>(_id))->GetQuery(), &timestamp, sizeof(UINT64), 0) == S_FALSE)
    {
        // 等待 GPU 完成
    }
    return static_cast<ty_real>(timestamp);
}

/// @func d3d11_timestamp_query_destroy(_id)
GM_EXPORT ty_real d3d11_timestamp_query_destroy(ty_real _id)
{
    delete Trackable::Get<TimestampQuery>(static_cast<size_t>(_id));
    return GM_TRUE;
}
