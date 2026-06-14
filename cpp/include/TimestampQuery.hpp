#pragma once

#include <common.hpp>
#include <d3d11.h>

/// @brief Timestamp query wrapper.
class TimestampQuery final
{
public:
    TimestampQuery(ID3D11Query* query);
    ~TimestampQuery();

    ID3D11Query* GetQuery() const { return Raw; }

private:
    ID3D11Query* Raw = nullptr;
};
