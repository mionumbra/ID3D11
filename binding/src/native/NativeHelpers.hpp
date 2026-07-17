#pragma once

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"

#include <cstdint>

#include <wrl/client.h>

namespace id3d11
{
    template<typename Interface>
    [[nodiscard]] Microsoft::WRL::ComPtr<Interface> acquireInterface(
        const std::uint64_t handle,
        const HandleRegistry::Kind expectedKind = HandleRegistry::Kind::Invalid) noexcept
    {
        const Microsoft::WRL::ComPtr<IUnknown> unknown =
            HandleRegistry::instance().acquire(handle, expectedKind);
        if (!unknown)
        {
            BridgeState::instance().setLastHresult(E_HANDLE);
            return {};
        }

        Microsoft::WRL::ComPtr<Interface> result;
        const HRESULT hresult = unknown.As(&result);
        BridgeState::instance().setLastHresult(hresult);
        return SUCCEEDED(hresult) ? result : Microsoft::WRL::ComPtr<Interface>{};
    }
}
