#pragma once

#include "FormatLayout.hpp"

#include <algorithm>
#include <cstdint>
#include <limits>

#include <d3d11.h>
#include <wrl/client.h>

namespace id3d11
{
    struct ResourceLayout final
    {
        D3D11_RESOURCE_DIMENSION dimension = D3D11_RESOURCE_DIMENSION_UNKNOWN;
        D3D11_USAGE usage = D3D11_USAGE_DEFAULT;
        std::uint32_t cpuAccessFlags = 0;
        std::uint32_t sampleCount = 1;
        std::uint32_t width = 0;
        std::uint32_t height = 0;
        std::uint32_t depth = 0;
        std::uint32_t rowBytes = 0;
        std::uint32_t rowCount = 0;
        std::uint64_t byteCount = 0;
        FormatLayout format{};
    };

    [[nodiscard]] inline bool checkedMultiply(
        const std::uint64_t left,
        const std::uint64_t right,
        std::uint64_t& output) noexcept
    {
        if (left != 0 && right > std::numeric_limits<std::uint64_t>::max() / left)
        {
            return false;
        }
        output = left * right;
        return true;
    }

    [[nodiscard]] inline bool describeSubresourceLayout(
        ID3D11Resource* resource,
        const std::uint32_t subresource,
        ResourceLayout& output) noexcept
    {
        output = {};
        resource->GetType(&output.dimension);
        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
        std::uint32_t mipLevels = 1;
        std::uint32_t arraySize = 1;

        switch (output.dimension)
        {
        case D3D11_RESOURCE_DIMENSION_BUFFER:
        {
            Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
            if (FAILED(resource->QueryInterface(IID_PPV_ARGS(&buffer))) || subresource != 0)
            {
                return false;
            }
            D3D11_BUFFER_DESC desc{};
            buffer->GetDesc(&desc);
            output.usage = desc.Usage;
            output.cpuAccessFlags = desc.CPUAccessFlags;
            output.width = desc.ByteWidth;
            output.height = 1;
            output.depth = 1;
            output.rowBytes = desc.ByteWidth;
            output.rowCount = 1;
            output.byteCount = desc.ByteWidth;
            output.format = {1, 1, 1};
            return desc.ByteWidth != 0;
        }
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
        {
            Microsoft::WRL::ComPtr<ID3D11Texture1D> texture;
            if (FAILED(resource->QueryInterface(IID_PPV_ARGS(&texture))))
            {
                return false;
            }
            D3D11_TEXTURE1D_DESC desc{};
            texture->GetDesc(&desc);
            output.usage = desc.Usage;
            output.cpuAccessFlags = desc.CPUAccessFlags;
            output.width = desc.Width;
            output.height = 1;
            output.depth = 1;
            mipLevels = desc.MipLevels;
            arraySize = desc.ArraySize;
            format = desc.Format;
            break;
        }
        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
        {
            Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
            if (FAILED(resource->QueryInterface(IID_PPV_ARGS(&texture))))
            {
                return false;
            }
            D3D11_TEXTURE2D_DESC desc{};
            texture->GetDesc(&desc);
            output.usage = desc.Usage;
            output.cpuAccessFlags = desc.CPUAccessFlags;
            output.sampleCount = desc.SampleDesc.Count;
            output.width = desc.Width;
            output.height = desc.Height;
            output.depth = 1;
            mipLevels = desc.MipLevels;
            arraySize = desc.ArraySize;
            format = desc.Format;
            break;
        }
        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
        {
            Microsoft::WRL::ComPtr<ID3D11Texture3D> texture;
            if (FAILED(resource->QueryInterface(IID_PPV_ARGS(&texture))))
            {
                return false;
            }
            D3D11_TEXTURE3D_DESC desc{};
            texture->GetDesc(&desc);
            output.usage = desc.Usage;
            output.cpuAccessFlags = desc.CPUAccessFlags;
            output.width = desc.Width;
            output.height = desc.Height;
            output.depth = desc.Depth;
            mipLevels = desc.MipLevels;
            format = desc.Format;
            break;
        }
        default:
            return false;
        }

        const std::uint64_t subresourceCount =
            static_cast<std::uint64_t>(mipLevels) * arraySize;
        if (mipLevels == 0 || subresource >= subresourceCount ||
            !getFormatLayout(format, output.format))
        {
            return false;
        }
        const std::uint32_t mip = subresource % mipLevels;
        output.width = std::max(1U, output.width >> mip);
        output.height = std::max(1U, output.height >> mip);
        output.depth = std::max(1U, output.depth >> mip);
        const std::uint64_t blocksWide =
            (static_cast<std::uint64_t>(output.width) + output.format.blockWidth - 1) /
            output.format.blockWidth;
        const std::uint64_t rows =
            (static_cast<std::uint64_t>(output.height) + output.format.blockHeight - 1) /
            output.format.blockHeight;
        const std::uint64_t rowBytes = blocksWide * output.format.bytesPerBlock;
        std::uint64_t sliceBytes = 0;
        if (rowBytes > std::numeric_limits<std::uint32_t>::max() ||
            rows > std::numeric_limits<std::uint32_t>::max() ||
            !checkedMultiply(rowBytes, rows, sliceBytes) ||
            !checkedMultiply(sliceBytes, output.depth, output.byteCount))
        {
            return false;
        }
        output.rowBytes = static_cast<std::uint32_t>(rowBytes);
        output.rowCount = static_cast<std::uint32_t>(rows);
        return output.byteCount != 0;
    }
}
