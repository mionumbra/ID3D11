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
    const UINT capacity = count;
    if (count != 0)
    {
        context->RSGetViewports(&count, viewports.data());
    }
    if (count > capacity)
    {
        id3d11::BridgeState::instance().setLastHresult(E_FAIL);
        return output;
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
    const UINT capacity = count;
    if (count != 0)
    {
        context->RSGetScissorRects(&count, rects.data());
    }
    if (count > capacity)
    {
        id3d11::BridgeState::instance().setLastHresult(E_FAIL);
        return output;
    }
    output.reserve(count);
    for (std::size_t index = 0; index < count; ++index)
    {
        output.push_back(fromNative(rects[index]));
    }
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}

bool id3d11_device_context_om_set_render_targets(
    const std::uint64_t contextHandle,
    const std::vector<std::uint64_t>& renderTargetViews,
    const std::uint64_t depthStencilView)
{
    auto& bridge = id3d11::BridgeState::instance();
    if (renderTargetViews.size() > D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }

    std::vector<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>> ownedViews;
    std::vector<ID3D11RenderTargetView*> views;
    ownedViews.reserve(renderTargetViews.size());
    views.reserve(renderTargetViews.size());
    for (const std::uint64_t handle : renderTargetViews)
    {
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> view;
        if (!id3d11::acquireOptionalContextChild(context.Get(), handle, view))
        {
            return false;
        }
        ownedViews.push_back(view);
        views.push_back(view.Get());
    }

    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthView;
    if (!id3d11::acquireOptionalContextChild(context.Get(), depthStencilView, depthView))
    {
        return false;
    }

    context->OMSetRenderTargets(
        static_cast<UINT>(views.size()),
        views.empty() ? nullptr : views.data(),
        depthView.Get());
    bridge.setLastHresult(S_OK);
    return true;
}

gm_structs::ID3D11OutputMergerTargets id3d11_device_context_om_get_render_targets(
    const std::uint64_t contextHandle,
    const std::uint32_t count)
{
    gm_structs::ID3D11OutputMergerTargets output{};
    auto& bridge = id3d11::BridgeState::instance();
    if (count > D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)
    {
        bridge.setLastHresult(E_INVALIDARG);
        return output;
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return output;
    }

    std::vector<ID3D11RenderTargetView*> views(count, nullptr);
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthView;
    context->OMGetRenderTargets(
        count,
        views.empty() ? nullptr : views.data(),
        &depthView);

    bool internFailed = false;
    output.renderTargetViews.reserve(count);
    for (ID3D11RenderTargetView* rawView : views)
    {
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> view;
        view.Attach(rawView);
        const std::uint64_t handle = id3d11::internOptionalDeviceChild(
            view.Get(),
            gm_enums::ID3D11HandleKind::RenderTargetView);
        internFailed = internFailed || (view && handle == 0);
        output.renderTargetViews.push_back(handle);
    }
    output.depthStencilView = id3d11::internOptionalDeviceChild(
        depthView.Get(),
        gm_enums::ID3D11HandleKind::DepthStencilView);
    internFailed = internFailed || (depthView && output.depthStencilView == 0);
    bridge.setLastHresult(internFailed ? E_OUTOFMEMORY : S_OK);
    return output;
}

bool id3d11_device_context_so_set_targets(
    const std::uint64_t contextHandle,
    const std::vector<gm_structs::ID3D11StreamOutputTarget>& targets)
{
    auto& bridge = id3d11::BridgeState::instance();
    if (targets.size() > D3D11_SO_BUFFER_SLOT_COUNT)
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
    std::vector<UINT> offsets;
    ownedBuffers.reserve(targets.size());
    buffers.reserve(targets.size());
    offsets.reserve(targets.size());
    for (const auto& target : targets)
    {
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
        if (!id3d11::acquireOptionalContextChild(context.Get(), target.buffer, buffer))
        {
            return false;
        }
        ownedBuffers.push_back(buffer);
        buffers.push_back(buffer.Get());
        offsets.push_back(target.offset);
    }

    context->SOSetTargets(
        static_cast<UINT>(targets.size()),
        buffers.empty() ? nullptr : buffers.data(),
        offsets.empty() ? nullptr : offsets.data());
    bridge.setLastHresult(S_OK);
    return true;
}

