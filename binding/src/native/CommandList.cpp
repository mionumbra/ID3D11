#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "DeviceContextHelpers.hpp"
#include "HandleRegistry.hpp"
#include "NativeHelpers.hpp"

#include <d3d11.h>
#include <wrl/client.h>

namespace
{
    Microsoft::WRL::ComPtr<ID3D11Device> acquireDevice(const std::uint64_t handle) noexcept
    {
        return id3d11::acquireInterface<ID3D11Device>(
            handle,
            gm_enums::ID3D11HandleKind::Device);
    }
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_deferred_context(
    const std::uint64_t deviceHandle,
    const std::uint32_t contextFlags)
{
    gm_structs::ID3D11CreateHandleResult output{};
    auto& bridge = id3d11::BridgeState::instance();
    if (contextFlags != 0)
    {
        output.hresult = E_INVALIDARG;
        bridge.setLastHresult(E_INVALIDARG);
        return output;
    }

    const auto device = acquireDevice(deviceHandle);
    if (!device)
    {
        output.hresult = E_HANDLE;
        return output;
    }

    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deferred;
    const HRESULT result = device->CreateDeferredContext(contextFlags, &deferred);
    output.hresult = static_cast<std::int32_t>(result);
    bridge.setLastHresult(result);
    if (FAILED(result) || !deferred)
    {
        return output;
    }

    output.handle = id3d11::HandleRegistry::instance().intern(
        deferred.Get(),
        gm_enums::ID3D11HandleKind::DeviceContext);
    if (output.handle == 0)
    {
        output.hresult = E_OUTOFMEMORY;
        bridge.setLastHresult(E_OUTOFMEMORY);
    }
    return output;
}

gm_structs::ID3D11CreateHandleResult id3d11_device_context_finish_command_list(
    const std::uint64_t contextHandle,
    const bool restoreDeferredContextState)
{
    gm_structs::ID3D11CreateHandleResult output{};
    auto& bridge = id3d11::BridgeState::instance();
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        output.hresult = static_cast<std::int32_t>(bridge.lastHresult());
        return output;
    }

    if (context->GetType() != D3D11_DEVICE_CONTEXT_DEFERRED)
    {
        output.hresult = E_INVALIDARG;
        bridge.setLastHresult(E_INVALIDARG);
        return output;
    }

    Microsoft::WRL::ComPtr<ID3D11CommandList> commandList;
    const HRESULT result = context->FinishCommandList(
        restoreDeferredContextState ? TRUE : FALSE,
        &commandList);
    output.hresult = static_cast<std::int32_t>(result);
    bridge.setLastHresult(result);
    if (FAILED(result) || !commandList)
    {
        return output;
    }

    output.handle = id3d11::HandleRegistry::instance().intern(
        commandList.Get(),
        gm_enums::ID3D11HandleKind::CommandList);
    if (output.handle == 0)
    {
        output.hresult = E_OUTOFMEMORY;
        bridge.setLastHresult(E_OUTOFMEMORY);
    }
    return output;
}

bool id3d11_device_context_execute_command_list(
    const std::uint64_t contextHandle,
    const std::uint64_t commandListHandle,
    const bool restoreContextState)
{
    auto& bridge = id3d11::BridgeState::instance();
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11CommandList> commandList;
    if (!id3d11::acquireContextAndChild(
            contextHandle,
            commandListHandle,
            context,
            commandList))
    {
        return false;
    }

    // Execute is only valid on the immediate context.
    if (context->GetType() != D3D11_DEVICE_CONTEXT_IMMEDIATE)
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    context->ExecuteCommandList(
        commandList.Get(),
        restoreContextState ? TRUE : FALSE);
    bridge.setLastHresult(S_OK);
    return true;
}

std::uint32_t id3d11_device_context_get_type(const std::uint64_t contextHandle)
{
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return static_cast<std::uint32_t>(D3D11_DEVICE_CONTEXT_IMMEDIATE);
    }

    const D3D11_DEVICE_CONTEXT_TYPE type = context->GetType();
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return static_cast<std::uint32_t>(type);
}

std::uint32_t id3d11_device_context_get_context_flags(const std::uint64_t contextHandle)
{
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return 0;
    }

    const UINT flags = context->GetContextFlags();
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return flags;
}

std::uint32_t id3d11_command_list_get_context_flags(const std::uint64_t commandListHandle)
{
    const auto commandList = id3d11::acquireInterface<ID3D11CommandList>(
        commandListHandle,
        gm_enums::ID3D11HandleKind::CommandList);
    if (!commandList)
    {
        return 0;
    }

    const UINT flags = commandList->GetContextFlags();
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return flags;
}