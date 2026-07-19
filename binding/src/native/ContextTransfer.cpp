#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "DeviceContextHelpers.hpp"
#include "ResourceLayout.hpp"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>

#include <d3d11.h>
#include <wrl/client.h>

namespace
{
    struct CopyLayout final
    {
        std::uint32_t rowBytes = 0;
        std::uint32_t rowCount = 0;
        std::uint32_t depth = 0;
    };

    [[nodiscard]] bool fail(const HRESULT hresult) noexcept
    {
        id3d11::BridgeState::instance().setLastHresult(hresult);
        return false;
    }

    [[nodiscard]] bool acquireTransferTarget(
        const std::uint64_t contextHandle,
        const std::uint64_t resourceHandle,
        const std::uint32_t subresource,
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>& context,
        Microsoft::WRL::ComPtr<ID3D11Resource>& resource,
        id3d11::ResourceLayout& layout) noexcept
    {
        if (!id3d11::acquireContextAndChild(
            contextHandle,
            resourceHandle,
            context,
            resource))
        {
            return false;
        }
        if (!id3d11::describeSubresourceLayout(resource.Get(), subresource, layout))
        {
            return fail(E_INVALIDARG);
        }
        return true;
    }

    [[nodiscard]] bool checkedRequiredBytes(
        const CopyLayout& layout,
        const std::uint64_t rowPitch,
        const std::uint64_t depthPitch,
        std::uint64_t& required) noexcept
    {
        if (layout.rowBytes == 0 || layout.rowCount == 0 || layout.depth == 0 ||
            rowPitch < layout.rowBytes)
        {
            return false;
        }
        std::uint64_t minimumSlice = 0;
        if (!id3d11::checkedMultiply(rowPitch, layout.rowCount, minimumSlice) ||
            depthPitch < minimumSlice)
        {
            return false;
        }
        std::uint64_t precedingSlices = 0;
        std::uint64_t precedingRows = 0;
        if (!id3d11::checkedMultiply(depthPitch, layout.depth - 1U, precedingSlices) ||
            !id3d11::checkedMultiply(rowPitch, layout.rowCount - 1U, precedingRows) ||
            precedingSlices > std::numeric_limits<std::uint64_t>::max() - precedingRows ||
            precedingSlices + precedingRows >
                std::numeric_limits<std::uint64_t>::max() - layout.rowBytes)
        {
            return false;
        }
        required = precedingSlices + precedingRows + layout.rowBytes;
        return true;
    }

    [[nodiscard]] bool selectUpdateRegion(
        const id3d11::ResourceLayout& resource,
        const bool useBox,
        const gm_structs::ID3D11Box& box,
        D3D11_BOX& nativeBox,
        const D3D11_BOX*& nativeBoxPointer,
        CopyLayout& copy) noexcept
    {
        std::uint32_t left = 0;
        std::uint32_t top = 0;
        std::uint32_t front = 0;
        std::uint32_t right = resource.width;
        std::uint32_t bottom = resource.height;
        std::uint32_t back = resource.depth;
        nativeBoxPointer = nullptr;
        if (useBox)
        {
            left = box.left;
            top = box.top;
            front = box.front;
            right = box.right;
            bottom = box.bottom;
            back = box.back;
            if (left >= right || top >= bottom || front >= back ||
                right > resource.width || bottom > resource.height || back > resource.depth)
            {
                return false;
            }
            nativeBox = {left, top, front, right, bottom, back};
            nativeBoxPointer = &nativeBox;
        }

        if (resource.dimension == D3D11_RESOURCE_DIMENSION_BUFFER &&
            (top != 0 || bottom != 1 || front != 0 || back != 1))
        {
            return false;
        }
        const auto& format = resource.format;
        if (left % format.blockWidth != 0 || top % format.blockHeight != 0 ||
            (right != resource.width && right % format.blockWidth != 0) ||
            (bottom != resource.height && bottom % format.blockHeight != 0))
        {
            return false;
        }
        const std::uint64_t blocksWide =
            (static_cast<std::uint64_t>(right - left) + format.blockWidth - 1) /
            format.blockWidth;
        const std::uint64_t rows =
            (static_cast<std::uint64_t>(bottom - top) + format.blockHeight - 1) /
            format.blockHeight;
        const std::uint64_t rowBytes = blocksWide * format.bytesPerBlock;
        if (rowBytes > std::numeric_limits<std::uint32_t>::max() ||
            rows > std::numeric_limits<std::uint32_t>::max())
        {
            return false;
        }
        copy = {
            static_cast<std::uint32_t>(rowBytes),
            static_cast<std::uint32_t>(rows),
            back - front,
        };
        return true;
    }

