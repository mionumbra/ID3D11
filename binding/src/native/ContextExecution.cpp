#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "DeviceContextHelpers.hpp"
#include "FormatLayout.hpp"
#include "NativeHelpers.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>

#include <d3d11.h>
#include <dxgiformat.h>
#include <wrl/client.h>

namespace
{
    struct ResourceInfo
    {
        D3D11_RESOURCE_DIMENSION dimension = D3D11_RESOURCE_DIMENSION_UNKNOWN;
        UINT width = 0;
        UINT height = 0;
        UINT depth = 0;
        UINT mipLevels = 0;
        UINT arraySize = 0;
        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
        DXGI_SAMPLE_DESC sampleDesc{1, 0};
        UINT bindFlags = 0;
        UINT miscFlags = 0;
        D3D11_USAGE usage = D3D11_USAGE_DEFAULT;
    };

    [[nodiscard]] bool fail(const HRESULT hresult) noexcept
    {
        id3d11::BridgeState::instance().setLastHresult(hresult);
        return false;
    }

    [[nodiscard]] bool succeed() noexcept
    {
        id3d11::BridgeState::instance().setLastHresult(S_OK);
        return true;
    }

    [[nodiscard]] UINT mipDimension(const UINT size, const UINT mip) noexcept
    {
        return std::max<UINT>(1, size >> mip);
    }

    [[nodiscard]] bool describeResource(
        ID3D11Resource* resource,
        ResourceInfo& output) noexcept
    {
        resource->GetType(&output.dimension);
        switch (output.dimension)
        {
        case D3D11_RESOURCE_DIMENSION_BUFFER:
        {
            Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
            if (FAILED(resource->QueryInterface(IID_PPV_ARGS(&buffer))))
            {
                return false;
            }
            D3D11_BUFFER_DESC desc{};
            buffer->GetDesc(&desc);
            output.width = desc.ByteWidth;
            output.height = 1;
            output.depth = 1;
            output.mipLevels = 1;
            output.arraySize = 1;
            output.bindFlags = desc.BindFlags;
            output.miscFlags = desc.MiscFlags;
            output.usage = desc.Usage;
            return true;
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
            output.width = desc.Width;
            output.height = 1;
            output.depth = 1;
            output.mipLevels = desc.MipLevels;
            output.arraySize = desc.ArraySize;
            output.format = desc.Format;
            output.bindFlags = desc.BindFlags;
            output.miscFlags = desc.MiscFlags;
            output.usage = desc.Usage;
            return true;
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
            output.width = desc.Width;
            output.height = desc.Height;
            output.depth = 1;
            output.mipLevels = desc.MipLevels;
            output.arraySize = desc.ArraySize;
            output.format = desc.Format;
            output.sampleDesc = desc.SampleDesc;
            output.bindFlags = desc.BindFlags;
            output.miscFlags = desc.MiscFlags;
            output.usage = desc.Usage;
            return true;
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
            output.width = desc.Width;
            output.height = desc.Height;
            output.depth = desc.Depth;
            output.mipLevels = desc.MipLevels;
            output.arraySize = 1;
            output.format = desc.Format;
            output.bindFlags = desc.BindFlags;
            output.miscFlags = desc.MiscFlags;
            output.usage = desc.Usage;
            return true;
        }
        default:
            return false;
        }
    }

    [[nodiscard]] bool subresourceExtent(
        const ResourceInfo& info,
        const UINT subresource,
        UINT& width,
        UINT& height,
        UINT& depth) noexcept
    {
        if (info.mipLevels == 0 || info.arraySize == 0)
        {
            return false;
        }
        const std::uint64_t count =
            static_cast<std::uint64_t>(info.mipLevels) * info.arraySize;
        if (subresource >= count)
        {
            return false;
        }

        const UINT mip = subresource % info.mipLevels;
        width = mipDimension(info.width, mip);
        height = mipDimension(info.height, mip);
        depth = mipDimension(info.depth, mip);
        return true;
    }

    [[nodiscard]] bool sameCopyFamily(
        const ResourceInfo& destination,
        const ResourceInfo& source) noexcept
    {
        return destination.dimension == source.dimension &&
            destination.format == source.format;
    }

