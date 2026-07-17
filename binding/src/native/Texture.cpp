#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"
#include "NativeHelpers.hpp"

#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

#include <d3d11.h>
#include <wrl/client.h>

namespace
{
    using CreateResult = gm_structs::ID3D11CreateHandleResult;
    using Subresource = gm_structs::ID3D11SubresourceData;

    [[nodiscard]] CreateResult failedResult(const HRESULT hresult) noexcept
    {
        id3d11::BridgeState::instance().setLastHresult(hresult);
        return {
            .hresult = static_cast<std::int32_t>(hresult),
            .handle = 0,
        };
    }

    [[nodiscard]] std::uint32_t resolveMipLevels(
        std::uint32_t largestDimension,
        const std::uint32_t requestedMipLevels) noexcept
    {
        if (largestDimension == 0)
        {
            return 0;
        }

        if (requestedMipLevels != 0)
        {
            return requestedMipLevels;
        }

        std::uint32_t mipLevels = 1;
        while (largestDimension > 1)
        {
            largestDimension >>= 1U;
            ++mipLevels;
        }
        return mipLevels;
    }

    [[nodiscard]] bool checkedMultiply(
        const std::uint32_t left,
        const std::uint32_t right,
        std::size_t& result) noexcept
    {
        const std::uint64_t wide =
            static_cast<std::uint64_t>(left) * static_cast<std::uint64_t>(right);
        if (wide > std::numeric_limits<std::size_t>::max())
        {
            return false;
        }

        result = static_cast<std::size_t>(wide);
        return true;
    }

    [[nodiscard]] bool prepareInitialData(
        const std::size_t expectedCount,
        const std::vector<Subresource>* descriptions,
        const gm::wire::GMBuffer* data,
        std::vector<D3D11_SUBRESOURCE_DATA>& nativeData) noexcept
    {
        if (descriptions == nullptr && data == nullptr)
        {
            return true;
        }

        if (descriptions == nullptr || data == nullptr || expectedCount == 0 ||
            descriptions->size() != expectedCount || data->data() == nullptr)
        {
            return false;
        }

        const std::uint64_t bufferLength = data->length();
        const auto* bytes = static_cast<const std::byte*>(data->data());
        nativeData.reserve(expectedCount);
        for (const Subresource& description : *descriptions)
        {
            if (description.dataSize == 0 || description.offset > bufferLength ||
                description.dataSize > bufferLength - description.offset ||
                description.offset > std::numeric_limits<std::size_t>::max())
            {
                nativeData.clear();
                return false;
            }

            nativeData.push_back({
                .pSysMem = bytes + static_cast<std::size_t>(description.offset),
                .SysMemPitch = description.rowPitch,
                .SysMemSlicePitch = description.slicePitch,
            });
        }
        return true;
    }

    [[nodiscard]] D3D11_TEXTURE1D_DESC toNative(
        const gm_structs::ID3D11Texture1DDesc& desc) noexcept
    {
        return {
            .Width = desc.width,
            .MipLevels = desc.mipLevels,
            .ArraySize = desc.arraySize,
            .Format = static_cast<DXGI_FORMAT>(desc.format),
            .Usage = static_cast<D3D11_USAGE>(desc.usage),
            .BindFlags = desc.bindFlags,
            .CPUAccessFlags = desc.cpuAccessFlags,
            .MiscFlags = desc.miscFlags,
        };
    }

    [[nodiscard]] D3D11_TEXTURE2D_DESC toNative(
        const gm_structs::ID3D11Texture2DDesc& desc) noexcept
    {
        return {
            .Width = desc.width,
            .Height = desc.height,
            .MipLevels = desc.mipLevels,
            .ArraySize = desc.arraySize,
            .Format = static_cast<DXGI_FORMAT>(desc.format),
            .SampleDesc = {
                .Count = desc.sampleCount,
                .Quality = desc.sampleQuality,
            },
            .Usage = static_cast<D3D11_USAGE>(desc.usage),
            .BindFlags = desc.bindFlags,
            .CPUAccessFlags = desc.cpuAccessFlags,
            .MiscFlags = desc.miscFlags,
        };
    }

    [[nodiscard]] D3D11_TEXTURE3D_DESC toNative(
        const gm_structs::ID3D11Texture3DDesc& desc) noexcept
    {
        return {
            .Width = desc.width,
            .Height = desc.height,
            .Depth = desc.depth,
            .MipLevels = desc.mipLevels,
            .Format = static_cast<DXGI_FORMAT>(desc.format),
            .Usage = static_cast<D3D11_USAGE>(desc.usage),
            .BindFlags = desc.bindFlags,
            .CPUAccessFlags = desc.cpuAccessFlags,
            .MiscFlags = desc.miscFlags,
        };
    }