std::vector<std::uint64_t> id3d11_device_context_so_get_targets(
    const std::uint64_t contextHandle,
    const std::uint32_t count)
{
    std::vector<std::uint64_t> output;
    auto& bridge = id3d11::BridgeState::instance();
    if (count > D3D11_SO_BUFFER_SLOT_COUNT)
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
    context->SOGetTargets(count, buffers.empty() ? nullptr : buffers.data());

    bool internFailed = false;
    output.reserve(count);
    for (ID3D11Buffer* rawBuffer : buffers)
    {
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
        buffer.Attach(rawBuffer);
        const std::uint64_t handle = id3d11::internOptionalDeviceChild(
            buffer.Get(),
            gm_enums::ID3D11HandleKind::Buffer);
        internFailed = internFailed || (buffer && handle == 0);
        output.push_back(handle);
    }
    bridge.setLastHresult(internFailed ? E_OUTOFMEMORY : S_OK);
    return output;
}

bool id3d11_device_context_cs_set_unordered_access_views(
    const std::uint64_t contextHandle,
    const std::uint32_t startSlot,
    const std::vector<gm_structs::ID3D11UnorderedAccessViewBinding>& views)
{
    auto& bridge = id3d11::BridgeState::instance();
    if (!validSlotRange(startSlot, views.size(), D3D11_1_UAV_SLOT_COUNT))
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }

    std::vector<Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>> ownedViews;
    std::vector<ID3D11UnorderedAccessView*> nativeViews;
    std::vector<UINT> initialCounts;
    ownedViews.reserve(views.size());
    nativeViews.reserve(views.size());
    initialCounts.reserve(views.size());
    for (const auto& binding : views)
    {
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> view;
        if (!id3d11::acquireOptionalContextChild(context.Get(), binding.view, view))
        {
            return false;
        }
        ownedViews.push_back(view);
        nativeViews.push_back(view.Get());
        initialCounts.push_back(binding.initialCount);
    }

    context->CSSetUnorderedAccessViews(
        startSlot,
        static_cast<UINT>(views.size()),
        nativeViews.empty() ? nullptr : nativeViews.data(),
        initialCounts.empty() ? nullptr : initialCounts.data());
    bridge.setLastHresult(S_OK);
    return true;
}

std::vector<std::uint64_t> id3d11_device_context_cs_get_unordered_access_views(
    const std::uint64_t contextHandle,
    const std::uint32_t startSlot,
    const std::uint32_t count)
{
    std::vector<std::uint64_t> output;
    auto& bridge = id3d11::BridgeState::instance();
    if (!validSlotRange(startSlot, count, D3D11_1_UAV_SLOT_COUNT))
    {
        bridge.setLastHresult(E_INVALIDARG);
        return output;
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return output;
    }

    std::vector<ID3D11UnorderedAccessView*> views(count, nullptr);
    context->CSGetUnorderedAccessViews(
        startSlot,
        count,
        views.empty() ? nullptr : views.data());

    bool internFailed = false;
    output.reserve(count);
    for (ID3D11UnorderedAccessView* rawView : views)
    {
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> view;
        view.Attach(rawView);
        const std::uint64_t handle = id3d11::internOptionalDeviceChild(
            view.Get(),
            gm_enums::ID3D11HandleKind::UnorderedAccessView);
        internFailed = internFailed || (view && handle == 0);
        output.push_back(handle);
    }
    bridge.setLastHresult(internFailed ? E_OUTOFMEMORY : S_OK);
    return output;
}