    [[nodiscard]] bool identicalCopyShape(
        const ResourceInfo& destination,
        const ResourceInfo& source) noexcept
    {
        return sameCopyFamily(destination, source) &&
            destination.width == source.width &&
            destination.height == source.height &&
            destination.depth == source.depth &&
            destination.mipLevels == source.mipLevels &&
            destination.arraySize == source.arraySize &&
            destination.sampleDesc.Count == source.sampleDesc.Count &&
            destination.sampleDesc.Quality == source.sampleDesc.Quality;
    }

    [[nodiscard]] bool acquireResourcePair(
        const std::uint64_t contextHandle,
        const std::uint64_t destinationHandle,
        const std::uint64_t sourceHandle,
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>& context,
        Microsoft::WRL::ComPtr<ID3D11Resource>& destination,
        Microsoft::WRL::ComPtr<ID3D11Resource>& source) noexcept
    {
        context = id3d11::acquireContext(contextHandle);
        if (!context)
        {
            return false;
        }

        destination = id3d11::acquireInterface<ID3D11Resource>(destinationHandle);
        source = id3d11::acquireInterface<ID3D11Resource>(sourceHandle);
        return destination && source &&
            id3d11::validateSameDevice(context.Get(), destination.Get()) &&
            id3d11::validateSameDevice(context.Get(), source.Get());
    }

    template<typename Caller>
    [[nodiscard]] bool callContext(
        const std::uint64_t contextHandle,
        Caller caller)
    {
        const auto context = id3d11::acquireContext(contextHandle);
        if (!context)
        {
            return false;
        }
        caller(context.Get());
        return succeed();
    }

    template<std::size_t ArgumentBytes, typename Caller>
    [[nodiscard]] bool callIndirect(
        const std::uint64_t contextHandle,
        const std::uint64_t bufferHandle,
        const std::uint32_t alignedByteOffset,
        Caller caller)
    {
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
        if (!id3d11::acquireContextAndChild(contextHandle, bufferHandle, context, buffer))
        {
            return false;
        }

        D3D11_BUFFER_DESC desc{};
        buffer->GetDesc(&desc);
        if ((desc.MiscFlags & D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS) == 0 ||
            alignedByteOffset % 4U != 0 ||
            alignedByteOffset > desc.ByteWidth ||
            ArgumentBytes > desc.ByteWidth - alignedByteOffset)
        {
            return fail(E_INVALIDARG);
        }

        caller(context.Get(), buffer.Get(), alignedByteOffset);
        return succeed();
    }

    [[nodiscard]] bool hasMiscFlag(
        ID3D11Resource* resource,
        const UINT flag) noexcept
    {
        ResourceInfo info{};
        return describeResource(resource, info) && (info.miscFlags & flag) != 0;
    }
}

bool id3d11_device_context_draw_indexed(
    const std::uint64_t context,
    const std::uint32_t indexCount,
    const std::uint32_t startIndexLocation,
    const std::int32_t baseVertexLocation)
{
    return callContext(context, [&](ID3D11DeviceContext* nativeContext)
    {
        nativeContext->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
    });
}

bool id3d11_device_context_draw(
    const std::uint64_t context,
    const std::uint32_t vertexCount,
    const std::uint32_t startVertexLocation)
{
    return callContext(context, [&](ID3D11DeviceContext* nativeContext)
    {
        nativeContext->Draw(vertexCount, startVertexLocation);
    });
}

bool id3d11_device_context_draw_indexed_instanced(
    const std::uint64_t context,
    const std::uint32_t indexCountPerInstance,
    const std::uint32_t instanceCount,
    const std::uint32_t startIndexLocation,
    const std::int32_t baseVertexLocation,
    const std::uint32_t startInstanceLocation)
{
    return callContext(context, [&](ID3D11DeviceContext* nativeContext)
    {
        nativeContext->DrawIndexedInstanced(
            indexCountPerInstance,
            instanceCount,
            startIndexLocation,
            baseVertexLocation,
            startInstanceLocation);
    });
}

bool id3d11_device_context_draw_instanced(
    const std::uint64_t context,
    const std::uint32_t vertexCountPerInstance,
    const std::uint32_t instanceCount,
    const std::uint32_t startVertexLocation,
    const std::uint32_t startInstanceLocation)
{
    return callContext(context, [&](ID3D11DeviceContext* nativeContext)
    {
        nativeContext->DrawInstanced(
            vertexCountPerInstance,
            instanceCount,
            startVertexLocation,
            startInstanceLocation);
    });
}

