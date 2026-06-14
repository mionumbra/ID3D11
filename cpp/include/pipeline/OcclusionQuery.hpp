#pragma once

#include <common.hpp>
#include <Trackable.hpp>
#include <d3d11.h>

/// @brief Occlusion query wrapper.
class OcclusionQuery final : public Trackable
{
public:
    OcclusionQuery(ID3D11Query* query);
    ~OcclusionQuery();

    ID3D11Query* GetQuery() const { return Raw; }

private:
    ID3D11Query* Raw = nullptr;
};
