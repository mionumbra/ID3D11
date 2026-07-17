#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"
#include "NativeHelpers.hpp"

#include <d3d11.h>
#include <wrl/client.h>

std::uint64_t id3d11_device_child_get_device(const std::uint64_t deviceChild)
{
    const auto child = id3d11::acquireInterface<ID3D11DeviceChild>(deviceChild);
    if (!child)
    {
        return 0;
    }

    Microsoft::WRL::ComPtr<ID3D11Device> device;
    child->GetDevice(&device);
    if (!device)
    {
        id3d11::BridgeState::instance().setLastHresult(E_FAIL);
        return 0;
    }

    const std::uint64_t handle = id3d11::HandleRegistry::instance().intern(
        device.Get(),
        gm_enums::ID3D11HandleKind::Device);
    id3d11::BridgeState::instance().setLastHresult(handle == 0 ? E_OUTOFMEMORY : S_OK);
    return handle;
}

gm_enums::ID3D11ResourceDimension id3d11_resource_get_dimension(
    const std::uint64_t resourceHandle)
{
    const auto resource = id3d11::acquireInterface<ID3D11Resource>(resourceHandle);
    if (!resource)
    {
        return gm_enums::ID3D11ResourceDimension::Unknown;
    }

    D3D11_RESOURCE_DIMENSION dimension = D3D11_RESOURCE_DIMENSION_UNKNOWN;
    resource->GetType(&dimension);
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return static_cast<gm_enums::ID3D11ResourceDimension>(dimension);
}

std::uint32_t id3d11_resource_get_eviction_priority(const std::uint64_t resourceHandle)
{
    const auto resource = id3d11::acquireInterface<ID3D11Resource>(resourceHandle);
    if (!resource)
    {
        return 0;
    }

    const UINT priority = resource->GetEvictionPriority();
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return priority;
}

bool id3d11_resource_set_eviction_priority(
    const std::uint64_t resourceHandle,
    const std::uint32_t evictionPriority)
{
    const auto resource = id3d11::acquireInterface<ID3D11Resource>(resourceHandle);
    if (!resource)
    {
        return false;
    }

    resource->SetEvictionPriority(evictionPriority);
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return true;
}