bool id3d11_device_context_draw_auto(const std::uint64_t context)
{
    return callContext(context, [](ID3D11DeviceContext* nativeContext)
    {
        nativeContext->DrawAuto();
    });
}

bool id3d11_device_context_draw_indexed_instanced_indirect(
    const std::uint64_t context,
    const std::uint64_t argumentBuffer,
    const std::uint32_t alignedByteOffset)
{
    return callIndirect<5U * sizeof(UINT)>(
        context,
        argumentBuffer,
        alignedByteOffset,
        [](ID3D11DeviceContext* nativeContext, ID3D11Buffer* buffer, const UINT offset)
        {
            nativeContext->DrawIndexedInstancedIndirect(buffer, offset);
        });
}

bool id3d11_device_context_draw_instanced_indirect(
    const std::uint64_t context,
    const std::uint64_t argumentBuffer,
    const std::uint32_t alignedByteOffset)
{
    return callIndirect<4U * sizeof(UINT)>(
        context,
        argumentBuffer,
        alignedByteOffset,
        [](ID3D11DeviceContext* nativeContext, ID3D11Buffer* buffer, const UINT offset)
        {
            nativeContext->DrawInstancedIndirect(buffer, offset);
        });
}

bool id3d11_device_context_dispatch(
    const std::uint64_t context,
    const std::uint32_t threadGroupCountX,
    const std::uint32_t threadGroupCountY,
    const std::uint32_t threadGroupCountZ)
{
    if (threadGroupCountX > D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION ||
        threadGroupCountY > D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION ||
        threadGroupCountZ > D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION)
    {
        return fail(E_INVALIDARG);
    }
    return callContext(context, [&](ID3D11DeviceContext* nativeContext)
    {
        nativeContext->Dispatch(threadGroupCountX, threadGroupCountY, threadGroupCountZ);
    });
}

bool id3d11_device_context_dispatch_indirect(
    const std::uint64_t context,
    const std::uint64_t argumentBuffer,
    const std::uint32_t alignedByteOffset)
{
    return callIndirect<3U * sizeof(UINT)>(
        context,
        argumentBuffer,
        alignedByteOffset,
        [](ID3D11DeviceContext* nativeContext, ID3D11Buffer* buffer, const UINT offset)
        {
            nativeContext->DispatchIndirect(buffer, offset);
        });
}

