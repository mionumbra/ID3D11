#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"
#include "NativeHelpers.hpp"

#include <d3d11.h>
#include <wrl/client.h>

#include <cstdint>
#include <cstdio>
#include <string>
#include <string_view>
#include <vector>

namespace
{
    // WKPDID_D3DDebugObjectName — defined locally to avoid dxguid.lib dependency.
    constexpr GUID kDebugObjectNameGuid{
        0x429b8c22,
        0x9188,
        0x4b0c,
        {0x87, 0x42, 0xac, 0xb0, 0xbf, 0x85, 0xc2, 0x00}};

    [[nodiscard]] bool parseGuid(const std::string_view text, GUID& outGuid) noexcept
    {
        std::string cleaned;
        cleaned.reserve(text.size());
        for (const char ch : text)
        {
            if (ch == '{' || ch == '}' || ch == '(' || ch == ')')
            {
                continue;
            }
            cleaned.push_back(ch);
        }

        unsigned int data1 = 0;
        unsigned int data2 = 0;
        unsigned int data3 = 0;
        unsigned int b0 = 0;
        unsigned int b1 = 0;
        unsigned int b2 = 0;
        unsigned int b3 = 0;
        unsigned int b4 = 0;
        unsigned int b5 = 0;
        unsigned int b6 = 0;
        unsigned int b7 = 0;
        if (std::sscanf(
                cleaned.c_str(),
                "%8x-%4x-%4x-%2x%2x-%2x%2x%2x%2x%2x%2x",
                &data1,
                &data2,
                &data3,
                &b0,
                &b1,
                &b2,
                &b3,
                &b4,
                &b5,
                &b6,
                &b7) != 11)
        {
            return false;
        }

        outGuid.Data1 = static_cast<unsigned long>(data1);
        outGuid.Data2 = static_cast<unsigned short>(data2);
        outGuid.Data3 = static_cast<unsigned short>(data3);
        outGuid.Data4[0] = static_cast<unsigned char>(b0);
        outGuid.Data4[1] = static_cast<unsigned char>(b1);
        outGuid.Data4[2] = static_cast<unsigned char>(b2);
        outGuid.Data4[3] = static_cast<unsigned char>(b3);
        outGuid.Data4[4] = static_cast<unsigned char>(b4);
        outGuid.Data4[5] = static_cast<unsigned char>(b5);
        outGuid.Data4[6] = static_cast<unsigned char>(b6);
        outGuid.Data4[7] = static_cast<unsigned char>(b7);
        return true;
    }
}

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

bool id3d11_device_child_set_debug_name(
    const std::uint64_t deviceChild,
    const std::string_view name)
{
    auto& bridge = id3d11::BridgeState::instance();
    if (name.size() > 1024)
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    const auto child = id3d11::acquireInterface<ID3D11DeviceChild>(deviceChild);
    if (!child)
    {
        return false;
    }

    const HRESULT result = child->SetPrivateData(
        kDebugObjectNameGuid,
        static_cast<UINT>(name.size()),
        name.empty() ? nullptr : name.data());
    bridge.setLastHresult(result);
    return SUCCEEDED(result);
}

std::string id3d11_device_child_get_debug_name(const std::uint64_t deviceChild)
{
    auto& bridge = id3d11::BridgeState::instance();
    const auto child = id3d11::acquireInterface<ID3D11DeviceChild>(deviceChild);
    if (!child)
    {
        return {};
    }

    UINT size = 0;
    HRESULT result = child->GetPrivateData(kDebugObjectNameGuid, &size, nullptr);
    if (result == DXGI_ERROR_NOT_FOUND || size == 0)
    {
        bridge.setLastHresult(S_OK);
        return {};
    }
    if (FAILED(result) && result != DXGI_ERROR_MORE_DATA)
    {
        bridge.setLastHresult(result);
        return {};
    }
    if (size > 4096)
    {
        bridge.setLastHresult(E_OUTOFMEMORY);
        return {};
    }

    std::vector<char> bytes(size);
    result = child->GetPrivateData(kDebugObjectNameGuid, &size, bytes.data());
    bridge.setLastHresult(result);
    if (FAILED(result))
    {
        return {};
    }

    return std::string(bytes.data(), bytes.data() + size);
}

bool id3d11_device_child_set_private_data(
    const std::uint64_t deviceChild,
    const std::string_view guidText,
    const gm::wire::GMBuffer data)
{
    auto& bridge = id3d11::BridgeState::instance();
    GUID guid{};
    if (!parseGuid(guidText, guid))
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }
    if (data.data() == nullptr && data.length() != 0)
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }
    if (data.length() > 65536)
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    const auto child = id3d11::acquireInterface<ID3D11DeviceChild>(deviceChild);
    if (!child)
    {
        return false;
    }

    const HRESULT result = child->SetPrivateData(
        guid,
        static_cast<UINT>(data.length()),
        data.length() == 0 ? nullptr : data.data());
    bridge.setLastHresult(result);
    return SUCCEEDED(result);
}

std::int32_t id3d11_device_child_get_private_data(
    const std::uint64_t deviceChild,
    const std::string_view guidText,
    const gm::wire::GMBuffer data)
{
    auto& bridge = id3d11::BridgeState::instance();
    GUID guid{};
    if (!parseGuid(guidText, guid))
    {
        bridge.setLastHresult(E_INVALIDARG);
        return static_cast<std::int32_t>(E_INVALIDARG);
    }
    if (data.data() == nullptr && data.length() != 0)
    {
        bridge.setLastHresult(E_INVALIDARG);
        return static_cast<std::int32_t>(E_INVALIDARG);
    }

    const auto child = id3d11::acquireInterface<ID3D11DeviceChild>(deviceChild);
    if (!child)
    {
        return static_cast<std::int32_t>(bridge.lastHresult());
    }

    UINT size = static_cast<UINT>(data.length());
    const HRESULT result = child->GetPrivateData(
        guid,
        &size,
        data.length() == 0 ? nullptr : data.data());
    bridge.setLastHresult(result);
    if (SUCCEEDED(result))
    {
        return static_cast<std::int32_t>(size);
    }
    if (result == DXGI_ERROR_MORE_DATA)
    {
        return static_cast<std::int32_t>(size);
    }
    return static_cast<std::int32_t>(result);
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