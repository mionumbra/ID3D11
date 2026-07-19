#pragma once

#include <atomic>
#include <cstdint>
#include <mutex>

#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>

namespace id3d11
{
    class BridgeState final
    {
    public:
        static BridgeState& instance() noexcept;

        bool initialize(
            ID3D11Device* device,
            ID3D11DeviceContext* context,
            IDXGISwapChain* swapchain) noexcept;

        void shutdown() noexcept;

        [[nodiscard]] bool initialized() const noexcept;
        [[nodiscard]] std::int32_t lastHresult() const noexcept;
        [[nodiscard]] std::uint32_t ownerThreadId() const noexcept;
        void setLastHresult(HRESULT result) noexcept;

        [[nodiscard]] Microsoft::WRL::ComPtr<ID3D11Device> device() const noexcept;
        [[nodiscard]] Microsoft::WRL::ComPtr<ID3D11DeviceContext> context() const noexcept;
        [[nodiscard]] Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain() const noexcept;

    private:
        BridgeState() = default;

        void fail(HRESULT result) noexcept;

        mutable std::mutex mutex_;
        Microsoft::WRL::ComPtr<ID3D11Device> device_;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;
        Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain_;
        std::atomic_bool initialized_{false};
        std::atomic<std::int32_t> lastHresult_{S_OK};
        std::uint32_t ownerThreadId_ = 0;
    };
}
