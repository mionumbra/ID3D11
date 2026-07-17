#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "DeviceContextHelpers.hpp"

#include <cstdint>
#include <vector>

#include <d3d11.h>
#include <wrl/client.h>

namespace
{
    [[nodiscard]] bool validSlotRange(
        const std::uint32_t startSlot,
        const std::size_t count,
        const std::uint32_t limit) noexcept
    {
        return startSlot < limit && count <= static_cast<std::size_t>(limit - startSlot);
    }

    template<typename Interface, typename Setter>
    [[nodiscard]] bool setBindings(
        const std::uint64_t contextHandle,
        const std::uint32_t startSlot,
        const std::vector<std::uint64_t>& handles,
        const std::uint32_t limit,
        Setter setter)
    {
        auto& bridge = id3d11::BridgeState::instance();
        if (!validSlotRange(startSlot, handles.size(), limit))
        {
            bridge.setLastHresult(E_INVALIDARG);
            return false;
        }

        const auto context = id3d11::acquireContext(contextHandle);
        if (!context)
        {
            return false;
        }

        std::vector<Microsoft::WRL::ComPtr<Interface>> ownedObjects;
        std::vector<Interface*> objects;
        ownedObjects.reserve(handles.size());
        objects.reserve(handles.size());
        for (const std::uint64_t handle : handles)
        {
            Microsoft::WRL::ComPtr<Interface> object;
            if (!id3d11::acquireOptionalContextChild(context.Get(), handle, object))
            {
                return false;
            }
            ownedObjects.push_back(object);
            objects.push_back(object.Get());
        }

        setter(
            context.Get(),
            startSlot,
            static_cast<UINT>(objects.size()),
            objects.empty() ? nullptr : objects.data());
        bridge.setLastHresult(S_OK);
        return true;
    }

    template<typename Interface, typename Getter>
    [[nodiscard]] std::vector<std::uint64_t> getBindings(
        const std::uint64_t contextHandle,
        const std::uint32_t startSlot,
        const std::uint32_t count,
        const std::uint32_t limit,
        const gm_enums::ID3D11HandleKind kind,
        Getter getter)
    {
        std::vector<std::uint64_t> output;
        auto& bridge = id3d11::BridgeState::instance();
        if (!validSlotRange(startSlot, count, limit))
        {
            bridge.setLastHresult(E_INVALIDARG);
            return output;
        }

        const auto context = id3d11::acquireContext(contextHandle);
        if (!context)
        {
            return output;
        }

        std::vector<Interface*> objects(count, nullptr);
        getter(
            context.Get(),
            startSlot,
            count,
            objects.empty() ? nullptr : objects.data());

        bool internFailed = false;
        output.reserve(count);
        for (Interface* rawObject : objects)
        {
            Microsoft::WRL::ComPtr<Interface> object;
            object.Attach(rawObject);
            const std::uint64_t handle = id3d11::internOptionalDeviceChild(object.Get(), kind);
            internFailed = internFailed || (object && handle == 0);
            output.push_back(handle);
        }
        bridge.setLastHresult(internFailed ? E_OUTOFMEMORY : S_OK);
        return output;
    }
}

#define ID3D11_DEFINE_STAGE_BINDINGS(stageName, stagePrefix) \
    bool id3d11_device_context_##stageName##_set_constant_buffers( \
        const std::uint64_t context, \
        const std::uint32_t startSlot, \
        const std::vector<std::uint64_t>& buffers) \
    { \
        return setBindings<ID3D11Buffer>( \
            context, startSlot, buffers, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, \
            [](ID3D11DeviceContext* nativeContext, const UINT slot, const UINT count, \
                ID3D11Buffer* const* objects) \
            { \
                nativeContext->stagePrefix##SetConstantBuffers(slot, count, objects); \
            }); \
    } \
    std::vector<std::uint64_t> id3d11_device_context_##stageName##_get_constant_buffers( \
        const std::uint64_t context, \
        const std::uint32_t startSlot, \
        const std::uint32_t count) \
    { \
        return getBindings<ID3D11Buffer>( \
            context, startSlot, count, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, \
            gm_enums::ID3D11HandleKind::Buffer, \
            [](ID3D11DeviceContext* nativeContext, const UINT slot, const UINT objectCount, \
                ID3D11Buffer** objects) \
            { \
                nativeContext->stagePrefix##GetConstantBuffers(slot, objectCount, objects); \
            }); \
    } \
    bool id3d11_device_context_##stageName##_set_shader_resources( \
        const std::uint64_t context, \
        const std::uint32_t startSlot, \
        const std::vector<std::uint64_t>& views) \
    { \
        return setBindings<ID3D11ShaderResourceView>( \
            context, startSlot, views, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, \
            [](ID3D11DeviceContext* nativeContext, const UINT slot, const UINT count, \
                ID3D11ShaderResourceView* const* objects) \
            { \
                nativeContext->stagePrefix##SetShaderResources(slot, count, objects); \
            }); \
    } \
    std::vector<std::uint64_t> id3d11_device_context_##stageName##_get_shader_resources( \
        const std::uint64_t context, \
        const std::uint32_t startSlot, \
        const std::uint32_t count) \
    { \
        return getBindings<ID3D11ShaderResourceView>( \
            context, startSlot, count, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, \
            gm_enums::ID3D11HandleKind::ShaderResourceView, \
            [](ID3D11DeviceContext* nativeContext, const UINT slot, const UINT objectCount, \
                ID3D11ShaderResourceView** objects) \
            { \
                nativeContext->stagePrefix##GetShaderResources(slot, objectCount, objects); \
            }); \
    } \
    bool id3d11_device_context_##stageName##_set_samplers( \
        const std::uint64_t context, \
        const std::uint32_t startSlot, \
        const std::vector<std::uint64_t>& samplers) \
    { \
        return setBindings<ID3D11SamplerState>( \
            context, startSlot, samplers, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, \
            [](ID3D11DeviceContext* nativeContext, const UINT slot, const UINT count, \
                ID3D11SamplerState* const* objects) \
            { \
                nativeContext->stagePrefix##SetSamplers(slot, count, objects); \
            }); \
    } \
    std::vector<std::uint64_t> id3d11_device_context_##stageName##_get_samplers( \
        const std::uint64_t context, \
        const std::uint32_t startSlot, \
        const std::uint32_t count) \
    { \
        return getBindings<ID3D11SamplerState>( \
            context, startSlot, count, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, \
            gm_enums::ID3D11HandleKind::SamplerState, \
            [](ID3D11DeviceContext* nativeContext, const UINT slot, const UINT objectCount, \
                ID3D11SamplerState** objects) \
            { \
                nativeContext->stagePrefix##GetSamplers(slot, objectCount, objects); \
            }); \
    }

ID3D11_DEFINE_STAGE_BINDINGS(vs, VS)
ID3D11_DEFINE_STAGE_BINDINGS(hs, HS)
ID3D11_DEFINE_STAGE_BINDINGS(ds, DS)
ID3D11_DEFINE_STAGE_BINDINGS(gs, GS)
ID3D11_DEFINE_STAGE_BINDINGS(ps, PS)
ID3D11_DEFINE_STAGE_BINDINGS(cs, CS)

#undef ID3D11_DEFINE_STAGE_BINDINGS