    [[nodiscard]] CreateResult finishCreate(
        const HRESULT hresult,
        IUnknown* texture,
        const gm_enums::ID3D11HandleKind kind) noexcept
    {
        HRESULT finalResult = hresult;
        std::uint64_t handle = 0;
        if (SUCCEEDED(finalResult))
        {
            handle = id3d11::HandleRegistry::instance().intern(texture, kind);
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

    [[nodiscard]] CreateResult createTexture1D(
        const std::uint64_t deviceHandle,
        const gm_structs::ID3D11Texture1DDesc& desc,
        const std::vector<Subresource>* subresources,
        const gm::wire::GMBuffer* data) noexcept
    {
        const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
        if (!device)
        {
            return failedResult(E_HANDLE);
        }

        const std::uint32_t mipLevels = resolveMipLevels(desc.width, desc.mipLevels);
        std::size_t expectedCount = 0;
        if (mipLevels == 0 || desc.arraySize == 0 ||
            !checkedMultiply(mipLevels, desc.arraySize, expectedCount))
        {
            return failedResult(E_INVALIDARG);
        }

        std::vector<D3D11_SUBRESOURCE_DATA> nativeData;
        if (!prepareInitialData(expectedCount, subresources, data, nativeData))
        {
            return failedResult(E_INVALIDARG);
        }

        const D3D11_TEXTURE1D_DESC nativeDesc = toNative(desc);
        Microsoft::WRL::ComPtr<ID3D11Texture1D> texture;
        const HRESULT hresult = device->CreateTexture1D(
            &nativeDesc,
            nativeData.empty() ? nullptr : nativeData.data(),
            &texture);
        return finishCreate(hresult, texture.Get(), gm_enums::ID3D11HandleKind::Texture1D);
    }

    [[nodiscard]] CreateResult createTexture2D(
        const std::uint64_t deviceHandle,
        const gm_structs::ID3D11Texture2DDesc& desc,
        const std::vector<Subresource>* subresources,
        const gm::wire::GMBuffer* data) noexcept
    {
        const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
        if (!device)
        {
            return failedResult(E_HANDLE);
        }

        const std::uint32_t largestDimension = desc.width > desc.height ? desc.width : desc.height;
        const std::uint32_t mipLevels = resolveMipLevels(largestDimension, desc.mipLevels);
        std::size_t expectedCount = 0;
        if (mipLevels == 0 || desc.arraySize == 0 ||
            !checkedMultiply(mipLevels, desc.arraySize, expectedCount))
        {
            return failedResult(E_INVALIDARG);
        }

        std::vector<D3D11_SUBRESOURCE_DATA> nativeData;
        if (!prepareInitialData(expectedCount, subresources, data, nativeData))
        {
            return failedResult(E_INVALIDARG);
        }

        const D3D11_TEXTURE2D_DESC nativeDesc = toNative(desc);
        Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
        const HRESULT hresult = device->CreateTexture2D(
            &nativeDesc,
            nativeData.empty() ? nullptr : nativeData.data(),
            &texture);
        return finishCreate(hresult, texture.Get(), gm_enums::ID3D11HandleKind::Texture2D);
    }

    [[nodiscard]] CreateResult createTexture3D(
        const std::uint64_t deviceHandle,
        const gm_structs::ID3D11Texture3DDesc& desc,
        const std::vector<Subresource>* subresources,
        const gm::wire::GMBuffer* data) noexcept
    {
        const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
        if (!device)
        {
            return failedResult(E_HANDLE);
        }

        std::uint32_t largestDimension = desc.width > desc.height ? desc.width : desc.height;
        if (desc.depth > largestDimension)
        {
            largestDimension = desc.depth;
        }
        const std::size_t expectedCount = resolveMipLevels(largestDimension, desc.mipLevels);
        if (expectedCount == 0)
        {
            return failedResult(E_INVALIDARG);
        }

        std::vector<D3D11_SUBRESOURCE_DATA> nativeData;
        if (!prepareInitialData(expectedCount, subresources, data, nativeData))
        {
            return failedResult(E_INVALIDARG);
        }

        const D3D11_TEXTURE3D_DESC nativeDesc = toNative(desc);
        Microsoft::WRL::ComPtr<ID3D11Texture3D> texture;
        const HRESULT hresult = device->CreateTexture3D(
            &nativeDesc,
            nativeData.empty() ? nullptr : nativeData.data(),
            &texture);
        return finishCreate(hresult, texture.Get(), gm_enums::ID3D11HandleKind::Texture3D);
    }
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_texture1d(
    const std::uint64_t device,
    const gm_structs::ID3D11Texture1DDesc& desc)
{
    return createTexture1D(device, desc, nullptr, nullptr);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_texture1d_with_data(
    const std::uint64_t device,
    const gm_structs::ID3D11Texture1DDesc& desc,
    const std::vector<gm_structs::ID3D11SubresourceData>& subresources,
    const gm::wire::GMBuffer data)
{
    return createTexture1D(device, desc, &subresources, &data);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_texture2d(
    const std::uint64_t device,
    const gm_structs::ID3D11Texture2DDesc& desc)
{
    return createTexture2D(device, desc, nullptr, nullptr);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_texture2d_with_data(
    const std::uint64_t device,
    const gm_structs::ID3D11Texture2DDesc& desc,
    const std::vector<gm_structs::ID3D11SubresourceData>& subresources,
    const gm::wire::GMBuffer data)
{
    return createTexture2D(device, desc, &subresources, &data);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_texture3d(
    const std::uint64_t device,
    const gm_structs::ID3D11Texture3DDesc& desc)
{
    return createTexture3D(device, desc, nullptr, nullptr);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_texture3d_with_data(
    const std::uint64_t device,
    const gm_structs::ID3D11Texture3DDesc& desc,
    const std::vector<gm_structs::ID3D11SubresourceData>& subresources,
    const gm::wire::GMBuffer data)
{
    return createTexture3D(device, desc, &subresources, &data);
}

gm_structs::ID3D11Texture1DDesc id3d11_texture1d_get_desc(const std::uint64_t textureHandle)
{
    gm_structs::ID3D11Texture1DDesc output{};
    const auto texture = id3d11::acquireInterface<ID3D11Texture1D>(textureHandle);
    if (!texture)
    {
        return output;
    }

    D3D11_TEXTURE1D_DESC desc{};
    texture->GetDesc(&desc);
    output.width = desc.Width;
    output.mipLevels = desc.MipLevels;
    output.arraySize = desc.ArraySize;
    output.format = static_cast<std::uint32_t>(desc.Format);
    output.usage = static_cast<std::uint32_t>(desc.Usage);
    output.bindFlags = desc.BindFlags;
    output.cpuAccessFlags = desc.CPUAccessFlags;
    output.miscFlags = desc.MiscFlags;
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}

gm_structs::ID3D11Texture2DDesc id3d11_texture2d_get_desc(const std::uint64_t textureHandle)
{
    gm_structs::ID3D11Texture2DDesc output{};
    const auto texture = id3d11::acquireInterface<ID3D11Texture2D>(textureHandle);
    if (!texture)
    {
        return output;
    }

    D3D11_TEXTURE2D_DESC desc{};
    texture->GetDesc(&desc);
    output.width = desc.Width;
    output.height = desc.Height;
    output.mipLevels = desc.MipLevels;
    output.arraySize = desc.ArraySize;
    output.format = static_cast<std::uint32_t>(desc.Format);
    output.sampleCount = desc.SampleDesc.Count;
    output.sampleQuality = desc.SampleDesc.Quality;
    output.usage = static_cast<std::uint32_t>(desc.Usage);
    output.bindFlags = desc.BindFlags;
    output.cpuAccessFlags = desc.CPUAccessFlags;
    output.miscFlags = desc.MiscFlags;
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}

gm_structs::ID3D11Texture3DDesc id3d11_texture3d_get_desc(const std::uint64_t textureHandle)
{
    gm_structs::ID3D11Texture3DDesc output{};
    const auto texture = id3d11::acquireInterface<ID3D11Texture3D>(textureHandle);
    if (!texture)
    {
        return output;
    }

    D3D11_TEXTURE3D_DESC desc{};
    texture->GetDesc(&desc);
    output.width = desc.Width;
    output.height = desc.Height;
    output.depth = desc.Depth;
    output.mipLevels = desc.MipLevels;
    output.format = static_cast<std::uint32_t>(desc.Format);
    output.usage = static_cast<std::uint32_t>(desc.Usage);
    output.bindFlags = desc.BindFlags;
    output.cpuAccessFlags = desc.CPUAccessFlags;
    output.miscFlags = desc.MiscFlags;
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}