bool id3d11_device_context_copy_subresource_region(
    const std::uint64_t contextHandle,
    const std::uint64_t destinationResource,
    const std::uint32_t destinationSubresource,
    const std::uint32_t destinationX,
    const std::uint32_t destinationY,
    const std::uint32_t destinationZ,
    const std::uint64_t sourceResource,
    const std::uint32_t sourceSubresource,
    const bool useSourceBox,
    const gm_structs::ID3D11Box& sourceBox)
{
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11Resource> destination;
    Microsoft::WRL::ComPtr<ID3D11Resource> source;
    if (!acquireResourcePair(
        contextHandle,
        destinationResource,
        sourceResource,
        context,
        destination,
        source))
    {
        return false;
    }

    ResourceInfo destinationInfo{};
    ResourceInfo sourceInfo{};
    UINT destinationWidth = 0;
    UINT destinationHeight = 0;
    UINT destinationDepth = 0;
    UINT sourceWidth = 0;
    UINT sourceHeight = 0;
    UINT sourceDepth = 0;
    if (!describeResource(destination.Get(), destinationInfo) ||
        !describeResource(source.Get(), sourceInfo) ||
        !sameCopyFamily(destinationInfo, sourceInfo) ||
        !subresourceExtent(
            destinationInfo,
            destinationSubresource,
            destinationWidth,
            destinationHeight,
            destinationDepth) ||
        !subresourceExtent(
            sourceInfo,
            sourceSubresource,
            sourceWidth,
            sourceHeight,
            sourceDepth) ||
        (id3d11::sameComIdentity(destination.Get(), source.Get()) &&
            destinationSubresource == sourceSubresource))
    {
        return fail(E_INVALIDARG);
    }

    D3D11_BOX nativeBox{};
    const D3D11_BOX* nativeBoxPointer = nullptr;
    UINT copyWidth = sourceWidth;
    UINT copyHeight = sourceHeight;
    UINT copyDepth = sourceDepth;
    if (useSourceBox)
    {
        nativeBox = {
            .left = sourceBox.left,
            .top = sourceBox.top,
            .front = sourceBox.front,
            .right = sourceBox.right,
            .bottom = sourceBox.bottom,
            .back = sourceBox.back,
        };
        if (nativeBox.left >= nativeBox.right ||
            nativeBox.top >= nativeBox.bottom ||
            nativeBox.front >= nativeBox.back ||
            nativeBox.right > sourceWidth ||
            nativeBox.bottom > sourceHeight ||
            nativeBox.back > sourceDepth)
        {
            return fail(E_INVALIDARG);
        }
        copyWidth = nativeBox.right - nativeBox.left;
        copyHeight = nativeBox.bottom - nativeBox.top;
        copyDepth = nativeBox.back - nativeBox.front;
        nativeBoxPointer = &nativeBox;
    }

    const bool multisampled = sourceInfo.sampleDesc.Count > 1 ||
        destinationInfo.sampleDesc.Count > 1;
    if ((sourceInfo.bindFlags & D3D11_BIND_DEPTH_STENCIL) != 0 ||
        (destinationInfo.bindFlags & D3D11_BIND_DEPTH_STENCIL) != 0 ||
        sourceInfo.sampleDesc.Count != destinationInfo.sampleDesc.Count ||
        sourceInfo.sampleDesc.Quality != destinationInfo.sampleDesc.Quality ||
        (multisampled && (useSourceBox || destinationX != 0 ||
            destinationY != 0 || destinationZ != 0)))
    {
        return fail(E_INVALIDARG);
    }

    id3d11::FormatLayout formatLayout{};
    if (sourceInfo.dimension != D3D11_RESOURCE_DIMENSION_BUFFER &&
        id3d11::getFormatLayout(sourceInfo.format, formatLayout) &&
        (formatLayout.blockWidth > 1 || formatLayout.blockHeight > 1))
    {
        if (destinationX % formatLayout.blockWidth != 0 ||
            destinationY % formatLayout.blockHeight != 0 ||
            (useSourceBox &&
                (nativeBox.left % formatLayout.blockWidth != 0 ||
                 nativeBox.top % formatLayout.blockHeight != 0 ||
                 (nativeBox.right != sourceWidth &&
                    nativeBox.right % formatLayout.blockWidth != 0) ||
                 (nativeBox.bottom != sourceHeight &&
                    nativeBox.bottom % formatLayout.blockHeight != 0))))
        {
            return fail(E_INVALIDARG);
        }
    }

    if (copyWidth > destinationWidth ||
        destinationX > destinationWidth - copyWidth ||
        copyHeight > destinationHeight ||
        destinationY > destinationHeight - copyHeight ||
        copyDepth > destinationDepth ||
        destinationZ > destinationDepth - copyDepth)
    {
        return fail(E_INVALIDARG);
    }

    context->CopySubresourceRegion(
        destination.Get(),
        destinationSubresource,
        destinationX,
        destinationY,
        destinationZ,
        source.Get(),
        sourceSubresource,
        nativeBoxPointer);
    return succeed();
}

bool id3d11_device_context_copy_resource(
    const std::uint64_t contextHandle,
    const std::uint64_t destinationResource,
    const std::uint64_t sourceResource)
{
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11Resource> destination;
    Microsoft::WRL::ComPtr<ID3D11Resource> source;
    if (!acquireResourcePair(
        contextHandle,
        destinationResource,
        sourceResource,
        context,
        destination,
        source))
    {
        return false;
    }

    ResourceInfo destinationInfo{};
    ResourceInfo sourceInfo{};
    if (id3d11::sameComIdentity(destination.Get(), source.Get()) ||
        !describeResource(destination.Get(), destinationInfo) ||
        !describeResource(source.Get(), sourceInfo) ||
        !identicalCopyShape(destinationInfo, sourceInfo))
    {
        return fail(E_INVALIDARG);
    }

    context->CopyResource(destination.Get(), source.Get());
    return succeed();
}

