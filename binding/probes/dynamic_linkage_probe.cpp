#include <Windows.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <new>

using Microsoft::WRL::ComPtr;

namespace
{
    constexpr char kShaderSource[] =
        "interface IColor { float4 GetColor(); }; "
        "class ColorClass : IColor { float4 color; "
        "float4 GetColor() { return color; } }; "
        "cbuffer DynamicData : register(b0) { ColorClass storedColor; }; "
        "IColor activeColor; "
        "float4 main() : SV_Target { return activeColor.GetColor(); }";

    void printMessages(ID3D11InfoQueue* queue)
    {
        if (!queue)
        {
            return;
        }

        const UINT64 count = queue->GetNumStoredMessagesAllowedByRetrievalFilter();
        for (UINT64 index = 0; index < count; ++index)
        {
            SIZE_T size = 0;
            if (FAILED(queue->GetMessage(index, nullptr, &size)) || size == 0)
            {
                continue;
            }

            auto* storage = new (std::nothrow) std::byte[size];
            if (!storage)
            {
                return;
            }

            auto* message = reinterpret_cast<D3D11_MESSAGE*>(storage);
            if (SUCCEEDED(queue->GetMessage(index, message, &size)))
            {
                std::printf(
                    "debug-layer category=%u severity=%u id=%u: %.*s\n",
                    static_cast<unsigned>(message->Category),
                    static_cast<unsigned>(message->Severity),
                    static_cast<unsigned>(message->ID),
                    static_cast<int>(message->DescriptionByteLength),
                    message->pDescription);
            }
            delete[] storage;
        }
        queue->ClearStoredMessages();
    }
}

int main(const int argc, char** argv)
{
    std::setvbuf(stdout, nullptr, _IONBF, 0);

    const bool useWarp = argc > 1 && std::strcmp(argv[1], "--warp") == 0;
    const D3D_DRIVER_TYPE driverType = useWarp
        ? D3D_DRIVER_TYPE_WARP
        : D3D_DRIVER_TYPE_HARDWARE;
    std::printf("driver=%s\n", useWarp ? "WARP" : "hardware");

    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    D3D_FEATURE_LEVEL featureLevel{};
    HRESULT result = D3D11CreateDevice(
        nullptr,
        driverType,
        nullptr,
        D3D11_CREATE_DEVICE_DEBUG,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &device,
        &featureLevel,
        &context);
    std::printf(
        "D3D11CreateDevice(debug) hr=0x%08X feature=0x%X\n",
        static_cast<unsigned>(result),
        static_cast<unsigned>(featureLevel));
    if (FAILED(result))
    {
        return 1;
    }

    ComPtr<ID3D11InfoQueue> infoQueue;
    device.As(&infoQueue);

    ComPtr<ID3DBlob> bytecode;
    ComPtr<ID3DBlob> errors;
    result = D3DCompile(
        kShaderSource,
        sizeof(kShaderSource) - 1,
        "id3d11_dynamic_linkage_probe",
        nullptr,
        nullptr,
        "main",
        "ps_5_0",
        D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG,
        0,
        &bytecode,
        &errors);
    std::printf("D3DCompile hr=0x%08X\n", static_cast<unsigned>(result));
    if (errors && errors->GetBufferSize() > 0)
    {
        std::printf(
            "%.*s\n",
            static_cast<int>(errors->GetBufferSize()),
            static_cast<const char*>(errors->GetBufferPointer()));
    }
    if (FAILED(result))
    {
        return 2;
    }

    ComPtr<ID3D11ClassLinkage> linkage;
    result = device->CreateClassLinkage(&linkage);
    std::printf("CreateClassLinkage hr=0x%08X\n", static_cast<unsigned>(result));
    if (FAILED(result))
    {
        return 3;
    }

    ComPtr<ID3D11PixelShader> shader;
    result = device->CreatePixelShader(
        bytecode->GetBufferPointer(),
        bytecode->GetBufferSize(),
        linkage.Get(),
        &shader);
    std::printf("CreatePixelShader hr=0x%08X\n", static_cast<unsigned>(result));
    if (FAILED(result))
    {
        printMessages(infoQueue.Get());
        return 4;
    }

    ComPtr<ID3D11ClassInstance> instance;
    result = linkage->GetClassInstance("storedColor", 0, &instance);
    std::printf("GetClassInstance hr=0x%08X instance=%p\n", static_cast<unsigned>(result), instance.Get());
    if (FAILED(result))
    {
        printMessages(infoQueue.Get());
        return 5;
    }

    D3D11_CLASS_INSTANCE_DESC desc{};
    instance->GetDesc(&desc);
    std::printf(
        "instance id=%u index=%u type=%u cbuffer=%u created=%u\n",
        desc.InstanceId,
        desc.InstanceIndex,
        desc.TypeId,
        desc.ConstantBuffer,
        static_cast<unsigned>(desc.Created));

    ID3D11ClassInstance* instances[] = {instance.Get()};
    context->PSSetShader(shader.Get(), instances, 1);
    context->Flush();
    std::puts("PSSetShader(dynamic) returned; waiting for asynchronous driver work");
    printMessages(infoQueue.Get());
    Sleep(3000);

    context->PSSetShader(nullptr, nullptr, 0);
    context->ClearState();
    context->Flush();
    std::puts("dynamic shader cleared; releasing objects");
    printMessages(infoQueue.Get());

    instance.Reset();
    shader.Reset();
    linkage.Reset();
    bytecode.Reset();
    Sleep(3000);
    printMessages(infoQueue.Get());
    std::puts("probe completed");
    return 0;
}