    [[nodiscard]] bool validMapRequest(
        const id3d11::ResourceLayout& layout,
        const D3D11_MAP mapType,
        const bool reading) noexcept
    {
        const bool cpuRead = (layout.cpuAccessFlags & D3D11_CPU_ACCESS_READ) != 0;
        const bool cpuWrite = (layout.cpuAccessFlags & D3D11_CPU_ACCESS_WRITE) != 0;
        if (reading)
        {
            return (mapType == D3D11_MAP_READ && cpuRead) ||
                (mapType == D3D11_MAP_READ_WRITE && cpuRead && cpuWrite);
        }
        if (mapType == D3D11_MAP_WRITE)
        {
            return cpuWrite;
        }
        if (mapType == D3D11_MAP_READ_WRITE)
        {
            return cpuRead && cpuWrite;
        }
        if (mapType == D3D11_MAP_WRITE_DISCARD)
        {
            return layout.usage == D3D11_USAGE_DYNAMIC && cpuWrite;
        }
        return mapType == D3D11_MAP_WRITE_NO_OVERWRITE &&
            layout.dimension == D3D11_RESOURCE_DIMENSION_BUFFER &&
            layout.usage == D3D11_USAGE_DYNAMIC && cpuWrite;
    }

    void copyRows(
        std::byte* destination,
        const std::uint64_t destinationRowPitch,
        const std::uint64_t destinationDepthPitch,
        const std::byte* source,
        const std::uint64_t sourceRowPitch,
        const std::uint64_t sourceDepthPitch,
        const id3d11::ResourceLayout& layout) noexcept
    {
        for (std::uint32_t slice = 0; slice < layout.depth; ++slice)
        {
            for (std::uint32_t row = 0; row < layout.rowCount; ++row)
            {
                std::memcpy(
                    destination + static_cast<std::size_t>(slice) * destinationDepthPitch +
                        static_cast<std::size_t>(row) * destinationRowPitch,
                    source + static_cast<std::size_t>(slice) * sourceDepthPitch +
                        static_cast<std::size_t>(row) * sourceRowPitch,
                    layout.rowBytes);
            }
        }
    }

    [[nodiscard]] bool mapAndCopy(
        const std::uint64_t contextHandle,
        const std::uint64_t resourceHandle,
        const std::uint32_t subresource,
        const gm_enums::ID3D11Map mapTypeValue,
        const std::uint32_t mapFlags,
        const gm::wire::GMBuffer data,
        const bool reading) noexcept
    {
        if ((mapFlags & ~static_cast<std::uint32_t>(D3D11_MAP_FLAG_DO_NOT_WAIT)) != 0)
        {
            return fail(E_INVALIDARG);
        }
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
        Microsoft::WRL::ComPtr<ID3D11Resource> resource;
        id3d11::ResourceLayout layout{};
        if (!acquireTransferTarget(
            contextHandle, resourceHandle, subresource, context, resource, layout))
        {
            return false;
        }
        const auto mapType = static_cast<D3D11_MAP>(mapTypeValue);
        if (!validMapRequest(layout, mapType, reading) || layout.sampleCount != 1 ||
            data.data() == nullptr || data.length() < layout.byteCount)
        {
            return fail(E_INVALIDARG);
        }

        D3D11_MAPPED_SUBRESOURCE mapped{};
        const HRESULT hresult = context->Map(
            resource.Get(), subresource, mapType, mapFlags, &mapped);
        if (FAILED(hresult))
        {
            return fail(hresult);
        }

        const std::uint64_t mappedRowPitch = layout.dimension == D3D11_RESOURCE_DIMENSION_BUFFER
            ? layout.rowBytes
            : mapped.RowPitch;
        const std::uint64_t mappedDepthPitch =
            layout.dimension == D3D11_RESOURCE_DIMENSION_TEXTURE3D
            ? mapped.DepthPitch
            : mappedRowPitch * layout.rowCount;
        std::uint64_t mappedRequired = 0;
        const CopyLayout copyLayout{layout.rowBytes, layout.rowCount, layout.depth};
        const bool mappedLayoutValid = mapped.pData != nullptr &&
            checkedRequiredBytes(copyLayout, mappedRowPitch, mappedDepthPitch, mappedRequired);
        if (mappedLayoutValid)
        {
            auto* gmlBytes = static_cast<std::byte*>(data.data());
            auto* mappedBytes = static_cast<std::byte*>(mapped.pData);
            const std::uint64_t compactDepthPitch =
                static_cast<std::uint64_t>(layout.rowBytes) * layout.rowCount;
            if (reading)
            {
                copyRows(
                    gmlBytes, layout.rowBytes, compactDepthPitch,
                    mappedBytes, mappedRowPitch, mappedDepthPitch, layout);
            }
            else
            {
                copyRows(
                    mappedBytes, mappedRowPitch, mappedDepthPitch,
                    gmlBytes, layout.rowBytes, compactDepthPitch, layout);
            }
        }
        context->Unmap(resource.Get(), subresource);
        return mappedLayoutValid ?
            (id3d11::BridgeState::instance().setLastHresult(S_OK), true) :
            fail(E_FAIL);
    }
}

