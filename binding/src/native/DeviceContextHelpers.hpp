#pragma once

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"
#include "NativeHelpers.hpp"

#include <cstdint>

#include <Windows.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace id3d11
{
    [[nodiscard]] inline bool sameComIdentity(IUnknown* left, IUnknown* right) noexcept
    {
        if (left == nullptr || right == nullptr)
        {
            return false;
        }

        Microsoft::WRL::ComPtr<IUnknown> leftIdentity;
        Microsoft::WRL::ComPtr<IUnknown> rightIdentity;
        const HRESULT leftResult = left->QueryInterface(IID_PPV_ARGS(&leftIdentity));
        const HRESULT rightResult = right->QueryInterface(IID_PPV_ARGS(&rightIdentity));
        return SUCCEEDED(leftResult) && SUCCEEDED(rightResult) &&
            leftIdentity.Get() == rightIdentity.Get();
    }

    [[nodiscard]] inline bool validateContextThread(ID3D11DeviceContext* context) noexcept
    {
        auto& state = BridgeState::instance();
        const Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediateContext = state.context();
        if (sameComIdentity(context, immediateContext.Get()) &&
            GetCurrentThreadId() != state.ownerThreadId())
        {
            state.setLastHresult(RPC_E_WRONG_THREAD);
            return false;
        }
        return true;
    }

    [[nodiscard]] inline Microsoft::WRL::ComPtr<ID3D11DeviceContext> acquireContext(
        const std::uint64_t contextHandle) noexcept
    {
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> context =
            acquireInterface<ID3D11DeviceContext>(contextHandle);
        return context && validateContextThread(context.Get())
            ? context
            : Microsoft::WRL::ComPtr<ID3D11DeviceContext>{};
    }

    [[nodiscard]] inline bool validateSameDevice(
        ID3D11DeviceContext* context,
        ID3D11DeviceChild* child) noexcept
    {
        Microsoft::WRL::ComPtr<ID3D11Device> contextDevice;
        Microsoft::WRL::ComPtr<ID3D11Device> childDevice;
        context->GetDevice(&contextDevice);
        child->GetDevice(&childDevice);
        if (!sameComIdentity(contextDevice.Get(), childDevice.Get()))
        {
            BridgeState::instance().setLastHresult(E_INVALIDARG);
            return false;
        }
        return true;
    }

    template<typename Interface>
    [[nodiscard]] bool acquireContextAndChild(
        const std::uint64_t contextHandle,
        const std::uint64_t childHandle,
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>& context,
        Microsoft::WRL::ComPtr<Interface>& child) noexcept
    {
        context = acquireContext(contextHandle);
        if (!context)
        {
            return false;
        }

        child = acquireInterface<Interface>(childHandle);
        return child && validateSameDevice(context.Get(), child.Get());
    }

    template<typename Interface>
    [[nodiscard]] bool acquireOptionalContextChild(
        ID3D11DeviceContext* context,
        const std::uint64_t childHandle,
        Microsoft::WRL::ComPtr<Interface>& child) noexcept
    {
        child.Reset();
        if (childHandle == 0)
        {
            return true;
        }

        child = acquireInterface<Interface>(childHandle);
        return child && validateSameDevice(context, child.Get());
    }

    template<typename Interface>
    [[nodiscard]] std::uint64_t internOptionalDeviceChild(
        Interface* object,
        const gm_enums::ID3D11HandleKind kind) noexcept
    {
        if (object == nullptr)
        {
            BridgeState::instance().setLastHresult(S_OK);
            return 0;
        }

        const std::uint64_t handle = HandleRegistry::instance().intern(object, kind);
        BridgeState::instance().setLastHresult(handle == 0 ? E_OUTOFMEMORY : S_OK);
        return handle;
    }
}
