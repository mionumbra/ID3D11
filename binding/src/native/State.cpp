#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"
#include "NativeHelpers.hpp"

#include <cstdint>

#include <d3d11.h>
#include <wrl/client.h>

namespace
{
    using CreateResult = gm_structs::ID3D11CreateHandleResult;

    [[nodiscard]] CreateResult failedResult(const HRESULT hresult) noexcept
    {
        id3d11::BridgeState::instance().setLastHresult(hresult);
        return {
            .hresult = static_cast<std::int32_t>(hresult),
            .handle = 0,
        };
    }

    template<typename State>
    [[nodiscard]] CreateResult finishCreate(
        const HRESULT hresult,
        State* state,
        const gm_enums::ID3D11HandleKind kind) noexcept
    {
        HRESULT finalResult = hresult;
        std::uint64_t handle = 0;
        if (SUCCEEDED(finalResult))
        {
            handle = id3d11::HandleRegistry::instance().intern(state, kind);
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

    [[nodiscard]] D3D11_SAMPLER_DESC toNative(const gm_structs::ID3D11SamplerDesc& desc) noexcept
    {
        D3D11_SAMPLER_DESC output{};
        output.Filter = static_cast<D3D11_FILTER>(desc.filter);
        output.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(desc.addressU);
        output.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(desc.addressV);
        output.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(desc.addressW);
        output.MipLODBias = desc.mipLodBias;
        output.MaxAnisotropy = desc.maxAnisotropy;
        output.ComparisonFunc = static_cast<D3D11_COMPARISON_FUNC>(desc.comparisonFunc);
        output.BorderColor[0] = desc.borderColorR;
        output.BorderColor[1] = desc.borderColorG;
        output.BorderColor[2] = desc.borderColorB;
        output.BorderColor[3] = desc.borderColorA;
        output.MinLOD = desc.minLod;
        output.MaxLOD = desc.maxLod;
        return output;
    }

    [[nodiscard]] gm_structs::ID3D11SamplerDesc fromNative(const D3D11_SAMPLER_DESC& desc) noexcept
    {
        return {
            .filter = static_cast<std::uint32_t>(desc.Filter),
            .addressU = static_cast<std::uint32_t>(desc.AddressU),
            .addressV = static_cast<std::uint32_t>(desc.AddressV),
            .addressW = static_cast<std::uint32_t>(desc.AddressW),
            .mipLodBias = desc.MipLODBias,
            .maxAnisotropy = desc.MaxAnisotropy,
            .comparisonFunc = static_cast<std::uint32_t>(desc.ComparisonFunc),
            .borderColorR = desc.BorderColor[0],
            .borderColorG = desc.BorderColor[1],
            .borderColorB = desc.BorderColor[2],
            .borderColorA = desc.BorderColor[3],
            .minLod = desc.MinLOD,
            .maxLod = desc.MaxLOD,
        };
    }

    [[nodiscard]] D3D11_RASTERIZER_DESC toNative(
        const gm_structs::ID3D11RasterizerDesc& desc) noexcept
    {
        return {
            .FillMode = static_cast<D3D11_FILL_MODE>(desc.fillMode),
            .CullMode = static_cast<D3D11_CULL_MODE>(desc.cullMode),
            .FrontCounterClockwise = desc.frontCounterClockwise,
            .DepthBias = desc.depthBias,
            .DepthBiasClamp = desc.depthBiasClamp,
            .SlopeScaledDepthBias = desc.slopeScaledDepthBias,
            .DepthClipEnable = desc.depthClipEnable,
            .ScissorEnable = desc.scissorEnable,
            .MultisampleEnable = desc.multisampleEnable,
            .AntialiasedLineEnable = desc.antialiasedLineEnable,
        };
    }

    [[nodiscard]] gm_structs::ID3D11RasterizerDesc fromNative(
        const D3D11_RASTERIZER_DESC& desc) noexcept
    {
        return {
            .fillMode = static_cast<std::uint32_t>(desc.FillMode),
            .cullMode = static_cast<std::uint32_t>(desc.CullMode),
            .frontCounterClockwise = desc.FrontCounterClockwise != FALSE,
            .depthBias = desc.DepthBias,
            .depthBiasClamp = desc.DepthBiasClamp,
            .slopeScaledDepthBias = desc.SlopeScaledDepthBias,
            .depthClipEnable = desc.DepthClipEnable != FALSE,
            .scissorEnable = desc.ScissorEnable != FALSE,
            .multisampleEnable = desc.MultisampleEnable != FALSE,
            .antialiasedLineEnable = desc.AntialiasedLineEnable != FALSE,
        };
    }

    [[nodiscard]] D3D11_RENDER_TARGET_BLEND_DESC toNative(
        const gm_structs::ID3D11RenderTargetBlendDesc& desc) noexcept
    {
        return {
            .BlendEnable = desc.blendEnable,
            .SrcBlend = static_cast<D3D11_BLEND>(desc.srcBlend),
            .DestBlend = static_cast<D3D11_BLEND>(desc.destBlend),
            .BlendOp = static_cast<D3D11_BLEND_OP>(desc.blendOp),
            .SrcBlendAlpha = static_cast<D3D11_BLEND>(desc.srcBlendAlpha),
            .DestBlendAlpha = static_cast<D3D11_BLEND>(desc.destBlendAlpha),
            .BlendOpAlpha = static_cast<D3D11_BLEND_OP>(desc.blendOpAlpha),
            .RenderTargetWriteMask = static_cast<UINT8>(desc.renderTargetWriteMask),
        };
    }

    [[nodiscard]] gm_structs::ID3D11RenderTargetBlendDesc fromNative(
        const D3D11_RENDER_TARGET_BLEND_DESC& desc) noexcept
    {
        return {
            .blendEnable = desc.BlendEnable != FALSE,
            .srcBlend = static_cast<std::uint32_t>(desc.SrcBlend),
            .destBlend = static_cast<std::uint32_t>(desc.DestBlend),
            .blendOp = static_cast<std::uint32_t>(desc.BlendOp),
            .srcBlendAlpha = static_cast<std::uint32_t>(desc.SrcBlendAlpha),
            .destBlendAlpha = static_cast<std::uint32_t>(desc.DestBlendAlpha),
            .blendOpAlpha = static_cast<std::uint32_t>(desc.BlendOpAlpha),
            .renderTargetWriteMask = desc.RenderTargetWriteMask,
        };
    }

    [[nodiscard]] D3D11_DEPTH_STENCILOP_DESC toNative(
        const gm_structs::ID3D11DepthStencilOpDesc& desc) noexcept
    {
        return {
            .StencilFailOp = static_cast<D3D11_STENCIL_OP>(desc.stencilFailOp),
            .StencilDepthFailOp = static_cast<D3D11_STENCIL_OP>(desc.stencilDepthFailOp),
            .StencilPassOp = static_cast<D3D11_STENCIL_OP>(desc.stencilPassOp),
            .StencilFunc = static_cast<D3D11_COMPARISON_FUNC>(desc.stencilFunc),
        };
    }

    [[nodiscard]] gm_structs::ID3D11DepthStencilOpDesc fromNative(
        const D3D11_DEPTH_STENCILOP_DESC& desc) noexcept
    {
        return {
            .stencilFailOp = static_cast<std::uint32_t>(desc.StencilFailOp),
            .stencilDepthFailOp = static_cast<std::uint32_t>(desc.StencilDepthFailOp),
            .stencilPassOp = static_cast<std::uint32_t>(desc.StencilPassOp),
            .stencilFunc = static_cast<std::uint32_t>(desc.StencilFunc),
        };
    }
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_sampler_state(
    const std::uint64_t deviceHandle,
    const gm_structs::ID3D11SamplerDesc& desc)
{
    const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
    if (!device)
    {
        return failedResult(E_HANDLE);
    }

    const D3D11_SAMPLER_DESC nativeDesc = toNative(desc);
    Microsoft::WRL::ComPtr<ID3D11SamplerState> state;
    const HRESULT hresult = device->CreateSamplerState(&nativeDesc, &state);
    return finishCreate(hresult, state.Get(), gm_enums::ID3D11HandleKind::SamplerState);
}

gm_structs::ID3D11SamplerDesc id3d11_sampler_state_get_desc(const std::uint64_t stateHandle)
{
    const auto state = id3d11::acquireInterface<ID3D11SamplerState>(
        stateHandle,
        gm_enums::ID3D11HandleKind::SamplerState);
    if (!state)
    {
        return {};
    }

    D3D11_SAMPLER_DESC desc{};
    state->GetDesc(&desc);
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return fromNative(desc);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_rasterizer_state(
    const std::uint64_t deviceHandle,
    const gm_structs::ID3D11RasterizerDesc& desc)
{
    const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
    if (!device)
    {
        return failedResult(E_HANDLE);
    }

    const D3D11_RASTERIZER_DESC nativeDesc = toNative(desc);
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> state;
    const HRESULT hresult = device->CreateRasterizerState(&nativeDesc, &state);
    return finishCreate(hresult, state.Get(), gm_enums::ID3D11HandleKind::RasterizerState);
}

gm_structs::ID3D11RasterizerDesc id3d11_rasterizer_state_get_desc(
    const std::uint64_t stateHandle)
{
    const auto state = id3d11::acquireInterface<ID3D11RasterizerState>(
        stateHandle,
        gm_enums::ID3D11HandleKind::RasterizerState);
    if (!state)
    {
        return {};
    }

    D3D11_RASTERIZER_DESC desc{};
    state->GetDesc(&desc);
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return fromNative(desc);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_blend_state(
    const std::uint64_t deviceHandle,
    const gm_structs::ID3D11BlendDesc& desc)
{
    const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
    if (!device)
    {
        return failedResult(E_HANDLE);
    }
    if (desc.renderTargets.size() != D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)
    {
        return failedResult(E_INVALIDARG);
    }

    D3D11_BLEND_DESC nativeDesc{};
    nativeDesc.AlphaToCoverageEnable = desc.alphaToCoverageEnable;
    nativeDesc.IndependentBlendEnable = desc.independentBlendEnable;
    for (std::size_t index = 0; index < desc.renderTargets.size(); ++index)
    {
        if (desc.renderTargets[index].renderTargetWriteMask > 0xffU)
        {
            return failedResult(E_INVALIDARG);
        }
        nativeDesc.RenderTarget[index] = toNative(desc.renderTargets[index]);
    }

    Microsoft::WRL::ComPtr<ID3D11BlendState> state;
    const HRESULT hresult = device->CreateBlendState(&nativeDesc, &state);
    return finishCreate(hresult, state.Get(), gm_enums::ID3D11HandleKind::BlendState);
}

gm_structs::ID3D11BlendDesc id3d11_blend_state_get_desc(const std::uint64_t stateHandle)
{
    gm_structs::ID3D11BlendDesc output{};
    const auto state = id3d11::acquireInterface<ID3D11BlendState>(
        stateHandle,
        gm_enums::ID3D11HandleKind::BlendState);
    if (!state)
    {
        return output;
    }

    D3D11_BLEND_DESC desc{};
    state->GetDesc(&desc);
    output.alphaToCoverageEnable = desc.AlphaToCoverageEnable != FALSE;
    output.independentBlendEnable = desc.IndependentBlendEnable != FALSE;
    output.renderTargets.reserve(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT);
    for (const auto& renderTarget : desc.RenderTarget)
    {
        output.renderTargets.push_back(fromNative(renderTarget));
    }
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_depth_stencil_state(
    const std::uint64_t deviceHandle,
    const gm_structs::ID3D11DepthStencilDesc& desc)
{
    const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
    if (!device)
    {
        return failedResult(E_HANDLE);
    }
    if (desc.stencilReadMask > 0xffU || desc.stencilWriteMask > 0xffU)
    {
        return failedResult(E_INVALIDARG);
    }

    const D3D11_DEPTH_STENCIL_DESC nativeDesc{
        .DepthEnable = desc.depthEnable,
        .DepthWriteMask = static_cast<D3D11_DEPTH_WRITE_MASK>(desc.depthWriteMask),
        .DepthFunc = static_cast<D3D11_COMPARISON_FUNC>(desc.depthFunc),
        .StencilEnable = desc.stencilEnable,
        .StencilReadMask = static_cast<UINT8>(desc.stencilReadMask),
        .StencilWriteMask = static_cast<UINT8>(desc.stencilWriteMask),
        .FrontFace = toNative(desc.frontFace),
        .BackFace = toNative(desc.backFace),
    };

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> state;
    const HRESULT hresult = device->CreateDepthStencilState(&nativeDesc, &state);
    return finishCreate(hresult, state.Get(), gm_enums::ID3D11HandleKind::DepthStencilState);
}

gm_structs::ID3D11DepthStencilDesc id3d11_depth_stencil_state_get_desc(
    const std::uint64_t stateHandle)
{
    gm_structs::ID3D11DepthStencilDesc output{};
    const auto state = id3d11::acquireInterface<ID3D11DepthStencilState>(
        stateHandle,
        gm_enums::ID3D11HandleKind::DepthStencilState);
    if (!state)
    {
        return output;
    }

    D3D11_DEPTH_STENCIL_DESC desc{};
    state->GetDesc(&desc);
    output.depthEnable = desc.DepthEnable != FALSE;
    output.depthWriteMask = static_cast<std::uint32_t>(desc.DepthWriteMask);
    output.depthFunc = static_cast<std::uint32_t>(desc.DepthFunc);
    output.stencilEnable = desc.StencilEnable != FALSE;
    output.stencilReadMask = desc.StencilReadMask;
    output.stencilWriteMask = desc.StencilWriteMask;
    output.frontFace = fromNative(desc.FrontFace);
    output.backFace = fromNative(desc.BackFace);
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}
