#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"
#include "NativeHelpers.hpp"

#include <cstddef>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

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

    template<typename Interface>
    [[nodiscard]] CreateResult finishCreate(
        const HRESULT hresult,
        Interface* object,
        const gm_enums::ID3D11HandleKind kind) noexcept
    {
        HRESULT finalResult = hresult;
        std::uint64_t handle = 0;
        if (SUCCEEDED(finalResult))
        {
            handle = id3d11::HandleRegistry::instance().intern(object, kind);
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

    [[nodiscard]] bool validBytecode(
        const gm::wire::GMBuffer& bytecode,
        const std::uint64_t bytecodeSize) noexcept
    {
        return bytecode.data() != nullptr && bytecodeSize != 0 &&
            bytecodeSize <= bytecode.length() &&
            bytecodeSize <= std::numeric_limits<std::size_t>::max();
    }

    [[nodiscard]] bool acquireClassLinkage(
        const std::uint64_t handle,
        Microsoft::WRL::ComPtr<ID3D11ClassLinkage>& linkage) noexcept
    {
        if (handle == 0)
        {
            linkage.Reset();
            return true;
        }

        linkage = id3d11::acquireInterface<ID3D11ClassLinkage>(handle);
        return linkage != nullptr;
    }

    template<typename ShaderInterface, typename Creator>
    [[nodiscard]] CreateResult createShader(
        const std::uint64_t deviceHandle,
        const gm::wire::GMBuffer& bytecode,
        const std::uint64_t bytecodeSize,
        const std::uint64_t classLinkageHandle,
        const gm_enums::ID3D11HandleKind kind,
        Creator&& creator) noexcept
    {
        const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
        if (!device)
        {
            return failedResult(E_HANDLE);
        }
        if (!validBytecode(bytecode, bytecodeSize))
        {
            return failedResult(E_INVALIDARG);
        }

        Microsoft::WRL::ComPtr<ID3D11ClassLinkage> linkage;
        if (!acquireClassLinkage(classLinkageHandle, linkage))
        {
            return failedResult(E_HANDLE);
        }

        Microsoft::WRL::ComPtr<ShaderInterface> shader;
        const HRESULT hresult = std::forward<Creator>(creator)(
            device.Get(),
            bytecode.data(),
            static_cast<std::size_t>(bytecodeSize),
            linkage.Get(),
            &shader);
        return finishCreate(hresult, shader.Get(), kind);
    }
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_vertex_shader(
    const std::uint64_t device,
    const gm::wire::GMBuffer bytecode,
    const std::uint64_t bytecodeSize,
    const std::uint64_t classLinkage)
{
    return createShader<ID3D11VertexShader>(
        device,
        bytecode,
        bytecodeSize,
        classLinkage,
        gm_enums::ID3D11HandleKind::VertexShader,
        [](ID3D11Device* nativeDevice, const void* data, const std::size_t size,
            ID3D11ClassLinkage* linkage, ID3D11VertexShader** shader) {
            return nativeDevice->CreateVertexShader(data, size, linkage, shader);
        });
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_hull_shader(
    const std::uint64_t device,
    const gm::wire::GMBuffer bytecode,
    const std::uint64_t bytecodeSize,
    const std::uint64_t classLinkage)
{
    return createShader<ID3D11HullShader>(
        device,
        bytecode,
        bytecodeSize,
        classLinkage,
        gm_enums::ID3D11HandleKind::HullShader,
        [](ID3D11Device* nativeDevice, const void* data, const std::size_t size,
            ID3D11ClassLinkage* linkage, ID3D11HullShader** shader) {
            return nativeDevice->CreateHullShader(data, size, linkage, shader);
        });
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_domain_shader(
    const std::uint64_t device,
    const gm::wire::GMBuffer bytecode,
    const std::uint64_t bytecodeSize,
    const std::uint64_t classLinkage)
{
    return createShader<ID3D11DomainShader>(
        device,
        bytecode,
        bytecodeSize,
        classLinkage,
        gm_enums::ID3D11HandleKind::DomainShader,
        [](ID3D11Device* nativeDevice, const void* data, const std::size_t size,
            ID3D11ClassLinkage* linkage, ID3D11DomainShader** shader) {
            return nativeDevice->CreateDomainShader(data, size, linkage, shader);
        });
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_geometry_shader(
    const std::uint64_t device,
    const gm::wire::GMBuffer bytecode,
    const std::uint64_t bytecodeSize,
    const std::uint64_t classLinkage)
{
    return createShader<ID3D11GeometryShader>(
        device,
        bytecode,
        bytecodeSize,
        classLinkage,
        gm_enums::ID3D11HandleKind::GeometryShader,
        [](ID3D11Device* nativeDevice, const void* data, const std::size_t size,
            ID3D11ClassLinkage* linkage, ID3D11GeometryShader** shader) {
            return nativeDevice->CreateGeometryShader(data, size, linkage, shader);
        });
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_pixel_shader(
    const std::uint64_t device,
    const gm::wire::GMBuffer bytecode,
    const std::uint64_t bytecodeSize,
    const std::uint64_t classLinkage)
{
    return createShader<ID3D11PixelShader>(
        device,
        bytecode,
        bytecodeSize,
        classLinkage,
        gm_enums::ID3D11HandleKind::PixelShader,
        [](ID3D11Device* nativeDevice, const void* data, const std::size_t size,
            ID3D11ClassLinkage* linkage, ID3D11PixelShader** shader) {
            return nativeDevice->CreatePixelShader(data, size, linkage, shader);
        });
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_compute_shader(
    const std::uint64_t device,
    const gm::wire::GMBuffer bytecode,
    const std::uint64_t bytecodeSize,
    const std::uint64_t classLinkage)
{
    return createShader<ID3D11ComputeShader>(
        device,
        bytecode,
        bytecodeSize,
        classLinkage,
        gm_enums::ID3D11HandleKind::ComputeShader,
        [](ID3D11Device* nativeDevice, const void* data, const std::size_t size,
            ID3D11ClassLinkage* linkage, ID3D11ComputeShader** shader) {
            return nativeDevice->CreateComputeShader(data, size, linkage, shader);
        });
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_geometry_shader_with_stream_output(
    const std::uint64_t deviceHandle,
    const gm::wire::GMBuffer bytecode,
    const std::uint64_t bytecodeSize,
    const std::vector<gm_structs::ID3D11StreamOutputDeclarationEntry>& declarations,
    const std::vector<std::uint32_t>& bufferStrides,
    const std::uint32_t rasterizedStream,
    const std::uint64_t classLinkageHandle)
{
    const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
    if (!device)
    {
        return failedResult(E_HANDLE);
    }
    if (!validBytecode(bytecode, bytecodeSize) || declarations.empty() ||
        declarations.size() > std::numeric_limits<UINT>::max() ||
        bufferStrides.empty() || bufferStrides.size() > D3D11_SO_BUFFER_SLOT_COUNT ||
        (rasterizedStream != D3D11_SO_NO_RASTERIZED_STREAM &&
            rasterizedStream >= D3D11_SO_STREAM_COUNT))
    {
        return failedResult(E_INVALIDARG);
    }

    std::vector<D3D11_SO_DECLARATION_ENTRY> nativeDeclarations;
    nativeDeclarations.reserve(declarations.size());
    for (const auto& declaration : declarations)
    {
        if (declaration.stream >= D3D11_SO_STREAM_COUNT ||
            declaration.startComponent > 3 || declaration.componentCount == 0 ||
            declaration.componentCount > 4 ||
            declaration.startComponent + declaration.componentCount > 4 ||
            declaration.outputSlot >= D3D11_SO_BUFFER_SLOT_COUNT)
        {
            return failedResult(E_INVALIDARG);
        }

        nativeDeclarations.push_back({
            .Stream = declaration.stream,
            .SemanticName = declaration.semanticName.empty()
                ? nullptr
                : declaration.semanticName.c_str(),
            .SemanticIndex = declaration.semanticIndex,
            .StartComponent = static_cast<BYTE>(declaration.startComponent),
            .ComponentCount = static_cast<BYTE>(declaration.componentCount),
            .OutputSlot = static_cast<BYTE>(declaration.outputSlot),
        });
    }

    Microsoft::WRL::ComPtr<ID3D11ClassLinkage> linkage;
    if (!acquireClassLinkage(classLinkageHandle, linkage))
    {
        return failedResult(E_HANDLE);
    }

    Microsoft::WRL::ComPtr<ID3D11GeometryShader> shader;
    const HRESULT hresult = device->CreateGeometryShaderWithStreamOutput(
        bytecode.data(),
        static_cast<std::size_t>(bytecodeSize),
        nativeDeclarations.data(),
        static_cast<UINT>(nativeDeclarations.size()),
        bufferStrides.data(),
        static_cast<UINT>(bufferStrides.size()),
        rasterizedStream,
        linkage.Get(),
        &shader);
    return finishCreate(
        hresult,
        shader.Get(),
        gm_enums::ID3D11HandleKind::GeometryShader);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_input_layout(
    const std::uint64_t deviceHandle,
    const std::vector<gm_structs::ID3D11InputElementDesc>& elements,
    const gm::wire::GMBuffer shaderBytecode,
    const std::uint64_t bytecodeSize)
{
    const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
    if (!device)
    {
        return failedResult(E_HANDLE);
    }
    if (!validBytecode(shaderBytecode, bytecodeSize) || elements.empty() ||
        elements.size() > D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT)
    {
        return failedResult(E_INVALIDARG);
    }

    std::vector<D3D11_INPUT_ELEMENT_DESC> nativeElements;
    nativeElements.reserve(elements.size());
    for (const auto& element : elements)
    {
        if (element.semanticName.empty() ||
            element.inputSlot >= D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT ||
            element.inputSlotClass > D3D11_INPUT_PER_INSTANCE_DATA ||
            (element.inputSlotClass == D3D11_INPUT_PER_VERTEX_DATA &&
                element.instanceDataStepRate != 0))
        {
            return failedResult(E_INVALIDARG);
        }

        nativeElements.push_back({
            .SemanticName = element.semanticName.c_str(),
            .SemanticIndex = element.semanticIndex,
            .Format = static_cast<DXGI_FORMAT>(element.format),
            .InputSlot = element.inputSlot,
            .AlignedByteOffset = element.alignedByteOffset,
            .InputSlotClass = static_cast<D3D11_INPUT_CLASSIFICATION>(element.inputSlotClass),
            .InstanceDataStepRate = element.instanceDataStepRate,
        });
    }

    Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
    const HRESULT hresult = device->CreateInputLayout(
        nativeElements.data(),
        static_cast<UINT>(nativeElements.size()),
        shaderBytecode.data(),
        static_cast<std::size_t>(bytecodeSize),
        &layout);
    return finishCreate(hresult, layout.Get(), gm_enums::ID3D11HandleKind::InputLayout);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_class_linkage(
    const std::uint64_t deviceHandle)
{
    const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
    if (!device)
    {
        return failedResult(E_HANDLE);
    }

    Microsoft::WRL::ComPtr<ID3D11ClassLinkage> linkage;
    const HRESULT hresult = device->CreateClassLinkage(&linkage);
    return finishCreate(hresult, linkage.Get(), gm_enums::ID3D11HandleKind::ClassLinkage);
}
