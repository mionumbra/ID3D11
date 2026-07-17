#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"
#include "NativeHelpers.hpp"
#include "ResourceHelpers.hpp"

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

    template<typename View>
    [[nodiscard]] CreateResult finishCreate(
        const HRESULT hresult,
        View* view,
        const gm_enums::ID3D11HandleKind kind) noexcept
    {
        HRESULT finalResult = hresult;
        std::uint64_t handle = 0;
        if (SUCCEEDED(finalResult))
        {
            handle = id3d11::HandleRegistry::instance().intern(view, kind);
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

    [[nodiscard]] bool toNative(
        const gm_structs::ID3D11ShaderResourceViewDesc& source,
        D3D11_SHADER_RESOURCE_VIEW_DESC& target) noexcept
    {
        target = {};
        target.Format = static_cast<DXGI_FORMAT>(source.format);
        target.ViewDimension = static_cast<D3D11_SRV_DIMENSION>(source.viewDimension);
        switch (target.ViewDimension)
        {
        case D3D11_SRV_DIMENSION_BUFFER:
            target.Buffer.FirstElement = source.firstElement;
            target.Buffer.NumElements = source.numElements;
            return true;
        case D3D11_SRV_DIMENSION_TEXTURE1D:
            target.Texture1D.MostDetailedMip = source.mostDetailedMip;
            target.Texture1D.MipLevels = source.mipLevels;
            return true;
        case D3D11_SRV_DIMENSION_TEXTURE1DARRAY:
            target.Texture1DArray.MostDetailedMip = source.mostDetailedMip;
            target.Texture1DArray.MipLevels = source.mipLevels;
            target.Texture1DArray.FirstArraySlice = source.firstArraySlice;
            target.Texture1DArray.ArraySize = source.arraySize;
            return true;
        case D3D11_SRV_DIMENSION_TEXTURE2D:
            target.Texture2D.MostDetailedMip = source.mostDetailedMip;
            target.Texture2D.MipLevels = source.mipLevels;
            return true;
        case D3D11_SRV_DIMENSION_TEXTURE2DARRAY:
            target.Texture2DArray.MostDetailedMip = source.mostDetailedMip;
            target.Texture2DArray.MipLevels = source.mipLevels;
            target.Texture2DArray.FirstArraySlice = source.firstArraySlice;
            target.Texture2DArray.ArraySize = source.arraySize;
            return true;
        case D3D11_SRV_DIMENSION_TEXTURE2DMS:
            return true;
        case D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY:
            target.Texture2DMSArray.FirstArraySlice = source.firstArraySlice;
            target.Texture2DMSArray.ArraySize = source.arraySize;
            return true;
        case D3D11_SRV_DIMENSION_TEXTURE3D:
            target.Texture3D.MostDetailedMip = source.mostDetailedMip;
            target.Texture3D.MipLevels = source.mipLevels;
            return true;
        case D3D11_SRV_DIMENSION_TEXTURECUBE:
            target.TextureCube.MostDetailedMip = source.mostDetailedMip;
            target.TextureCube.MipLevels = source.mipLevels;
            return true;
        case D3D11_SRV_DIMENSION_TEXTURECUBEARRAY:
            target.TextureCubeArray.MostDetailedMip = source.mostDetailedMip;
            target.TextureCubeArray.MipLevels = source.mipLevels;
            target.TextureCubeArray.First2DArrayFace = source.first2DArrayFace;
            target.TextureCubeArray.NumCubes = source.numCubes;
            return true;
        case D3D11_SRV_DIMENSION_BUFFEREX:
            target.BufferEx.FirstElement = source.firstElement;
            target.BufferEx.NumElements = source.numElements;
            target.BufferEx.Flags = source.flags;
            return true;
        default:
            return false;
        }
    }

    [[nodiscard]] bool toNative(
        const gm_structs::ID3D11RenderTargetViewDesc& source,
        D3D11_RENDER_TARGET_VIEW_DESC& target) noexcept
    {
        target = {};
        target.Format = static_cast<DXGI_FORMAT>(source.format);
        target.ViewDimension = static_cast<D3D11_RTV_DIMENSION>(source.viewDimension);
        switch (target.ViewDimension)
        {
        case D3D11_RTV_DIMENSION_BUFFER:
            target.Buffer.FirstElement = source.firstElement;
            target.Buffer.NumElements = source.numElements;
            return true;
        case D3D11_RTV_DIMENSION_TEXTURE1D:
            target.Texture1D.MipSlice = source.mipSlice;
            return true;
        case D3D11_RTV_DIMENSION_TEXTURE1DARRAY:
            target.Texture1DArray.MipSlice = source.mipSlice;
            target.Texture1DArray.FirstArraySlice = source.firstArraySlice;
            target.Texture1DArray.ArraySize = source.arraySize;
            return true;
        case D3D11_RTV_DIMENSION_TEXTURE2D:
            target.Texture2D.MipSlice = source.mipSlice;
            return true;
        case D3D11_RTV_DIMENSION_TEXTURE2DARRAY:
            target.Texture2DArray.MipSlice = source.mipSlice;
            target.Texture2DArray.FirstArraySlice = source.firstArraySlice;
            target.Texture2DArray.ArraySize = source.arraySize;
            return true;
        case D3D11_RTV_DIMENSION_TEXTURE2DMS:
            return true;
        case D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY:
            target.Texture2DMSArray.FirstArraySlice = source.firstArraySlice;
            target.Texture2DMSArray.ArraySize = source.arraySize;
            return true;
        case D3D11_RTV_DIMENSION_TEXTURE3D:
            target.Texture3D.MipSlice = source.mipSlice;
            target.Texture3D.FirstWSlice = source.firstWSlice;
            target.Texture3D.WSize = source.wSize;
            return true;
        default:
            return false;
        }
    }

    [[nodiscard]] bool toNative(
        const gm_structs::ID3D11DepthStencilViewDesc& source,
        D3D11_DEPTH_STENCIL_VIEW_DESC& target) noexcept
    {
        target = {};
        target.Format = static_cast<DXGI_FORMAT>(source.format);
        target.ViewDimension = static_cast<D3D11_DSV_DIMENSION>(source.viewDimension);
        target.Flags = source.flags;
        switch (target.ViewDimension)
        {
        case D3D11_DSV_DIMENSION_TEXTURE1D:
            target.Texture1D.MipSlice = source.mipSlice;
            return true;
        case D3D11_DSV_DIMENSION_TEXTURE1DARRAY:
            target.Texture1DArray.MipSlice = source.mipSlice;
            target.Texture1DArray.FirstArraySlice = source.firstArraySlice;
            target.Texture1DArray.ArraySize = source.arraySize;
            return true;
        case D3D11_DSV_DIMENSION_TEXTURE2D:
            target.Texture2D.MipSlice = source.mipSlice;
            return true;
        case D3D11_DSV_DIMENSION_TEXTURE2DARRAY:
            target.Texture2DArray.MipSlice = source.mipSlice;
            target.Texture2DArray.FirstArraySlice = source.firstArraySlice;
            target.Texture2DArray.ArraySize = source.arraySize;
            return true;
        case D3D11_DSV_DIMENSION_TEXTURE2DMS:
            return true;
        case D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY:
            target.Texture2DMSArray.FirstArraySlice = source.firstArraySlice;
            target.Texture2DMSArray.ArraySize = source.arraySize;
            return true;
        default:
            return false;
        }
    }

    [[nodiscard]] bool toNative(
        const gm_structs::ID3D11UnorderedAccessViewDesc& source,
        D3D11_UNORDERED_ACCESS_VIEW_DESC& target) noexcept
    {
        target = {};
        target.Format = static_cast<DXGI_FORMAT>(source.format);
        target.ViewDimension = static_cast<D3D11_UAV_DIMENSION>(source.viewDimension);
        switch (target.ViewDimension)
        {
        case D3D11_UAV_DIMENSION_BUFFER:
            target.Buffer.FirstElement = source.firstElement;
            target.Buffer.NumElements = source.numElements;
            target.Buffer.Flags = source.flags;
            return true;
        case D3D11_UAV_DIMENSION_TEXTURE1D:
            target.Texture1D.MipSlice = source.mipSlice;
            return true;
        case D3D11_UAV_DIMENSION_TEXTURE1DARRAY:
            target.Texture1DArray.MipSlice = source.mipSlice;
            target.Texture1DArray.FirstArraySlice = source.firstArraySlice;
            target.Texture1DArray.ArraySize = source.arraySize;
            return true;
        case D3D11_UAV_DIMENSION_TEXTURE2D:
            target.Texture2D.MipSlice = source.mipSlice;
            return true;
        case D3D11_UAV_DIMENSION_TEXTURE2DARRAY:
            target.Texture2DArray.MipSlice = source.mipSlice;
            target.Texture2DArray.FirstArraySlice = source.firstArraySlice;
            target.Texture2DArray.ArraySize = source.arraySize;
            return true;
        case D3D11_UAV_DIMENSION_TEXTURE3D:
            target.Texture3D.MipSlice = source.mipSlice;
            target.Texture3D.FirstWSlice = source.firstWSlice;
            target.Texture3D.WSize = source.wSize;
            return true;
        default:
            return false;
        }
    }

    [[nodiscard]] CreateResult createShaderResourceView(
        const std::uint64_t deviceHandle,
        const std::uint64_t resourceHandle,
        const D3D11_SHADER_RESOURCE_VIEW_DESC* desc) noexcept
    {
        const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
        const auto resource = id3d11::acquireInterface<ID3D11Resource>(resourceHandle);
        if (!device || !resource)
        {
            return failedResult(E_HANDLE);
        }

        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> view;
        const HRESULT hresult = device->CreateShaderResourceView(resource.Get(), desc, &view);
        return finishCreate(hresult, view.Get(), gm_enums::ID3D11HandleKind::ShaderResourceView);
    }

    [[nodiscard]] CreateResult createRenderTargetView(
        const std::uint64_t deviceHandle,
        const std::uint64_t resourceHandle,
        const D3D11_RENDER_TARGET_VIEW_DESC* desc) noexcept
    {
        const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
        const auto resource = id3d11::acquireInterface<ID3D11Resource>(resourceHandle);
        if (!device || !resource)
        {
            return failedResult(E_HANDLE);
        }

        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> view;
        const HRESULT hresult = device->CreateRenderTargetView(resource.Get(), desc, &view);
        return finishCreate(hresult, view.Get(), gm_enums::ID3D11HandleKind::RenderTargetView);
    }

    [[nodiscard]] CreateResult createDepthStencilView(
        const std::uint64_t deviceHandle,
        const std::uint64_t resourceHandle,
        const D3D11_DEPTH_STENCIL_VIEW_DESC* desc) noexcept
    {
        const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
        const auto resource = id3d11::acquireInterface<ID3D11Resource>(resourceHandle);
        if (!device || !resource)
        {
            return failedResult(E_HANDLE);
        }

        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> view;
        const HRESULT hresult = device->CreateDepthStencilView(resource.Get(), desc, &view);
        return finishCreate(hresult, view.Get(), gm_enums::ID3D11HandleKind::DepthStencilView);
    }

    [[nodiscard]] CreateResult createUnorderedAccessView(
        const std::uint64_t deviceHandle,
        const std::uint64_t resourceHandle,
        const D3D11_UNORDERED_ACCESS_VIEW_DESC* desc) noexcept
    {
        const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
        const auto resource = id3d11::acquireInterface<ID3D11Resource>(resourceHandle);
        if (!device || !resource)
        {
            return failedResult(E_HANDLE);
        }

        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> view;
        const HRESULT hresult = device->CreateUnorderedAccessView(resource.Get(), desc, &view);
        return finishCreate(hresult, view.Get(), gm_enums::ID3D11HandleKind::UnorderedAccessView);
    }
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_shader_resource_view_default(
    const std::uint64_t device,
    const std::uint64_t resource)
{
    return createShaderResourceView(device, resource, nullptr);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_shader_resource_view(
    const std::uint64_t device,
    const std::uint64_t resource,
    const gm_structs::ID3D11ShaderResourceViewDesc& desc)
{
    D3D11_SHADER_RESOURCE_VIEW_DESC nativeDesc{};
    return toNative(desc, nativeDesc)
        ? createShaderResourceView(device, resource, &nativeDesc)
        : failedResult(E_INVALIDARG);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_render_target_view_default(
    const std::uint64_t device,
    const std::uint64_t resource)
{
    return createRenderTargetView(device, resource, nullptr);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_render_target_view(
    const std::uint64_t device,
    const std::uint64_t resource,
    const gm_structs::ID3D11RenderTargetViewDesc& desc)
{
    D3D11_RENDER_TARGET_VIEW_DESC nativeDesc{};
    return toNative(desc, nativeDesc)
        ? createRenderTargetView(device, resource, &nativeDesc)
        : failedResult(E_INVALIDARG);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_depth_stencil_view_default(
    const std::uint64_t device,
    const std::uint64_t resource)
{
    return createDepthStencilView(device, resource, nullptr);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_depth_stencil_view(
    const std::uint64_t device,
    const std::uint64_t resource,
    const gm_structs::ID3D11DepthStencilViewDesc& desc)
{
    D3D11_DEPTH_STENCIL_VIEW_DESC nativeDesc{};
    return toNative(desc, nativeDesc)
        ? createDepthStencilView(device, resource, &nativeDesc)
        : failedResult(E_INVALIDARG);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_unordered_access_view_default(
    const std::uint64_t device,
    const std::uint64_t resource)
{
    return createUnorderedAccessView(device, resource, nullptr);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_unordered_access_view(
    const std::uint64_t device,
    const std::uint64_t resource,
    const gm_structs::ID3D11UnorderedAccessViewDesc& desc)
{
    D3D11_UNORDERED_ACCESS_VIEW_DESC nativeDesc{};
    return toNative(desc, nativeDesc)
        ? createUnorderedAccessView(device, resource, &nativeDesc)
        : failedResult(E_INVALIDARG);
}

std::uint64_t id3d11_view_get_resource(const std::uint64_t viewHandle)
{
    const auto view = id3d11::acquireInterface<ID3D11View>(viewHandle);
    if (!view)
    {
        return 0;
    }

    Microsoft::WRL::ComPtr<ID3D11Resource> resource;
    view->GetResource(&resource);
    if (!resource)
    {
        id3d11::BridgeState::instance().setLastHresult(E_FAIL);
        return 0;
    }

    const std::uint64_t handle = id3d11::internResource(resource.Get());
    id3d11::BridgeState::instance().setLastHresult(handle == 0 ? E_OUTOFMEMORY : S_OK);
    return handle;
}

gm_structs::ID3D11ShaderResourceViewDesc id3d11_shader_resource_view_get_desc(
    const std::uint64_t viewHandle)
{
    gm_structs::ID3D11ShaderResourceViewDesc output{};
    const auto view = id3d11::acquireInterface<ID3D11ShaderResourceView>(viewHandle);
    if (!view)
    {
        return output;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC desc{};
    view->GetDesc(&desc);
    output.format = static_cast<std::uint32_t>(desc.Format);
    output.viewDimension = static_cast<std::uint32_t>(desc.ViewDimension);
    switch (desc.ViewDimension)
    {
    case D3D11_SRV_DIMENSION_BUFFER:
        output.firstElement = desc.Buffer.FirstElement;
        output.numElements = desc.Buffer.NumElements;
        break;
    case D3D11_SRV_DIMENSION_TEXTURE1D:
        output.mostDetailedMip = desc.Texture1D.MostDetailedMip;
        output.mipLevels = desc.Texture1D.MipLevels;
        break;
    case D3D11_SRV_DIMENSION_TEXTURE1DARRAY:
        output.mostDetailedMip = desc.Texture1DArray.MostDetailedMip;
        output.mipLevels = desc.Texture1DArray.MipLevels;
        output.firstArraySlice = desc.Texture1DArray.FirstArraySlice;
        output.arraySize = desc.Texture1DArray.ArraySize;
        break;
    case D3D11_SRV_DIMENSION_TEXTURE2D:
        output.mostDetailedMip = desc.Texture2D.MostDetailedMip;
        output.mipLevels = desc.Texture2D.MipLevels;
        break;
    case D3D11_SRV_DIMENSION_TEXTURE2DARRAY:
        output.mostDetailedMip = desc.Texture2DArray.MostDetailedMip;
        output.mipLevels = desc.Texture2DArray.MipLevels;
        output.firstArraySlice = desc.Texture2DArray.FirstArraySlice;
        output.arraySize = desc.Texture2DArray.ArraySize;
        break;
    case D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY:
        output.firstArraySlice = desc.Texture2DMSArray.FirstArraySlice;
        output.arraySize = desc.Texture2DMSArray.ArraySize;
        break;
    case D3D11_SRV_DIMENSION_TEXTURE3D:
        output.mostDetailedMip = desc.Texture3D.MostDetailedMip;
        output.mipLevels = desc.Texture3D.MipLevels;
        break;
    case D3D11_SRV_DIMENSION_TEXTURECUBE:
        output.mostDetailedMip = desc.TextureCube.MostDetailedMip;
        output.mipLevels = desc.TextureCube.MipLevels;
        break;
    case D3D11_SRV_DIMENSION_TEXTURECUBEARRAY:
        output.mostDetailedMip = desc.TextureCubeArray.MostDetailedMip;
        output.mipLevels = desc.TextureCubeArray.MipLevels;
        output.first2DArrayFace = desc.TextureCubeArray.First2DArrayFace;
        output.numCubes = desc.TextureCubeArray.NumCubes;
        break;
    case D3D11_SRV_DIMENSION_BUFFEREX:
        output.firstElement = desc.BufferEx.FirstElement;
        output.numElements = desc.BufferEx.NumElements;
        output.flags = desc.BufferEx.Flags;
        break;
    default:
        break;
    }
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}

gm_structs::ID3D11RenderTargetViewDesc id3d11_render_target_view_get_desc(
    const std::uint64_t viewHandle)
{
    gm_structs::ID3D11RenderTargetViewDesc output{};
    const auto view = id3d11::acquireInterface<ID3D11RenderTargetView>(viewHandle);
    if (!view)
    {
        return output;
    }

    D3D11_RENDER_TARGET_VIEW_DESC desc{};
    view->GetDesc(&desc);
    output.format = static_cast<std::uint32_t>(desc.Format);
    output.viewDimension = static_cast<std::uint32_t>(desc.ViewDimension);
    switch (desc.ViewDimension)
    {
    case D3D11_RTV_DIMENSION_BUFFER:
        output.firstElement = desc.Buffer.FirstElement;
        output.numElements = desc.Buffer.NumElements;
        break;
    case D3D11_RTV_DIMENSION_TEXTURE1D:
        output.mipSlice = desc.Texture1D.MipSlice;
        break;
    case D3D11_RTV_DIMENSION_TEXTURE1DARRAY:
        output.mipSlice = desc.Texture1DArray.MipSlice;
        output.firstArraySlice = desc.Texture1DArray.FirstArraySlice;
        output.arraySize = desc.Texture1DArray.ArraySize;
        break;
    case D3D11_RTV_DIMENSION_TEXTURE2D:
        output.mipSlice = desc.Texture2D.MipSlice;
        break;
    case D3D11_RTV_DIMENSION_TEXTURE2DARRAY:
        output.mipSlice = desc.Texture2DArray.MipSlice;
        output.firstArraySlice = desc.Texture2DArray.FirstArraySlice;
        output.arraySize = desc.Texture2DArray.ArraySize;
        break;
    case D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY:
        output.firstArraySlice = desc.Texture2DMSArray.FirstArraySlice;
        output.arraySize = desc.Texture2DMSArray.ArraySize;
        break;
    case D3D11_RTV_DIMENSION_TEXTURE3D:
        output.mipSlice = desc.Texture3D.MipSlice;
        output.firstWSlice = desc.Texture3D.FirstWSlice;
        output.wSize = desc.Texture3D.WSize;
        break;
    default:
        break;
    }
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}

gm_structs::ID3D11DepthStencilViewDesc id3d11_depth_stencil_view_get_desc(
    const std::uint64_t viewHandle)
{
    gm_structs::ID3D11DepthStencilViewDesc output{};
    const auto view = id3d11::acquireInterface<ID3D11DepthStencilView>(viewHandle);
    if (!view)
    {
        return output;
    }

    D3D11_DEPTH_STENCIL_VIEW_DESC desc{};
    view->GetDesc(&desc);
    output.format = static_cast<std::uint32_t>(desc.Format);
    output.viewDimension = static_cast<std::uint32_t>(desc.ViewDimension);
    output.flags = desc.Flags;
    switch (desc.ViewDimension)
    {
    case D3D11_DSV_DIMENSION_TEXTURE1D:
        output.mipSlice = desc.Texture1D.MipSlice;
        break;
    case D3D11_DSV_DIMENSION_TEXTURE1DARRAY:
        output.mipSlice = desc.Texture1DArray.MipSlice;
        output.firstArraySlice = desc.Texture1DArray.FirstArraySlice;
        output.arraySize = desc.Texture1DArray.ArraySize;
        break;
    case D3D11_DSV_DIMENSION_TEXTURE2D:
        output.mipSlice = desc.Texture2D.MipSlice;
        break;
    case D3D11_DSV_DIMENSION_TEXTURE2DARRAY:
        output.mipSlice = desc.Texture2DArray.MipSlice;
        output.firstArraySlice = desc.Texture2DArray.FirstArraySlice;
        output.arraySize = desc.Texture2DArray.ArraySize;
        break;
    case D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY:
        output.firstArraySlice = desc.Texture2DMSArray.FirstArraySlice;
        output.arraySize = desc.Texture2DMSArray.ArraySize;
        break;
    default:
        break;
    }
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}

gm_structs::ID3D11UnorderedAccessViewDesc id3d11_unordered_access_view_get_desc(
    const std::uint64_t viewHandle)
{
    gm_structs::ID3D11UnorderedAccessViewDesc output{};
    const auto view = id3d11::acquireInterface<ID3D11UnorderedAccessView>(viewHandle);
    if (!view)
    {
        return output;
    }

    D3D11_UNORDERED_ACCESS_VIEW_DESC desc{};
    view->GetDesc(&desc);
    output.format = static_cast<std::uint32_t>(desc.Format);
    output.viewDimension = static_cast<std::uint32_t>(desc.ViewDimension);
    switch (desc.ViewDimension)
    {
    case D3D11_UAV_DIMENSION_BUFFER:
        output.firstElement = desc.Buffer.FirstElement;
        output.numElements = desc.Buffer.NumElements;
        output.flags = desc.Buffer.Flags;
        break;
    case D3D11_UAV_DIMENSION_TEXTURE1D:
        output.mipSlice = desc.Texture1D.MipSlice;
        break;
    case D3D11_UAV_DIMENSION_TEXTURE1DARRAY:
        output.mipSlice = desc.Texture1DArray.MipSlice;
        output.firstArraySlice = desc.Texture1DArray.FirstArraySlice;
        output.arraySize = desc.Texture1DArray.ArraySize;
        break;
    case D3D11_UAV_DIMENSION_TEXTURE2D:
        output.mipSlice = desc.Texture2D.MipSlice;
        break;
    case D3D11_UAV_DIMENSION_TEXTURE2DARRAY:
        output.mipSlice = desc.Texture2DArray.MipSlice;
        output.firstArraySlice = desc.Texture2DArray.FirstArraySlice;
        output.arraySize = desc.Texture2DArray.ArraySize;
        break;
    case D3D11_UAV_DIMENSION_TEXTURE3D:
        output.mipSlice = desc.Texture3D.MipSlice;
        output.firstWSlice = desc.Texture3D.FirstWSlice;
        output.wSize = desc.Texture3D.WSize;
        break;
    default:
        break;
    }
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}
