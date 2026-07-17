#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "DeviceContextHelpers.hpp"
#include "NativeHelpers.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

#include <d3d11.h>
#include <wrl/client.h>

namespace
{
    constexpr std::size_t kMaxClassInstances = 256;

    template<typename Shader, typename Setter>
    [[nodiscard]] bool setShaderBinding(
        const std::uint64_t contextHandle,
        const std::uint64_t shaderHandle,
        const std::vector<std::uint64_t>& classInstanceHandles,
        Setter setter)
    {
        auto& bridge = id3d11::BridgeState::instance();
        if (classInstanceHandles.size() > kMaxClassInstances ||
            (shaderHandle == 0 && !classInstanceHandles.empty()))
        {
            bridge.setLastHresult(E_INVALIDARG);
            return false;
        }

        const auto context = id3d11::acquireContext(contextHandle);
        if (!context)
        {
            return false;
        }

        Microsoft::WRL::ComPtr<Shader> shader;
        if (!id3d11::acquireOptionalContextChild(context.Get(), shaderHandle, shader))
        {
            return false;
        }

        std::vector<Microsoft::WRL::ComPtr<ID3D11ClassInstance>> ownedInstances;
        std::vector<ID3D11ClassInstance*> instances;
        ownedInstances.reserve(classInstanceHandles.size());
        instances.reserve(classInstanceHandles.size());
        for (const std::uint64_t handle : classInstanceHandles)
        {
            if (handle == 0)
            {
                bridge.setLastHresult(E_INVALIDARG);
                return false;
            }

            Microsoft::WRL::ComPtr<ID3D11ClassInstance> instance =
                id3d11::acquireInterface<ID3D11ClassInstance>(handle);
            if (!instance || !id3d11::validateSameDevice(context.Get(), instance.Get()))
            {
                return false;
            }
            ownedInstances.push_back(instance);
            instances.push_back(instance.Get());
        }

        setter(
            context.Get(),
            shader.Get(),
            instances.empty() ? nullptr : instances.data(),
            static_cast<UINT>(instances.size()));
        bridge.setLastHresult(S_OK);
        return true;
    }

    template<typename Shader, typename Getter>
    [[nodiscard]] gm_structs::ID3D11ShaderBinding getShaderBinding(
        const std::uint64_t contextHandle,
        const gm_enums::ID3D11HandleKind shaderKind,
        Getter getter)
    {
        gm_structs::ID3D11ShaderBinding output{};
        const auto context = id3d11::acquireContext(contextHandle);
        if (!context)
        {
            return output;
        }

        Shader* rawShader = nullptr;
        std::array<ID3D11ClassInstance*, kMaxClassInstances> rawInstances{};
        UINT instanceCount = static_cast<UINT>(rawInstances.size());
        getter(context.Get(), &rawShader, rawInstances.data(), &instanceCount);

        Microsoft::WRL::ComPtr<Shader> shader;
        shader.Attach(rawShader);
        bool internFailed = false;
        output.shader = id3d11::internOptionalDeviceChild(shader.Get(), shaderKind);
        internFailed = shader && output.shader == 0;

        const std::size_t safeCount = std::min<std::size_t>(instanceCount, rawInstances.size());
        output.classInstances.reserve(safeCount);
        for (std::size_t index = 0; index < safeCount; ++index)
        {
            Microsoft::WRL::ComPtr<ID3D11ClassInstance> instance;
            instance.Attach(rawInstances[index]);
            const std::uint64_t handle = id3d11::internOptionalDeviceChild(
                instance.Get(),
                gm_enums::ID3D11HandleKind::ClassInstance);
            internFailed = internFailed || (instance && handle == 0);
            output.classInstances.push_back(handle);
        }

        id3d11::BridgeState::instance().setLastHresult(
            instanceCount > rawInstances.size()
                ? E_FAIL
                : (internFailed ? E_OUTOFMEMORY : S_OK));
        return output;
    }
}

#define ID3D11_DEFINE_SHADER_BINDING(stageName, stagePrefix, shaderType, shaderKind) \
    bool id3d11_device_context_##stageName##_set_shader( \
        const std::uint64_t context, \
        const std::uint64_t shader, \
        const std::vector<std::uint64_t>& classInstances) \
    { \
        return setShaderBinding<shaderType>( \
            context, shader, classInstances, \
            [](ID3D11DeviceContext* nativeContext, shaderType* nativeShader, \
                ID3D11ClassInstance* const* instances, const UINT count) \
            { \
                nativeContext->stagePrefix##SetShader(nativeShader, instances, count); \
            }); \
    } \
    gm_structs::ID3D11ShaderBinding id3d11_device_context_##stageName##_get_shader( \
        const std::uint64_t context) \
    { \
        return getShaderBinding<shaderType>( \
            context, gm_enums::ID3D11HandleKind::shaderKind, \
            [](ID3D11DeviceContext* nativeContext, shaderType** nativeShader, \
                ID3D11ClassInstance** instances, UINT* count) \
            { \
                nativeContext->stagePrefix##GetShader(nativeShader, instances, count); \
            }); \
    }

ID3D11_DEFINE_SHADER_BINDING(vs, VS, ID3D11VertexShader, VertexShader)
ID3D11_DEFINE_SHADER_BINDING(hs, HS, ID3D11HullShader, HullShader)
ID3D11_DEFINE_SHADER_BINDING(ds, DS, ID3D11DomainShader, DomainShader)
ID3D11_DEFINE_SHADER_BINDING(gs, GS, ID3D11GeometryShader, GeometryShader)
ID3D11_DEFINE_SHADER_BINDING(ps, PS, ID3D11PixelShader, PixelShader)
ID3D11_DEFINE_SHADER_BINDING(cs, CS, ID3D11ComputeShader, ComputeShader)

#undef ID3D11_DEFINE_SHADER_BINDING
