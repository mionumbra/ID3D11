#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"

using namespace gm::wire;
using namespace gm_structs;
using namespace gm_enums;

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

std::int32_t id3d11_get_last_hresult()
{
    return id3d11::BridgeState::instance().lastHresult();
}

std::uint64_t id3d11_get_device_handle()
{
    const auto device = id3d11::BridgeState::instance().device();
    return id3d11::HandleRegistry::instance().intern(device.Get(), ID3D11HandleKind::Device);
}

std::uint64_t id3d11_get_context_handle()
{
    const auto context = id3d11::BridgeState::instance().context();
    return id3d11::HandleRegistry::instance().intern(
        context.Get(),
        ID3D11HandleKind::DeviceContext);
}

std::uint64_t id3d11_get_swapchain_handle()
{
    const auto swapchain = id3d11::BridgeState::instance().swapchain();
    return id3d11::HandleRegistry::instance().intern(
        swapchain.Get(),
        ID3D11HandleKind::SwapChain);
}

bool id3d11_handle_is_valid(const std::uint64_t handle)
{
    return id3d11::HandleRegistry::instance().valid(handle);
}

ID3D11HandleKind id3d11_handle_get_kind(const std::uint64_t handle)
{
    return id3d11::HandleRegistry::instance().kind(handle);
}

bool id3d11_handle_release(const std::uint64_t handle)
{
    return id3d11::HandleRegistry::instance().release(handle);
}
