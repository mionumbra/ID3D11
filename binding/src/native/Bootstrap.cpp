#include "BridgeState.hpp"
#include "HandleRegistry.hpp"

#include "core/GMExtUtils.h"

GMEXPORT double __id3d11_bootstrap_raw(
    char* device,
    char* context,
    char* swapchain)
{
    const bool initialized = id3d11::BridgeState::instance().initialize(
        reinterpret_cast<ID3D11Device*>(device),
        reinterpret_cast<ID3D11DeviceContext*>(context),
        reinterpret_cast<IDXGISwapChain*>(swapchain));

    id3d11::HandleRegistry::instance().clear();
    return initialized ? 1.0 : 0.0;
}
