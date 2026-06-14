#include <pipeline/OcclusionQuery.hpp>
#include <iostream>

extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_Context;

OcclusionQuery::OcclusionQuery(ID3D11Query* query)
    : Raw(query) {}

OcclusionQuery::~OcclusionQuery()
{
    if (Raw) Raw->Release();
}

/// @func d3d11_occlusion_query_create()
GM_EXPORT ty_real d3d11_occlusion_query_create()
{
    D3D11_QUERY_DESC desc = {};
    desc.Query = D3D11_QUERY_OCCLUSION;
    desc.MiscFlags = 0;

    ID3D11Query* query = nullptr;
    HRESULT hr = g_Device->CreateQuery(&desc, &query);
    if (FAILED(hr))
    {
        std::cout << "Failed to create Occlusion Query!" << std::endl;
        return GMD3D11_ID_INVALID;
    }

    return static_cast<ty_real>((new OcclusionQuery(query))->GetID());
}

/// @func d3d11_occlusion_query_begin(_id)
GM_EXPORT ty_real d3d11_occlusion_query_begin(ty_real _id)
{
    g_Context->Begin(Trackable::Get<OcclusionQuery>(static_cast<size_t>(_id))->GetQuery());
    return GM_TRUE;
}

/// @func d3d11_occlusion_query_end(_id)
GM_EXPORT ty_real d3d11_occlusion_query_end(ty_real _id)
{
    g_Context->End(Trackable::Get<OcclusionQuery>(static_cast<size_t>(_id))->GetQuery());
    return GM_TRUE;
}

/// @func d3d11_occlusion_query_get_data(_id)
GM_EXPORT ty_real d3d11_occlusion_query_get_data(ty_real _id)
{
    UINT64 pixels = 0;
    while (g_Context->GetData(Trackable::Get<OcclusionQuery>(static_cast<size_t>(_id))->GetQuery(), &pixels, sizeof(UINT64), 0) == S_FALSE)
    {
        // 等待 GPU 完成
    }
    return static_cast<ty_real>(pixels);
}

/// @func d3d11_occlusion_query_destroy(_id)
GM_EXPORT ty_real d3d11_occlusion_query_destroy(ty_real _id)
{
    delete Trackable::Get<OcclusionQuery>(static_cast<size_t>(_id));
    return GM_TRUE;
}
