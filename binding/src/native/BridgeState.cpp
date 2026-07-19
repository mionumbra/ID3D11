#include "BridgeState.hpp"

#include <utility>
#include <Windows.h>

namespace
{
    bool sameComObject(IUnknown* left, IUnknown* right) noexcept
    {
        if (left == nullptr || right == nullptr)
        {
            return false;
        }

        Microsoft::WRL::ComPtr<IUnknown> leftIdentity;
        Microsoft::WRL::ComPtr<IUnknown> rightIdentity;
        const HRESULT leftResult = left->QueryInterface(IID_PPV_ARGS(&leftIdentity));
        const HRESULT rightResult = right->QueryInterface(IID_PPV_ARGS(&rightIdentity));
        return SUCCEEDED(leftResult) && SUCCEEDED(rightResult) &&
            leftIdentity.Get() == rightIdentity.Get();
    }
}

namespace id3d11
{
    BridgeState& BridgeState::instance() noexcept
    {
        static BridgeState state;
        return state;
    }

    bool BridgeState::initialize(
        ID3D11Device* device,
        ID3D11DeviceContext* context,
        IDXGISwapChain* swapchain) noexcept
    {
        if (device == nullptr || context == nullptr || swapchain == nullptr)
        {
            fail(E_POINTER);
            return false;
        }

        Microsoft::WRL::ComPtr<ID3D11Device> contextDevice;
        context->GetDevice(&contextDevice);
        if (!sameComObject(device, contextDevice.Get()))
        {
            fail(E_INVALIDARG);
            return false;
        }

        Microsoft::WRL::ComPtr<ID3D11Device> swapchainDevice;
        const HRESULT swapchainResult = swapchain->GetDevice(IID_PPV_ARGS(&swapchainDevice));
        if (FAILED(swapchainResult) || !sameComObject(device, swapchainDevice.Get()))
        {
            fail(FAILED(swapchainResult) ? swapchainResult : E_INVALIDARG);
            return false;
        }

        Microsoft::WRL::ComPtr<ID3D11Device> ownedDevice = device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> ownedContext = context;
        Microsoft::WRL::ComPtr<IDXGISwapChain> ownedSwapchain = swapchain;

        {
            const std::scoped_lock lock(mutex_);
            device_ = std::move(ownedDevice);
            context_ = std::move(ownedContext);
            swapchain_ = std::move(ownedSwapchain);
            ownerThreadId_ = GetCurrentThreadId();
        }

        lastHresult_.store(S_OK, std::memory_order_release);
        initialized_.store(true, std::memory_order_release);
        return true;
    }

    void BridgeState::shutdown() noexcept
    {
        {
            const std::scoped_lock lock(mutex_);
            device_.Reset();
            context_.Reset();
            swapchain_.Reset();
            ownerThreadId_ = 0;
        }

        lastHresult_.store(S_OK, std::memory_order_release);
        initialized_.store(false, std::memory_order_release);
    }

    bool BridgeState::initialized() const noexcept
    {
        return initialized_.load(std::memory_order_acquire);
    }

    std::int32_t BridgeState::lastHresult() const noexcept
    {
        return lastHresult_.load(std::memory_order_acquire);
    }

    std::uint32_t BridgeState::ownerThreadId() const noexcept
    {
        const std::scoped_lock lock(mutex_);
        return ownerThreadId_;
    }

    void BridgeState::setLastHresult(const HRESULT result) noexcept
    {
        lastHresult_.store(static_cast<std::int32_t>(result), std::memory_order_release);
    }

    Microsoft::WRL::ComPtr<ID3D11Device> BridgeState::device() const noexcept
    {
        const std::scoped_lock lock(mutex_);
        return device_;
    }

    Microsoft::WRL::ComPtr<ID3D11DeviceContext> BridgeState::context() const noexcept
    {
        const std::scoped_lock lock(mutex_);
        return context_;
    }

    Microsoft::WRL::ComPtr<IDXGISwapChain> BridgeState::swapchain() const noexcept
    {
        const std::scoped_lock lock(mutex_);
        return swapchain_;
    }

    void BridgeState::fail(const HRESULT result) noexcept
    {
        {
            const std::scoped_lock lock(mutex_);
            device_.Reset();
            context_.Reset();
            swapchain_.Reset();
            ownerThreadId_ = 0;
        }

        lastHresult_.store(static_cast<std::int32_t>(result), std::memory_order_release);
        initialized_.store(false, std::memory_order_release);
    }
}