bool id3d11_device_context_copy_structure_count(
    const std::uint64_t contextHandle,
    const std::uint64_t destinationBuffer,
    const std::uint32_t destinationAlignedByteOffset,
    const std::uint64_t sourceView)
{
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }
    const auto destination = id3d11::acquireInterface<ID3D11Buffer>(destinationBuffer);
    const auto source = id3d11::acquireInterface<ID3D11UnorderedAccessView>(sourceView);
    if (!destination || !source ||
        !id3d11::validateSameDevice(context.Get(), destination.Get()) ||
        !id3d11::validateSameDevice(context.Get(), source.Get()))
    {
        return false;
    }

    D3D11_BUFFER_DESC destinationDesc{};
    destination->GetDesc(&destinationDesc);
    D3D11_UNORDERED_ACCESS_VIEW_DESC sourceDesc{};
    source->GetDesc(&sourceDesc);
    constexpr UINT counterFlags =
        D3D11_BUFFER_UAV_FLAG_APPEND | D3D11_BUFFER_UAV_FLAG_COUNTER;
    if (destinationAlignedByteOffset % sizeof(UINT) != 0 ||
        destinationAlignedByteOffset > destinationDesc.ByteWidth ||
        sizeof(UINT) > destinationDesc.ByteWidth - destinationAlignedByteOffset ||
        sourceDesc.ViewDimension != D3D11_UAV_DIMENSION_BUFFER ||
        (sourceDesc.Buffer.Flags & counterFlags) == 0)
    {
        return fail(E_INVALIDARG);
    }

    context->CopyStructureCount(
        destination.Get(),
        destinationAlignedByteOffset,
        source.Get());
    return succeed();
}

bool id3d11_device_context_clear_render_target_view(
    const std::uint64_t contextHandle,
    const std::uint64_t renderTargetView,
    const float red,
    const float green,
    const float blue,
    const float alpha)
{
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> view;
    if (!id3d11::acquireContextAndChild(contextHandle, renderTargetView, context, view))
    {
        return false;
    }
    const FLOAT color[4] = {red, green, blue, alpha};
    context->ClearRenderTargetView(view.Get(), color);
    return succeed();
}

bool id3d11_device_context_clear_unordered_access_view_uint(
    const std::uint64_t contextHandle,
    const std::uint64_t unorderedAccessView,
    const std::uint32_t value0,
    const std::uint32_t value1,
    const std::uint32_t value2,
    const std::uint32_t value3)
{
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> view;
    if (!id3d11::acquireContextAndChild(contextHandle, unorderedAccessView, context, view))
    {
        return false;
    }
    const UINT values[4] = {value0, value1, value2, value3};
    context->ClearUnorderedAccessViewUint(view.Get(), values);
    return succeed();
}

bool id3d11_device_context_clear_unordered_access_view_float(
    const std::uint64_t contextHandle,
    const std::uint64_t unorderedAccessView,
    const float value0,
    const float value1,
    const float value2,
    const float value3)
{
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> view;
    if (!id3d11::acquireContextAndChild(contextHandle, unorderedAccessView, context, view))
    {
        return false;
    }
    const FLOAT values[4] = {value0, value1, value2, value3};
    context->ClearUnorderedAccessViewFloat(view.Get(), values);
    return succeed();
}

bool id3d11_device_context_clear_depth_stencil_view(
    const std::uint64_t contextHandle,
    const std::uint64_t depthStencilView,
    const std::uint32_t clearFlags,
    const float depth,
    const std::uint32_t stencil)
{
    constexpr UINT allowedFlags = D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL;
    if (clearFlags == 0 || (clearFlags & ~allowedFlags) != 0 ||
        !std::isfinite(depth) || depth < 0.0F || depth > 1.0F ||
        stencil > std::numeric_limits<UINT8>::max())
    {
        return fail(E_INVALIDARG);
    }

    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> view;
    if (!id3d11::acquireContextAndChild(contextHandle, depthStencilView, context, view))
    {
        return false;
    }
    context->ClearDepthStencilView(
        view.Get(),
        clearFlags,
        depth,
        static_cast<UINT8>(stencil));
    return succeed();
}

