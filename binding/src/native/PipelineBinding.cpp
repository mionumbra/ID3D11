#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "DeviceContextHelpers.hpp"

#include <cmath>
#include <cstdint>
#include <vector>

#include <d3d11.h>
#include <dxgiformat.h>
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

    [[nodiscard]] bool validIndexFormat(
        const std::uint64_t bufferHandle,
        const std::uint32_t format,
        const std::uint32_t offset) noexcept
    {
        if (bufferHandle == 0)
        {
            return format == DXGI_FORMAT_UNKNOWN ||
                format == DXGI_FORMAT_R16_UINT ||
                format == DXGI_FORMAT_R32_UINT;
        }
        if (format == DXGI_FORMAT_R16_UINT)
        {
            return offset % 2U == 0;
        }
        return format == DXGI_FORMAT_R32_UINT && offset % 4U == 0;
    }

    [[nodiscard]] bool validViewport(const gm_structs::ID3D11Viewport& viewport) noexcept
    {
        return std::isfinite(viewport.topLeftX) &&
            std::isfinite(viewport.topLeftY) &&
            std::isfinite(viewport.width) &&
            std::isfinite(viewport.height) &&
            std::isfinite(viewport.minDepth) &&
            std::isfinite(viewport.maxDepth) &&
            viewport.width >= 0.0F &&
            viewport.height >= 0.0F &&
            viewport.minDepth >= 0.0F &&
            viewport.maxDepth <= 1.0F &&
            viewport.minDepth <= viewport.maxDepth;
    }

    [[nodiscard]] D3D11_VIEWPORT toNative(const gm_structs::ID3D11Viewport& viewport) noexcept
    {
        return {
            .TopLeftX = viewport.topLeftX,
            .TopLeftY = viewport.topLeftY,
            .Width = viewport.width,
            .Height = viewport.height,
            .MinDepth = viewport.minDepth,
            .MaxDepth = viewport.maxDepth,
        };
    }

    [[nodiscard]] gm_structs::ID3D11Viewport fromNative(
        const D3D11_VIEWPORT& viewport) noexcept
    {
        return {
            .topLeftX = viewport.TopLeftX,
            .topLeftY = viewport.TopLeftY,
            .width = viewport.Width,
            .height = viewport.Height,
            .minDepth = viewport.MinDepth,
            .maxDepth = viewport.MaxDepth,
        };
    }

    [[nodiscard]] bool validRect(const gm_structs::ID3D11Rect& rect) noexcept
    {
        return rect.left <= rect.right && rect.top <= rect.bottom;
    }

    [[nodiscard]] D3D11_RECT toNative(const gm_structs::ID3D11Rect& rect) noexcept
    {
        return {
            .left = rect.left,
            .top = rect.top,
            .right = rect.right,
            .bottom = rect.bottom,
        };
    }

    [[nodiscard]] gm_structs::ID3D11Rect fromNative(const D3D11_RECT& rect) noexcept
    {
        return {
            .left = rect.left,
            .top = rect.top,
            .right = rect.right,
            .bottom = rect.bottom,
        };
    }
}

bool id3d11_device_context_ia_set_vertex_buffers(
    const std::uint64_t contextHandle,
    const std::uint32_t startSlot,
    const std::vector<gm_structs::ID3D11VertexBufferBinding>& bindings)
{
    auto& bridge = id3d11::BridgeState::instance();
    if (!validSlotRange(startSlot, bindings.size(), D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT))
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }

    std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> ownedBuffers;
    std::vector<ID3D11Buffer*> buffers;
    std::vector<UINT> strides;
    std::vector<UINT> offsets;
    ownedBuffers.reserve(bindings.size());
    buffers.reserve(bindings.size());
    strides.reserve(bindings.size());
    offsets.reserve(bindings.size());
    for (const auto& binding : bindings)
    {
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
        if (!id3d11::acquireOptionalContextChild(context.Get(), binding.buffer, buffer))
        {
            return false;
        }
        ownedBuffers.push_back(buffer);
        buffers.push_back(buffer.Get());
        strides.push_back(binding.stride);
        offsets.push_back(binding.offset);
    }

    context->IASetVertexBuffers(
        startSlot,
        static_cast<UINT>(bindings.size()),
        buffers.empty() ? nullptr : buffers.data(),
        strides.empty() ? nullptr : strides.data(),
        offsets.empty() ? nullptr : offsets.data());
    bridge.setLastHresult(S_OK);
    return true;
}

