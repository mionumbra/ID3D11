#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"
#include "NativeHelpers.hpp"

#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>

using namespace gm::wire;
using namespace gm_structs;
using namespace gm_enums;

namespace
{
    template <typename Interface>
    std::uint64_t internBridgeHandle(
        const Microsoft::WRL::ComPtr<Interface>& object,
        const ID3D11HandleKind kind)
    {
        auto& bridge = id3d11::BridgeState::instance();
        if (!object)
        {
            bridge.setLastHresult(E_HANDLE);
            return 0;
        }
        const std::uint64_t handle = id3d11::HandleRegistry::instance().intern(object.Get(), kind);
        bridge.setLastHresult(handle == 0 ? E_OUTOFMEMORY : S_OK);
        return handle;
    }
}

ID3D11Version id3d11_get_version()
{
    return {
        .major = 0,
        .minor = 1,
        .patch = 0,
        .abi = 1,
    };
}

bool id3d11_is_initialized()
{
    return id3d11::BridgeState::instance().initialized();
}

void id3d11_shutdown()
{
    id3d11::HandleRegistry::instance().clear();
    id3d11::BridgeState::instance().shutdown();
}

std::int32_t id3d11_get_last_hresult()
{
    return id3d11::BridgeState::instance().lastHresult();
}

std::uint64_t id3d11_get_device_handle()
{
    const auto device = id3d11::BridgeState::instance().device();
    return internBridgeHandle(device, ID3D11HandleKind::Device);
}

std::uint64_t id3d11_get_context_handle()
{
    const auto context = id3d11::BridgeState::instance().context();
    return internBridgeHandle(context, ID3D11HandleKind::DeviceContext);
}

std::uint64_t id3d11_get_swapchain_handle()
{
    const auto swapchain = id3d11::BridgeState::instance().swapchain();
    return internBridgeHandle(swapchain, ID3D11HandleKind::SwapChain);
}

gm_structs::ID3D11CreateHandleResult id3d11_swapchain_get_buffer(
    const std::uint64_t swapchainHandle,
    const std::uint32_t bufferIndex)
{
    const auto swapchain = id3d11::acquireInterface<IDXGISwapChain>(
        swapchainHandle,
        gm_enums::ID3D11HandleKind::SwapChain);
    if (!swapchain)
    {
        return {.hresult = E_HANDLE, .handle = 0};
    }

    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
    const HRESULT hresult = swapchain->GetBuffer(
        bufferIndex,
        IID_PPV_ARGS(&texture));
    if (FAILED(hresult))
    {
        id3d11::BridgeState::instance().setLastHresult(hresult);
        return {.hresult = static_cast<std::int32_t>(hresult), .handle = 0};
    }

    const std::uint64_t handle = id3d11::HandleRegistry::instance().intern(
        texture.Get(),
        gm_enums::ID3D11HandleKind::Texture2D);
    const HRESULT finalResult = handle != 0 ? S_OK : E_OUTOFMEMORY;
    id3d11::BridgeState::instance().setLastHresult(finalResult);
    return {
        .hresult = static_cast<std::int32_t>(finalResult),
        .handle = handle,
    };
}

bool id3d11_handle_is_valid(const std::uint64_t handle)
{
    const bool valid = id3d11::HandleRegistry::instance().valid(handle);
    id3d11::BridgeState::instance().setLastHresult(valid ? S_OK : E_HANDLE);
    return valid;
}

ID3D11HandleKind id3d11_handle_get_kind(const std::uint64_t handle)
{
    const auto kind = id3d11::HandleRegistry::instance().kind(handle);
    id3d11::BridgeState::instance().setLastHresult(
        kind == ID3D11HandleKind::Invalid ? E_HANDLE : S_OK);
    return kind;
}

bool id3d11_handle_release(const std::uint64_t handle)
{
    const bool released = id3d11::HandleRegistry::instance().release(handle);
    id3d11::BridgeState::instance().setLastHresult(released ? S_OK : E_HANDLE);
    return released;
}
