#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "DeviceContextHelpers.hpp"
#include "HandleRegistry.hpp"
#include "NativeHelpers.hpp"

#include <algorithm>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include <d3d11.h>
#include <wrl/client.h>

namespace
{
    using CreateResult = gm_structs::ID3D11CreateHandleResult;

    constexpr std::size_t kMaxClassNameBytes = 1024U * 1024U;

    [[nodiscard]] CreateResult failedCreate(const HRESULT hresult) noexcept
    {
        id3d11::BridgeState::instance().setLastHresult(hresult);
        return {
            .hresult = static_cast<std::int32_t>(hresult),
            .handle = 0,
        };
    }

    [[nodiscard]] CreateResult finishCreate(
        const HRESULT hresult,
        ID3D11ClassInstance* instance) noexcept
    {
        HRESULT finalResult = hresult;
        std::uint64_t handle = 0;
        if (SUCCEEDED(finalResult))
        {
            handle = id3d11::HandleRegistry::instance().intern(
                instance,
                gm_enums::ID3D11HandleKind::ClassInstance);
            if (handle == 0)
            {
                finalResult = E_OUTOFMEMORY;
            }
        }

        id3d11::BridgeState::instance().setLastHresult(finalResult);
        return {
            .hresult = static_cast<std::int32_t>(finalResult),
            .handle = handle,
        };
    }

    [[nodiscard]] bool validClassName(const std::string_view name) noexcept
    {
        return !name.empty() &&
            name.size() <= kMaxClassNameBytes &&
            std::find(name.begin(), name.end(), '\0') == name.end();
    }

    [[nodiscard]] gm_structs::ID3D11ClassInstanceDesc fromNative(
        const D3D11_CLASS_INSTANCE_DESC& desc) noexcept
    {
        return {
            .instanceId = desc.InstanceId,
            .instanceIndex = desc.InstanceIndex,
            .typeId = desc.TypeId,
            .constantBuffer = desc.ConstantBuffer,
            .baseConstantBufferOffset = desc.BaseConstantBufferOffset,
            .baseTexture = desc.BaseTexture,
            .baseSampler = desc.BaseSampler,
            .created = desc.Created != FALSE,
        };
    }

    template<typename Reader>
    [[nodiscard]] std::string readClassName(
        ID3D11ClassInstance* instance,
        Reader reader)
    {
        SIZE_T length = 0;
        reader(instance, nullptr, &length);
        if (length > kMaxClassNameBytes)
        {
            id3d11::BridgeState::instance().setLastHresult(E_OUTOFMEMORY);
            return {};
        }
        if (length == 0)
        {
            id3d11::BridgeState::instance().setLastHresult(S_OK);
            return {};
        }

        std::vector<char> bytes(length + 1U, '\0');
        SIZE_T capacity = bytes.size();
        reader(instance, bytes.data(), &capacity);
        const auto terminator = std::find(bytes.begin(), bytes.end(), '\0');
        id3d11::BridgeState::instance().setLastHresult(S_OK);
        return std::string(bytes.begin(), terminator);
    }
}

gm_structs::ID3D11CreateHandleResult id3d11_class_linkage_get_class_instance(
    const std::uint64_t linkageHandle,
    const std::string_view classInstanceName,
    const std::uint32_t instanceIndex)
{
    if (!validClassName(classInstanceName))
    {
        return failedCreate(E_INVALIDARG);
    }

    const auto linkage = id3d11::acquireInterface<ID3D11ClassLinkage>(linkageHandle);
    if (!linkage)
    {
        return failedCreate(E_HANDLE);
    }

    const std::string name(classInstanceName);
    Microsoft::WRL::ComPtr<ID3D11ClassInstance> instance;
    const HRESULT hresult = linkage->GetClassInstance(name.c_str(), instanceIndex, &instance);
    return finishCreate(hresult, instance.Get());
}

gm_structs::ID3D11CreateHandleResult id3d11_class_linkage_create_class_instance(
    const std::uint64_t linkageHandle,
    const std::string_view classTypeName,
    const std::uint32_t constantBufferOffset,
    const std::uint32_t constantVectorOffset,
    const std::uint32_t textureOffset,
    const std::uint32_t samplerOffset)
{
    if (!validClassName(classTypeName))
    {
        return failedCreate(E_INVALIDARG);
    }

    const auto linkage = id3d11::acquireInterface<ID3D11ClassLinkage>(linkageHandle);
    if (!linkage)
    {
        return failedCreate(E_HANDLE);
    }

    const std::string name(classTypeName);
    Microsoft::WRL::ComPtr<ID3D11ClassInstance> instance;
    const HRESULT hresult = linkage->CreateClassInstance(
        name.c_str(),
        constantBufferOffset,
        constantVectorOffset,
        textureOffset,
        samplerOffset,
        &instance);
    return finishCreate(hresult, instance.Get());
}

std::uint64_t id3d11_class_instance_get_class_linkage(
    const std::uint64_t instanceHandle)
{
    const auto instance = id3d11::acquireInterface<ID3D11ClassInstance>(instanceHandle);
    if (!instance)
    {
        return 0;
    }

    Microsoft::WRL::ComPtr<ID3D11ClassLinkage> linkage;
    instance->GetClassLinkage(&linkage);
    return id3d11::internOptionalDeviceChild(
        linkage.Get(),
        gm_enums::ID3D11HandleKind::ClassLinkage);
}

gm_structs::ID3D11ClassInstanceDesc id3d11_class_instance_get_desc(
    const std::uint64_t instanceHandle)
{
    const auto instance = id3d11::acquireInterface<ID3D11ClassInstance>(instanceHandle);
    if (!instance)
    {
        return {};
    }

    D3D11_CLASS_INSTANCE_DESC desc{};
    instance->GetDesc(&desc);
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return fromNative(desc);
}

std::string id3d11_class_instance_get_instance_name(const std::uint64_t instanceHandle)
{
    const auto instance = id3d11::acquireInterface<ID3D11ClassInstance>(instanceHandle);
    if (!instance)
    {
        return {};
    }

    return readClassName(
        instance.Get(),
        [](ID3D11ClassInstance* nativeInstance, char* name, SIZE_T* length)
        {
            nativeInstance->GetInstanceName(name, length);
        });
}

std::string id3d11_class_instance_get_type_name(const std::uint64_t instanceHandle)
{
    const auto instance = id3d11::acquireInterface<ID3D11ClassInstance>(instanceHandle);
    if (!instance)
    {
        return {};
    }

    return readClassName(
        instance.Get(),
        [](ID3D11ClassInstance* nativeInstance, char* name, SIZE_T* length)
        {
            nativeInstance->GetTypeName(name, length);
        });
}