bool id3d11_device_context_generate_mips(
    const std::uint64_t contextHandle,
    const std::uint64_t shaderResourceView)
{
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> view;
    if (!id3d11::acquireContextAndChild(contextHandle, shaderResourceView, context, view))
    {
        return false;
    }

    Microsoft::WRL::ComPtr<ID3D11Resource> resource;
    view->GetResource(&resource);
    if (!resource || !hasMiscFlag(resource.Get(), D3D11_RESOURCE_MISC_GENERATE_MIPS))
    {
        return fail(E_INVALIDARG);
    }
    context->GenerateMips(view.Get());
    return succeed();
}

bool id3d11_device_context_set_resource_min_lod(
    const std::uint64_t contextHandle,
    const std::uint64_t resourceHandle,
    const float minimumLod)
{
    if (!std::isfinite(minimumLod) || minimumLod < 0.0F)
    {
        return fail(E_INVALIDARG);
    }
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11Resource> resource;
    if (!id3d11::acquireContextAndChild(contextHandle, resourceHandle, context, resource))
    {
        return false;
    }
    if (!hasMiscFlag(resource.Get(), D3D11_RESOURCE_MISC_RESOURCE_CLAMP))
    {
        return fail(E_INVALIDARG);
    }
    context->SetResourceMinLOD(resource.Get(), minimumLod);
    return succeed();
}

float id3d11_device_context_get_resource_min_lod(
    const std::uint64_t contextHandle,
    const std::uint64_t resourceHandle)
{
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11Resource> resource;
    if (!id3d11::acquireContextAndChild(contextHandle, resourceHandle, context, resource))
    {
        return 0.0F;
    }
    if (!hasMiscFlag(resource.Get(), D3D11_RESOURCE_MISC_RESOURCE_CLAMP))
    {
        id3d11::BridgeState::instance().setLastHresult(E_INVALIDARG);
        return 0.0F;
    }
    const FLOAT minimumLod = context->GetResourceMinLOD(resource.Get());
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return minimumLod;
}

bool id3d11_device_context_resolve_subresource(
    const std::uint64_t contextHandle,
    const std::uint64_t destinationResource,
    const std::uint32_t destinationSubresource,
    const std::uint64_t sourceResource,
    const std::uint32_t sourceSubresource,
    const std::uint32_t format)
{
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11Resource> destination;
    Microsoft::WRL::ComPtr<ID3D11Resource> source;
    if (!acquireResourcePair(
        contextHandle,
        destinationResource,
        sourceResource,
        context,
        destination,
        source))
    {
        return false;
    }

    ResourceInfo destinationInfo{};
    ResourceInfo sourceInfo{};
    UINT destinationWidth = 0;
    UINT destinationHeight = 0;
    UINT destinationDepth = 0;
    UINT sourceWidth = 0;
    UINT sourceHeight = 0;
    UINT sourceDepth = 0;
    if (id3d11::sameComIdentity(destination.Get(), source.Get()) ||
        !describeResource(destination.Get(), destinationInfo) ||
        !describeResource(source.Get(), sourceInfo) ||
        destinationInfo.dimension != D3D11_RESOURCE_DIMENSION_TEXTURE2D ||
        sourceInfo.dimension != D3D11_RESOURCE_DIMENSION_TEXTURE2D ||
        destinationInfo.sampleDesc.Count != 1 ||
        sourceInfo.sampleDesc.Count <= 1 ||
        destinationInfo.usage != D3D11_USAGE_DEFAULT ||
        format == DXGI_FORMAT_UNKNOWN ||
        destinationInfo.format != static_cast<DXGI_FORMAT>(format) ||
        sourceInfo.format != static_cast<DXGI_FORMAT>(format) ||
        !subresourceExtent(
            destinationInfo,
            destinationSubresource,
            destinationWidth,
            destinationHeight,
            destinationDepth) ||
        !subresourceExtent(
            sourceInfo,
            sourceSubresource,
            sourceWidth,
            sourceHeight,
            sourceDepth) ||
        destinationWidth != sourceWidth ||
        destinationHeight != sourceHeight)
    {
        return fail(E_INVALIDARG);
    }

    context->ResolveSubresource(
        destination.Get(),
        destinationSubresource,
        source.Get(),
        sourceSubresource,
        static_cast<DXGI_FORMAT>(format));
    return succeed();
}