bool id3d11_device_context_om_set_render_targets_and_unordered_access_views(
    const std::uint64_t contextHandle,
    const bool keepRenderTargets,
    const std::vector<std::uint64_t>& renderTargetViews,
    const std::uint64_t depthStencilView,
    const std::uint32_t uavStartSlot,
    const bool keepUnorderedAccessViews,
    const std::vector<gm_structs::ID3D11UnorderedAccessViewBinding>& unorderedAccessViews)
{
    auto& bridge = id3d11::BridgeState::instance();
    if (!keepRenderTargets &&
        renderTargetViews.size() > D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }
    if (!keepUnorderedAccessViews &&
        !validSlotRange(uavStartSlot, unorderedAccessViews.size(), D3D11_PS_CS_UAV_REGISTER_COUNT))
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }
    if (!keepRenderTargets &&
        !keepUnorderedAccessViews &&
        uavStartSlot < renderTargetViews.size())
    {
        bridge.setLastHresult(E_INVALIDARG);
        return false;
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return false;
    }

    std::vector<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>> ownedRtvs;
    std::vector<ID3D11RenderTargetView*> rtvs;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthView;
    UINT numRtvs = D3D11_KEEP_RENDER_TARGETS_AND_DEPTH_STENCIL;
    if (!keepRenderTargets)
    {
        numRtvs = static_cast<UINT>(renderTargetViews.size());
        ownedRtvs.reserve(renderTargetViews.size());
        rtvs.reserve(renderTargetViews.size());
        for (const std::uint64_t handle : renderTargetViews)
        {
            Microsoft::WRL::ComPtr<ID3D11RenderTargetView> view;
            if (!id3d11::acquireOptionalContextChild(context.Get(), handle, view))
            {
                return false;
            }
            ownedRtvs.push_back(view);
            rtvs.push_back(view.Get());
        }
        if (!id3d11::acquireOptionalContextChild(context.Get(), depthStencilView, depthView))
        {
            return false;
        }
    }

    std::vector<Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>> ownedUavs;
    std::vector<ID3D11UnorderedAccessView*> uavs;
    std::vector<UINT> initialCounts;
    UINT numUavs = D3D11_KEEP_UNORDERED_ACCESS_VIEWS;
    if (!keepUnorderedAccessViews)
    {
        numUavs = static_cast<UINT>(unorderedAccessViews.size());
        ownedUavs.reserve(unorderedAccessViews.size());
        uavs.reserve(unorderedAccessViews.size());
        initialCounts.reserve(unorderedAccessViews.size());
        for (const auto& binding : unorderedAccessViews)
        {
            Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> view;
            if (!id3d11::acquireOptionalContextChild(context.Get(), binding.view, view))
            {
                return false;
            }
            ownedUavs.push_back(view);
            uavs.push_back(view.Get());
            initialCounts.push_back(binding.initialCount);
        }
    }

    context->OMSetRenderTargetsAndUnorderedAccessViews(
        numRtvs,
        keepRenderTargets ? nullptr : (rtvs.empty() ? nullptr : rtvs.data()),
        keepRenderTargets ? nullptr : depthView.Get(),
        keepUnorderedAccessViews ? 0 : uavStartSlot,
        numUavs,
        keepUnorderedAccessViews ? nullptr : (uavs.empty() ? nullptr : uavs.data()),
        keepUnorderedAccessViews ? nullptr : (initialCounts.empty() ? nullptr : initialCounts.data()));
    bridge.setLastHresult(S_OK);
    return true;
}

gm_structs::ID3D11OutputMergerTargetsAndUAVs
id3d11_device_context_om_get_render_targets_and_unordered_access_views(
    const std::uint64_t contextHandle,
    const std::uint32_t renderTargetCount,
    const std::uint32_t uavStartSlot,
    const std::uint32_t uavCount)
{
    gm_structs::ID3D11OutputMergerTargetsAndUAVs output{};
    auto& bridge = id3d11::BridgeState::instance();
    if (renderTargetCount > D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT ||
        !validSlotRange(uavStartSlot, uavCount, D3D11_PS_CS_UAV_REGISTER_COUNT))
    {
        bridge.setLastHresult(E_INVALIDARG);
        return output;
    }

    const auto context = id3d11::acquireContext(contextHandle);
    if (!context)
    {
        return output;
    }

    std::vector<ID3D11RenderTargetView*> rtvs(renderTargetCount, nullptr);
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthView;
    std::vector<ID3D11UnorderedAccessView*> uavs(uavCount, nullptr);
    context->OMGetRenderTargetsAndUnorderedAccessViews(
        renderTargetCount,
        rtvs.empty() ? nullptr : rtvs.data(),
        &depthView,
        uavStartSlot,
        uavCount,
        uavs.empty() ? nullptr : uavs.data());

    bool internFailed = false;
    output.renderTargetViews.reserve(renderTargetCount);
    for (ID3D11RenderTargetView* rawView : rtvs)
    {
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> view;
        view.Attach(rawView);
        const std::uint64_t handle = id3d11::internOptionalDeviceChild(
            view.Get(),
            gm_enums::ID3D11HandleKind::RenderTargetView);
        internFailed = internFailed || (view && handle == 0);
        output.renderTargetViews.push_back(handle);
    }
    output.depthStencilView = id3d11::internOptionalDeviceChild(
        depthView.Get(),
        gm_enums::ID3D11HandleKind::DepthStencilView);
    internFailed = internFailed || (depthView && output.depthStencilView == 0);

    output.unorderedAccessViews.reserve(uavCount);
    for (ID3D11UnorderedAccessView* rawView : uavs)
    {
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> view;
        view.Attach(rawView);
        const std::uint64_t handle = id3d11::internOptionalDeviceChild(
            view.Get(),
            gm_enums::ID3D11HandleKind::UnorderedAccessView);
        internFailed = internFailed || (view && handle == 0);
        output.unorderedAccessViews.push_back(handle);
    }
    bridge.setLastHresult(internFailed ? E_OUTOFMEMORY : S_OK);
    return output;
}
