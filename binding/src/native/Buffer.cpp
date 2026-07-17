#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"

#include <d3d11.h>
#include <wrl/client.h>

namespace
{
    Microsoft::WRL::ComPtr<ID3D11Device> acquireDevice(const std::uint64_t handle) noexcept
    {
        const Microsoft::WRL::ComPtr<IUnknown> unknown =
            id3d11::HandleRegistry::instance().acquire(
                handle,
                gm_enums::ID3D11HandleKind::Device);
        if (!unknown)
        {
            id3d11::BridgeState::instance().setLastHresult(E_HANDLE);
            return {};
        }

        Microsoft::WRL::ComPtr<ID3D11Device> device;
        const HRESULT result = unknown.As(&device);
        id3d11::BridgeState::instance().setLastHresult(result);
        return SUCCEEDED(result) ? device : Microsoft::WRL::ComPtr<ID3D11Device>{};
    }

    Microsoft::WRL::ComPtr<ID3D11Buffer> acquireBuffer(const std::uint64_t handle) noexcept
    {
        const Microsoft::WRL::ComPtr<IUnknown> unknown =
            id3d11::HandleRegistry::instance().acquire(
                handle,
                gm_enums::ID3D11HandleKind::Buffer);
        if (!unknown)
        {
            id3d11::BridgeState::instance().setLastHresult(E_HANDLE);
            return {};
        }

        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
        const HRESULT result = unknown.As(&buffer);
        id3d11::BridgeState::instance().setLastHresult(result);
        return SUCCEEDED(result) ? buffer : Microsoft::WRL::ComPtr<ID3D11Buffer>{};
    }

    D3D11_BUFFER_DESC toNative(const gm_structs::ID3D11BufferDesc& desc) noexcept
    {
        return {
            .ByteWidth = desc.byteWidth,
            .Usage = static_cast<D3D11_USAGE>(desc.usage),
            .BindFlags = desc.bindFlags,
            .CPUAccessFlags = desc.cpuAccessFlags,
            .MiscFlags = desc.miscFlags,
            .StructureByteStride = desc.structureByteStride,
        };
    }

    gm_structs::ID3D11CreateHandleResult createBuffer(
        const std::uint64_t deviceHandle,
        const gm_structs::ID3D11BufferDesc& desc,
        const gm::wire::GMBuffer* data) noexcept
    {
        gm_structs::ID3D11CreateHandleResult output{};
        auto& state = id3d11::BridgeState::instance();
        const auto device = acquireDevice(deviceHandle);
        if (!device)
        {
            output.hresult = E_HANDLE;
            return output;
        }

        if (desc.byteWidth == 0)
        {
            output.hresult = E_INVALIDARG;
            state.setLastHresult(E_INVALIDARG);
            return output;
        }

        D3D11_SUBRESOURCE_DATA initialData{};
        const D3D11_SUBRESOURCE_DATA* initialDataPointer = nullptr;
        if (data != nullptr)
        {
            if (data->data() == nullptr || data->length() < desc.byteWidth)
            {
                output.hresult = E_INVALIDARG;
                state.setLastHresult(E_INVALIDARG);
                return output;
            }

            initialData.pSysMem = data->data();
            initialDataPointer = &initialData;
        }

        const D3D11_BUFFER_DESC nativeDesc = toNative(desc);
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
        HRESULT result = device->CreateBuffer(&nativeDesc, initialDataPointer, &buffer);
        if (SUCCEEDED(result))
        {
            output.handle = id3d11::HandleRegistry::instance().intern(
                buffer.Get(),
                gm_enums::ID3D11HandleKind::Buffer);
            if (output.handle == 0)
            {
                result = E_OUTOFMEMORY;
            }
        }

        output.hresult = static_cast<std::int32_t>(result);
        state.setLastHresult(result);
        return output;
    }
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_buffer(
    const std::uint64_t device,
    const gm_structs::ID3D11BufferDesc& desc)
{
    return createBuffer(device, desc, nullptr);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_buffer_with_data(
    const std::uint64_t device,
    const gm_structs::ID3D11BufferDesc& desc,
    const gm::wire::GMBuffer data)
{
    return createBuffer(device, desc, &data);
}

gm_structs::ID3D11BufferDesc id3d11_buffer_get_desc(const std::uint64_t bufferHandle)
{
    gm_structs::ID3D11BufferDesc output{};
    const auto buffer = acquireBuffer(bufferHandle);
    if (!buffer)
    {
        return output;
    }

    D3D11_BUFFER_DESC desc{};
    buffer->GetDesc(&desc);
    output.byteWidth = desc.ByteWidth;
    output.usage = static_cast<std::uint32_t>(desc.Usage);
    output.bindFlags = desc.BindFlags;
    output.cpuAccessFlags = desc.CPUAccessFlags;
    output.miscFlags = desc.MiscFlags;
    output.structureByteStride = desc.StructureByteStride;
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return output;
}
