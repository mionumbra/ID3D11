#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"

#include <d3d11_4.h>
#include <dxgi.h>
#include <wrl/client.h>

namespace
{
    using Handle = id3d11::HandleRegistry::Handle;
    using Kind = id3d11::HandleRegistry::Kind;

    template<typename Interface>
    Handle queryInterface(const Handle handle, const Kind resultKind) noexcept
    {
        auto& state = id3d11::BridgeState::instance();
        auto& registry = id3d11::HandleRegistry::instance();
        const Microsoft::WRL::ComPtr<IUnknown> source = registry.acquire(handle);
        if (!source)
        {
            state.setLastHresult(E_HANDLE);
            return 0;
        }

        Microsoft::WRL::ComPtr<Interface> result;
        const HRESULT queryResult = source.As(&result);
        state.setLastHresult(queryResult);
        if (FAILED(queryResult))
        {
            return 0;
        }

        const Handle resultHandle = registry.intern(result.Get(), resultKind);
        if (resultHandle == 0)
        {
            state.setLastHresult(E_OUTOFMEMORY);
        }
        return resultHandle;
    }
}

std::uint64_t id3d11_handle_query_interface(
    const std::uint64_t handle,
    const gm_enums::ID3D11HandleKind interfaceKind)
{
    using enum gm_enums::ID3D11HandleKind;

#define ID3D11_QUERY_CASE(kindName, interfaceType) \
    case kindName: return queryInterface<interfaceType>(handle, interfaceKind)

    switch (interfaceKind)
    {
        ID3D11_QUERY_CASE(Device, ID3D11Device);
        ID3D11_QUERY_CASE(DeviceContext, ID3D11DeviceContext);
        ID3D11_QUERY_CASE(SwapChain, IDXGISwapChain);
        ID3D11_QUERY_CASE(Buffer, ID3D11Buffer);
        ID3D11_QUERY_CASE(Texture1D, ID3D11Texture1D);
        ID3D11_QUERY_CASE(Texture2D, ID3D11Texture2D);
        ID3D11_QUERY_CASE(Texture3D, ID3D11Texture3D);
        ID3D11_QUERY_CASE(View, ID3D11View);
        ID3D11_QUERY_CASE(Query, ID3D11Query);
        ID3D11_QUERY_CASE(CommandList, ID3D11CommandList);
        ID3D11_QUERY_CASE(Fence, ID3D11Fence);
        ID3D11_QUERY_CASE(Device1, ID3D11Device1);
        ID3D11_QUERY_CASE(Device2, ID3D11Device2);
        ID3D11_QUERY_CASE(Device3, ID3D11Device3);
        ID3D11_QUERY_CASE(Device4, ID3D11Device4);
        ID3D11_QUERY_CASE(Device5, ID3D11Device5);
        ID3D11_QUERY_CASE(DeviceContext1, ID3D11DeviceContext1);
        ID3D11_QUERY_CASE(DeviceContext2, ID3D11DeviceContext2);
        ID3D11_QUERY_CASE(DeviceContext3, ID3D11DeviceContext3);
        ID3D11_QUERY_CASE(DeviceContext4, ID3D11DeviceContext4);
        ID3D11_QUERY_CASE(Multithread, ID3D11Multithread);
        ID3D11_QUERY_CASE(DeviceChild, ID3D11DeviceChild);
        ID3D11_QUERY_CASE(Resource, ID3D11Resource);
        ID3D11_QUERY_CASE(Texture2D1, ID3D11Texture2D1);
        ID3D11_QUERY_CASE(Texture3D1, ID3D11Texture3D1);
        ID3D11_QUERY_CASE(ShaderResourceView, ID3D11ShaderResourceView);
        ID3D11_QUERY_CASE(ShaderResourceView1, ID3D11ShaderResourceView1);
        ID3D11_QUERY_CASE(RenderTargetView, ID3D11RenderTargetView);
        ID3D11_QUERY_CASE(RenderTargetView1, ID3D11RenderTargetView1);
        ID3D11_QUERY_CASE(DepthStencilView, ID3D11DepthStencilView);
        ID3D11_QUERY_CASE(UnorderedAccessView, ID3D11UnorderedAccessView);
        ID3D11_QUERY_CASE(UnorderedAccessView1, ID3D11UnorderedAccessView1);
        ID3D11_QUERY_CASE(VertexShader, ID3D11VertexShader);
        ID3D11_QUERY_CASE(HullShader, ID3D11HullShader);
        ID3D11_QUERY_CASE(DomainShader, ID3D11DomainShader);
        ID3D11_QUERY_CASE(GeometryShader, ID3D11GeometryShader);
        ID3D11_QUERY_CASE(PixelShader, ID3D11PixelShader);
        ID3D11_QUERY_CASE(ComputeShader, ID3D11ComputeShader);
        ID3D11_QUERY_CASE(InputLayout, ID3D11InputLayout);
        ID3D11_QUERY_CASE(SamplerState, ID3D11SamplerState);
        ID3D11_QUERY_CASE(DepthStencilState, ID3D11DepthStencilState);
        ID3D11_QUERY_CASE(BlendState, ID3D11BlendState);
        ID3D11_QUERY_CASE(BlendState1, ID3D11BlendState1);
        ID3D11_QUERY_CASE(RasterizerState, ID3D11RasterizerState);
        ID3D11_QUERY_CASE(RasterizerState1, ID3D11RasterizerState1);
        ID3D11_QUERY_CASE(RasterizerState2, ID3D11RasterizerState2);
        ID3D11_QUERY_CASE(Asynchronous, ID3D11Asynchronous);
        ID3D11_QUERY_CASE(Predicate, ID3D11Predicate);
        ID3D11_QUERY_CASE(Counter, ID3D11Counter);
        ID3D11_QUERY_CASE(Query1, ID3D11Query1);
        ID3D11_QUERY_CASE(ClassInstance, ID3D11ClassInstance);
        ID3D11_QUERY_CASE(ClassLinkage, ID3D11ClassLinkage);
        ID3D11_QUERY_CASE(VideoDecoder, ID3D11VideoDecoder);
        ID3D11_QUERY_CASE(VideoProcessorEnumerator, ID3D11VideoProcessorEnumerator);
        ID3D11_QUERY_CASE(VideoProcessorEnumerator1, ID3D11VideoProcessorEnumerator1);
        ID3D11_QUERY_CASE(VideoProcessor, ID3D11VideoProcessor);
        ID3D11_QUERY_CASE(AuthenticatedChannel, ID3D11AuthenticatedChannel);
        ID3D11_QUERY_CASE(CryptoSession, ID3D11CryptoSession);
        ID3D11_QUERY_CASE(VideoDecoderOutputView, ID3D11VideoDecoderOutputView);
        ID3D11_QUERY_CASE(VideoProcessorInputView, ID3D11VideoProcessorInputView);
        ID3D11_QUERY_CASE(VideoProcessorOutputView, ID3D11VideoProcessorOutputView);
        ID3D11_QUERY_CASE(VideoContext, ID3D11VideoContext);
        ID3D11_QUERY_CASE(VideoContext1, ID3D11VideoContext1);
        ID3D11_QUERY_CASE(VideoContext2, ID3D11VideoContext2);
        ID3D11_QUERY_CASE(VideoContext3, ID3D11VideoContext3);
        ID3D11_QUERY_CASE(VideoDevice, ID3D11VideoDevice);
        ID3D11_QUERY_CASE(VideoDevice1, ID3D11VideoDevice1);
        ID3D11_QUERY_CASE(VideoDevice2, ID3D11VideoDevice2);
        default:
            id3d11::BridgeState::instance().setLastHresult(E_NOINTERFACE);
            return 0;
    }

#undef ID3D11_QUERY_CASE
}
