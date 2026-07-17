#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"

#include <d3d11.h>
#include <dxgiformat.h>
#include <wrl/client.h>

namespace
{
    Microsoft::WRL::ComPtr<ID3D11Device> acquireDevice(const std::uint64_t handle) noexcept
    {
        auto& state = id3d11::BridgeState::instance();
        const Microsoft::WRL::ComPtr<IUnknown> unknown =
            id3d11::HandleRegistry::instance().acquire(
                handle,
                gm_enums::ID3D11HandleKind::Device);
        if (!unknown)
        {
            state.setLastHresult(E_HANDLE);
            return {};
        }

        Microsoft::WRL::ComPtr<ID3D11Device> device;
        const HRESULT queryResult = unknown.As(&device);
        state.setLastHresult(queryResult);
        return SUCCEEDED(queryResult) ? device : Microsoft::WRL::ComPtr<ID3D11Device>{};
    }
}

gm_enums::ID3D11FeatureLevel id3d11_device_get_feature_level(const std::uint64_t deviceHandle)
{
    const auto device = acquireDevice(deviceHandle);
    if (!device)
    {
        return static_cast<gm_enums::ID3D11FeatureLevel>(0);
    }

    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return static_cast<gm_enums::ID3D11FeatureLevel>(device->GetFeatureLevel());
}

std::uint32_t id3d11_device_get_creation_flags(const std::uint64_t deviceHandle)
{
    const auto device = acquireDevice(deviceHandle);
    if (!device)
    {
        return 0;
    }

    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return device->GetCreationFlags();
}

std::int32_t id3d11_device_get_removed_reason(const std::uint64_t deviceHandle)
{
    const auto device = acquireDevice(deviceHandle);
    if (!device)
    {
        return E_HANDLE;
    }

    const HRESULT result = device->GetDeviceRemovedReason();
    id3d11::BridgeState::instance().setLastHresult(result);
    return static_cast<std::int32_t>(result);
}

std::uint32_t id3d11_device_get_exception_mode(const std::uint64_t deviceHandle)
{
    const auto device = acquireDevice(deviceHandle);
    if (!device)
    {
        return 0;
    }

    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return device->GetExceptionMode();
}

std::int32_t id3d11_device_set_exception_mode(
    const std::uint64_t deviceHandle,
    const std::uint32_t raiseFlags)
{
    const auto device = acquireDevice(deviceHandle);
    if (!device)
    {
        return E_HANDLE;
    }

    const HRESULT result = device->SetExceptionMode(raiseFlags);
    id3d11::BridgeState::instance().setLastHresult(result);
    return static_cast<std::int32_t>(result);
}

std::uint64_t id3d11_device_get_immediate_context(const std::uint64_t deviceHandle)
{
    const auto device = acquireDevice(deviceHandle);
    if (!device)
    {
        return 0;
    }

    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    device->GetImmediateContext(&context);
    if (!context)
    {
        id3d11::BridgeState::instance().setLastHresult(E_FAIL);
        return 0;
    }

    const std::uint64_t contextHandle = id3d11::HandleRegistry::instance().intern(
        context.Get(),
        gm_enums::ID3D11HandleKind::DeviceContext);
    id3d11::BridgeState::instance().setLastHresult(contextHandle == 0 ? E_OUTOFMEMORY : S_OK);
    return contextHandle;
}

gm_structs::ID3D11FormatSupportResult id3d11_device_check_format_support(
    const std::uint64_t deviceHandle,
    const std::uint32_t format)
{
    gm_structs::ID3D11FormatSupportResult output{};
    const auto device = acquireDevice(deviceHandle);
    if (!device)
    {
        output.hresult = E_HANDLE;
        return output;
    }

    const HRESULT result = device->CheckFormatSupport(
        static_cast<DXGI_FORMAT>(format),
        &output.support);
    output.hresult = static_cast<std::int32_t>(result);
    id3d11::BridgeState::instance().setLastHresult(result);
    return output;
}

gm_structs::ID3D11MultisampleQualityResult id3d11_device_check_multisample_quality_levels(
    const std::uint64_t deviceHandle,
    const std::uint32_t format,
    const std::uint32_t sampleCount)
{
    gm_structs::ID3D11MultisampleQualityResult output{};
    const auto device = acquireDevice(deviceHandle);
    if (!device)
    {
        output.hresult = E_HANDLE;
        return output;
    }

    const HRESULT result = device->CheckMultisampleQualityLevels(
        static_cast<DXGI_FORMAT>(format),
        sampleCount,
        &output.qualityLevels);
    output.hresult = static_cast<std::int32_t>(result);
    id3d11::BridgeState::instance().setLastHresult(result);
    return output;
}

gm_structs::ID3D11CounterInfo id3d11_device_get_counter_info(const std::uint64_t deviceHandle)
{
    gm_structs::ID3D11CounterInfo output{};
    const auto device = acquireDevice(deviceHandle);
    if (!device)
    {
        return output;
    }

    D3D11_COUNTER_INFO info{};
    device->CheckCounterInfo(&info);
    output.lastDeviceDependentCounter = static_cast<std::uint32_t>(info.LastDeviceDependentCounter);
    output.numSimultaneousCounters = info.NumSimultaneousCounters;
    output.numDetectableParallelUnits = info.NumDetectableParallelUnits;
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}
