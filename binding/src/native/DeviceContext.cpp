#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "DeviceContextHelpers.hpp"

#include <cstdint>
#include <limits>

#include <d3d11.h>
#include <wrl/client.h>

bool id3d11_device_context_begin(
    const std::uint64_t contextHandle,
    const std::uint64_t asynchronousHandle)
{
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11Asynchronous> asynchronous;
    if (!id3d11::acquireContextAndChild(
        contextHandle,
        asynchronousHandle,
        context,
        asynchronous))
    {
        return false;
    }

    context->Begin(asynchronous.Get());
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return true;
}

bool id3d11_device_context_end(
    const std::uint64_t contextHandle,
    const std::uint64_t asynchronousHandle)
{
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11Asynchronous> asynchronous;
    if (!id3d11::acquireContextAndChild(
        contextHandle,
        asynchronousHandle,
        context,
        asynchronous))
    {
        return false;
    }

    context->End(asynchronous.Get());
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return true;
}

std::int32_t id3d11_device_context_get_data(
    const std::uint64_t contextHandle,
    const std::uint64_t asynchronousHandle,
    const gm::wire::GMBuffer data,
    const std::uint64_t dataSize,
    const std::uint32_t flags)
{
    auto& state = id3d11::BridgeState::instance();
    if (dataSize > std::numeric_limits<UINT>::max() ||
        dataSize > data.length() ||
        (dataSize != 0 && data.data() == nullptr) ||
        (flags & ~static_cast<std::uint32_t>(D3D11_ASYNC_GETDATA_DONOTFLUSH)) != 0)
    {
        state.setLastHresult(E_INVALIDARG);
        return E_INVALIDARG;
    }

    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11Asynchronous> asynchronous;
    if (!id3d11::acquireContextAndChild(
        contextHandle,
        asynchronousHandle,
        context,
        asynchronous))
    {
        return state.lastHresult();
    }

    const HRESULT hresult = context->GetData(
        asynchronous.Get(),
        dataSize == 0 ? nullptr : data.data(),
        static_cast<UINT>(dataSize),
        flags);
    state.setLastHresult(hresult);
    return static_cast<std::int32_t>(hresult);
}

bool id3d11_device_context_flush(const std::uint64_t contextHandle)
{
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }

    context->Flush();
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return true;
}