bool id3d11_device_context_update_subresource(
    const std::uint64_t contextHandle,
    const std::uint64_t destinationResource,
    const std::uint32_t destinationSubresource,
    const bool useDestinationBox,
    const gm_structs::ID3D11Box& destinationBox,
    const gm::wire::GMBuffer sourceData,
    const std::uint64_t sourceOffset,
    const std::uint64_t sourceLength,
    const std::uint32_t sourceRowPitch,
    const std::uint32_t sourceDepthPitch)
{
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11Resource> resource;
    id3d11::ResourceLayout resourceLayout{};
    if (!acquireTransferTarget(
        contextHandle,
        destinationResource,
        destinationSubresource,
        context,
        resource,
        resourceLayout))
    {
        return false;
    }
    D3D11_BOX nativeBox{};
    const D3D11_BOX* nativeBoxPointer = nullptr;
    CopyLayout copyLayout{};
    std::uint64_t requiredBytes = 0;
    if (resourceLayout.usage != D3D11_USAGE_DEFAULT || resourceLayout.sampleCount != 1 ||
        sourceData.data() == nullptr || sourceOffset > sourceData.length() ||
        sourceLength > sourceData.length() - sourceOffset ||
        !selectUpdateRegion(
            resourceLayout,
            useDestinationBox,
            destinationBox,
            nativeBox,
            nativeBoxPointer,
            copyLayout) ||
        !checkedRequiredBytes(copyLayout, sourceRowPitch, sourceDepthPitch, requiredBytes) ||
        requiredBytes > sourceLength)
    {
        return fail(E_INVALIDARG);
    }

    const auto* source = static_cast<const std::byte*>(sourceData.data()) + sourceOffset;
    context->UpdateSubresource(
        resource.Get(),
        destinationSubresource,
        nativeBoxPointer,
        source,
        sourceRowPitch,
        sourceDepthPitch);
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return true;
}

bool id3d11_device_context_map_read_to_buffer(
    const std::uint64_t context,
    const std::uint64_t resource,
    const std::uint32_t subresource,
    const gm_enums::ID3D11Map mapType,
    const std::uint32_t mapFlags,
    const gm::wire::GMBuffer destinationData)
{
    return mapAndCopy(
        context, resource, subresource, mapType, mapFlags, destinationData, true);
}

bool id3d11_device_context_map_write_from_buffer(
    const std::uint64_t context,
    const std::uint64_t resource,
    const std::uint32_t subresource,
    const gm_enums::ID3D11Map mapType,
    const std::uint32_t mapFlags,
    const gm::wire::GMBuffer sourceData)
{
    return mapAndCopy(context, resource, subresource, mapType, mapFlags, sourceData, false);
}
