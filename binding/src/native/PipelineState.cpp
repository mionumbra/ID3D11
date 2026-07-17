#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "DeviceContextHelpers.hpp"

#include <cstdint>
#include <iterator>
#include <vector>

#include <d3d11.h>
#include <wrl/client.h>

namespace
{
    [[nodiscard]] bool validPrimitiveTopology(const std::uint32_t topology) noexcept
    {
        return topology <= static_cast<std::uint32_t>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP) ||
            (topology >= static_cast<std::uint32_t>(D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ) &&
                topology <= static_cast<std::uint32_t>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ)) ||
            (topology >= static_cast<std::uint32_t>(D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST) &&
                topology <= static_cast<std::uint32_t>(D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST));
    }

}

bool id3d11_device_context_ia_set_input_layout(
    const std::uint64_t contextHandle,
    const std::uint64_t inputLayoutHandle)
{
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }

    Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
    if (!id3d11::acquireOptionalContextChild(
        context.Get(),
        inputLayoutHandle,
        inputLayout))
    {
        return false;
    }

    context->IASetInputLayout(inputLayout.Get());
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return true;
}

std::uint64_t id3d11_device_context_ia_get_input_layout(const std::uint64_t contextHandle)
{
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return 0;
    }

    Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
    context->IAGetInputLayout(&inputLayout);
    return id3d11::internOptionalDeviceChild(
        inputLayout.Get(),
        gm_enums::ID3D11HandleKind::InputLayout);
}

bool id3d11_device_context_ia_set_primitive_topology(
    const std::uint64_t contextHandle,
    const gm_enums::ID3D11PrimitiveTopology topology)
{
    auto& bridge = id3d11::BridgeState::instance();
    const std::uint32_t topologyValue = static_cast<std::uint32_t>(topology);
    if (!validPrimitiveTopology(topologyValue))
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }

    context->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(topologyValue));
    bridge.setLastHresult(S_OK);
    return true;
}

gm_enums::ID3D11PrimitiveTopology id3d11_device_context_ia_get_primitive_topology(
    const std::uint64_t contextHandle)
{
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return gm_enums::ID3D11PrimitiveTopology::Undefined;
    }

    D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
    context->IAGetPrimitiveTopology(&topology);
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return static_cast<gm_enums::ID3D11PrimitiveTopology>(topology);
}

bool id3d11_device_context_rs_set_state(
    const std::uint64_t contextHandle,
    const std::uint64_t stateHandle)
{
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }

    Microsoft::WRL::ComPtr<ID3D11RasterizerState> state;
    if (!id3d11::acquireOptionalContextChild(context.Get(), stateHandle, state))
    {
        return false;
    }

    context->RSSetState(state.Get());
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return true;
}

std::uint64_t id3d11_device_context_rs_get_state(const std::uint64_t contextHandle)
{
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return 0;
    }

    Microsoft::WRL::ComPtr<ID3D11RasterizerState> state;
    context->RSGetState(&state);
    return id3d11::internOptionalDeviceChild(
        state.Get(),
        gm_enums::ID3D11HandleKind::RasterizerState);
}

bool id3d11_device_context_om_set_blend_state(
    const std::uint64_t contextHandle,
    const std::uint64_t stateHandle,
    const std::vector<float>& blendFactor,
    const std::uint32_t sampleMask)
{
    auto& bridge = id3d11::BridgeState::instance();
    if (!blendFactor.empty() && blendFactor.size() != 4)
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }

    Microsoft::WRL::ComPtr<ID3D11BlendState> state;
    if (!id3d11::acquireOptionalContextChild(context.Get(), stateHandle, state))
    {
        return false;
    }

    context->OMSetBlendState(
        state.Get(),
        blendFactor.empty() ? nullptr : blendFactor.data(),
        sampleMask);
    bridge.setLastHresult(S_OK);
    return true;
}

gm_structs::ID3D11BlendStateBinding id3d11_device_context_om_get_blend_state(
    const std::uint64_t contextHandle)
{
    gm_structs::ID3D11BlendStateBinding output{};
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return output;
    }

    Microsoft::WRL::ComPtr<ID3D11BlendState> state;
    float blendFactor[4]{};
    context->OMGetBlendState(&state, blendFactor, &output.sampleMask);
    output.blendFactor.assign(std::begin(blendFactor), std::end(blendFactor));
    output.state = id3d11::internOptionalDeviceChild(
        state.Get(),
        gm_enums::ID3D11HandleKind::BlendState);
    return output;
}

bool id3d11_device_context_om_set_depth_stencil_state(
    const std::uint64_t contextHandle,
    const std::uint64_t stateHandle,
    const std::uint32_t stencilRef)
{
    auto& bridge = id3d11::BridgeState::instance();
    if (stencilRef > 0xffU)
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> state;
    if (!id3d11::acquireOptionalContextChild(context.Get(), stateHandle, state))
    {
        return false;
    }

    context->OMSetDepthStencilState(state.Get(), stencilRef);
    bridge.setLastHresult(S_OK);
    return true;
}

gm_structs::ID3D11DepthStencilStateBinding
id3d11_device_context_om_get_depth_stencil_state(const std::uint64_t contextHandle)
{
    gm_structs::ID3D11DepthStencilStateBinding output{};
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return output;
    }

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> state;
    context->OMGetDepthStencilState(&state, &output.stencilRef);
    output.state = id3d11::internOptionalDeviceChild(
        state.Get(),
        gm_enums::ID3D11HandleKind::DepthStencilState);
    return output;
}

bool id3d11_device_context_set_predication(
    const std::uint64_t contextHandle,
    const std::uint64_t predicateHandle,
    const bool predicateValue)
{
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }

    Microsoft::WRL::ComPtr<ID3D11Predicate> predicate;
    if (!id3d11::acquireOptionalContextChild(context.Get(), predicateHandle, predicate))
    {
        return false;
    }

    context->SetPredication(predicate.Get(), predicateValue);
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return true;
}

gm_structs::ID3D11PredicationBinding id3d11_device_context_get_predication(
    const std::uint64_t contextHandle)
{
    gm_structs::ID3D11PredicationBinding output{};
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return output;
    }

    Microsoft::WRL::ComPtr<ID3D11Predicate> predicate;
    BOOL predicateValue = FALSE;
    context->GetPredication(&predicate, &predicateValue);
    output.predicateValue = predicateValue != FALSE;
    output.predicate = id3d11::internOptionalDeviceChild(
        predicate.Get(),
        gm_enums::ID3D11HandleKind::Predicate);
    return output;
}
