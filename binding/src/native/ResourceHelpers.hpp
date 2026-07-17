#pragma once

#include "HandleRegistry.hpp"

#include <cstdint>

#include <d3d11.h>

namespace id3d11
{
    [[nodiscard]] inline HandleRegistry::Kind resourceKind(ID3D11Resource* resource) noexcept
    {
        if (resource == nullptr)
        {
            return HandleRegistry::Kind::Invalid;
        }

        D3D11_RESOURCE_DIMENSION dimension = D3D11_RESOURCE_DIMENSION_UNKNOWN;
        resource->GetType(&dimension);
        switch (dimension)
        {
        case D3D11_RESOURCE_DIMENSION_BUFFER:
            return HandleRegistry::Kind::Buffer;
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
            return HandleRegistry::Kind::Texture1D;
        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
            return HandleRegistry::Kind::Texture2D;
        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
            return HandleRegistry::Kind::Texture3D;
        default:
            return HandleRegistry::Kind::Resource;
        }
    }

    [[nodiscard]] inline std::uint64_t internResource(ID3D11Resource* resource) noexcept
    {
        return HandleRegistry::instance().intern(resource, resourceKind(resource));
    }
}