std::vector<gm_structs::ID3D11VertexBufferBinding>
id3d11_device_context_ia_get_vertex_buffers(
    const std::uint64_t contextHandle,
    const std::uint32_t startSlot,
    const std::uint32_t count)
{
    std::vector<gm_structs::ID3D11VertexBufferBinding> output;
    auto& bridge = id3d11::BridgeState::instance();
    if (!validSlotRange(startSlot, count, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT))
    {
        bridge.setLastHresult(E_INVALIDARG);
        return output;
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return output;
    }

    std::vector<ID3D11Buffer*> buffers(count, nullptr);
    std::vector<UINT> strides(count, 0);
    std::vector<UINT> offsets(count, 0);
    context->IAGetVertexBuffers(
        startSlot,
        count,
        buffers.empty() ? nullptr : buffers.data(),
        strides.empty() ? nullptr : strides.data(),
        offsets.empty() ? nullptr : offsets.data());

    bool internFailed = false;
    output.reserve(count);
    for (std::size_t index = 0; index < count; ++index)
    {
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
        buffer.Attach(buffers[index]);
        const std::uint64_t handle = id3d11::internOptionalDeviceChild(
            buffer.Get(),
            gm_enums::ID3D11HandleKind::Buffer);
        internFailed = internFailed || (buffer && handle == 0);
        output.push_back({
            .buffer = handle,
            .stride = strides[index],
            .offset = offsets[index],
        });
    }
    bridge.setLastHresult(internFailed ? E_OUTOFMEMORY : S_OK);
    return output;
}

bool id3d11_device_context_ia_set_index_buffer(
    const std::uint64_t contextHandle,
    const std::uint64_t bufferHandle,
    const std::uint32_t format,
    const std::uint32_t offset)
{
    auto& bridge = id3d11::BridgeState::instance();
    if (!validIndexFormat(bufferHandle, format, offset))
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }

    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    if (!id3d11::acquireOptionalContextChild(context.Get(), bufferHandle, buffer))
    {
        return false;
    }

    context->IASetIndexBuffer(buffer.Get(), static_cast<DXGI_FORMAT>(format), offset);
    bridge.setLastHresult(S_OK);
    return true;
}

gm_structs::ID3D11IndexBufferBinding id3d11_device_context_ia_get_index_buffer(
    const std::uint64_t contextHandle)
{
    gm_structs::ID3D11IndexBufferBinding output{};
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return output;
    }

    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
    context->IAGetIndexBuffer(&buffer, &format, &output.offset);
    output.buffer = id3d11::internOptionalDeviceChild(
        buffer.Get(),
        gm_enums::ID3D11HandleKind::Buffer);
    output.format = static_cast<std::uint32_t>(format);
    return output;
}

bool id3d11_device_context_rs_set_viewports(
    const std::uint64_t contextHandle,
    const std::vector<gm_structs::ID3D11Viewport>& viewports)
{
    auto& bridge = id3d11::BridgeState::instance();
    if (viewports.size() > D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    std::vector<D3D11_VIEWPORT> nativeViewports;
    nativeViewports.reserve(viewports.size());
    for (const auto& viewport : viewports)
    {
        if (!validViewport(viewport))
        {
            bridge.setLastHresult(E_INVALIDARG);
            return false;
        }
        nativeViewports.push_back(toNative(viewport));
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }
    context->RSSetViewports(
        static_cast<UINT>(nativeViewports.size()),
        nativeViewports.empty() ? nullptr : nativeViewports.data());
    bridge.setLastHresult(S_OK);
    return true;
}

std::vector<gm_structs::ID3D11Viewport> id3d11_device_context_rs_get_viewports(
    const std::uint64_t contextHandle)
{
    std::vector<gm_structs::ID3D11Viewport> output;
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return output;
    }

    UINT count = 0;
    context->RSGetViewports(&count, nullptr);
    if (count > D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)
    {
        id3d11::BridgeState::instance().setLastHresult(E_FAIL);
        return output;
    }

    std::vector<D3D11_VIEWPORT> viewports(count);
    if (count != 0)
    {
        context->RSGetViewports(&count, viewports.data());
    }
    output.reserve(count);
    for (std::size_t index = 0; index < count; ++index)
    {
        output.push_back(fromNative(viewports[index]));
    }
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}

bool id3d11_device_context_rs_set_scissor_rects(
    const std::uint64_t contextHandle,
    const std::vector<gm_structs::ID3D11Rect>& rects)
{
    auto& bridge = id3d11::BridgeState::instance();
    if (rects.size() > D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    std::vector<D3D11_RECT> nativeRects;
    nativeRects.reserve(rects.size());
    for (const auto& rect : rects)
    {
        if (!validRect(rect))
        {
            bridge.setLastHresult(E_INVALIDARG);
            return false;
        }
        nativeRects.push_back(toNative(rect));
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }
    context->RSSetScissorRects(
        static_cast<UINT>(nativeRects.size()),
        nativeRects.empty() ? nullptr : nativeRects.data());
    bridge.setLastHresult(S_OK);
    return true;
}

std::vector<gm_structs::ID3D11Rect> id3d11_device_context_rs_get_scissor_rects(
    const std::uint64_t contextHandle)
{
    std::vector<gm_structs::ID3D11Rect> output;
    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return output;
    }

    UINT count = 0;
    context->RSGetScissorRects(&count, nullptr);
    if (count > D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)
    {
        id3d11::BridgeState::instance().setLastHresult(E_FAIL);
        return output;
    }

    std::vector<D3D11_RECT> rects(count);
    if (count != 0)
    {
        context->RSGetScissorRects(&count, rects.data());
    }
    output.reserve(count);
    for (std::size_t index = 0; index < count; ++index)
    {
        output.push_back(fromNative(rects[index]));
    }
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}
