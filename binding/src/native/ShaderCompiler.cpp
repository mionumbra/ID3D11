#include "ID3D11_native.h"

#include "BridgeState.hpp"

#include <cstring>
#include <string>
#include <string_view>

#include <d3dcompiler.h>
#include <wrl/client.h>

namespace
{
    [[nodiscard]] bool copyBlobToBuffer(
        ID3DBlob* blob,
        const gm::wire::GMBuffer& buffer) noexcept
    {
        if (blob == nullptr || blob->GetBufferSize() == 0)
        {
            return true;
        }

        if (buffer.data() == nullptr || buffer.length() < blob->GetBufferSize())
        {
            return false;
        }

        std::memcpy(buffer.data(), blob->GetBufferPointer(), blob->GetBufferSize());
        return true;
    }
}

gm_structs::ID3D11ShaderCompileResult id3d11_compile_shader(
    const std::string_view source,
    const std::string_view sourceName,
    const std::string_view entryPoint,
    const std::string_view target,
    const std::uint32_t flags1,
    const std::uint32_t flags2,
    const gm::wire::GMBuffer bytecode,
    const gm::wire::GMBuffer errors)
{
    gm_structs::ID3D11ShaderCompileResult output{};
    auto& state = id3d11::BridgeState::instance();
    if (source.empty() || entryPoint.empty() || target.empty())
    {
        output.hresult = E_INVALIDARG;
        state.setLastHresult(E_INVALIDARG);
        return output;
    }

    const std::string sourceNameString(sourceName);
    const std::string entryPointString(entryPoint);
    const std::string targetString(target);
    Microsoft::WRL::ComPtr<ID3DBlob> compiled;
    Microsoft::WRL::ComPtr<ID3DBlob> diagnostics;
    HRESULT hresult = D3DCompile(
        source.data(),
        source.size(),
        sourceNameString.empty() ? nullptr : sourceNameString.c_str(),
        nullptr,
        nullptr,
        entryPointString.c_str(),
        targetString.c_str(),
        flags1,
        flags2,
        &compiled,
        &diagnostics);

    output.bytecodeSize = compiled ? compiled->GetBufferSize() : 0;
    output.errorSize = diagnostics ? diagnostics->GetBufferSize() : 0;
    static_cast<void>(copyBlobToBuffer(diagnostics.Get(), errors));

    if (SUCCEEDED(hresult) && !copyBlobToBuffer(compiled.Get(), bytecode))
    {
        hresult = HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
    }

    output.hresult = static_cast<std::int32_t>(hresult);
    state.setLastHresult(hresult);
    return output;
}
