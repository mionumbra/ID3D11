#include "ID3D11_native.h"

#include "BridgeState.hpp"
#include "HandleRegistry.hpp"
#include "NativeHelpers.hpp"

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include <d3d11.h>
#include <wrl/client.h>

namespace
{
    using CreateResult = gm_structs::ID3D11CreateHandleResult;

    constexpr std::uint32_t maxCounterStringBytes = 1024U * 1024U;

    [[nodiscard]] CreateResult failedCreate(const HRESULT hresult) noexcept
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

    [[nodiscard]] D3D11_QUERY_DESC toNative(const gm_structs::ID3D11QueryDesc& desc) noexcept
    {
        return {
            .Query = static_cast<D3D11_QUERY>(desc.query),
            .MiscFlags = desc.miscFlags,
        };
    }

    [[nodiscard]] gm_structs::ID3D11QueryDesc fromNative(
        const D3D11_QUERY_DESC& desc) noexcept
    {
        return {
            .query = static_cast<std::uint32_t>(desc.Query),
            .miscFlags = desc.MiscFlags,
        };
    }

    [[nodiscard]] D3D11_COUNTER_DESC toNative(
        const gm_structs::ID3D11CounterDesc& desc) noexcept
    {
        return {
            .Counter = static_cast<D3D11_COUNTER>(desc.counter),
            .MiscFlags = desc.miscFlags,
        };
    }

    [[nodiscard]] gm_structs::ID3D11CounterDesc fromNative(
        const D3D11_COUNTER_DESC& desc) noexcept
    {
        return {
            .counter = static_cast<std::uint32_t>(desc.Counter),
            .miscFlags = desc.MiscFlags,
        };
    }

    [[nodiscard]] std::string readCounterString(const std::vector<char>& bytes)
    {
        const auto terminator = std::find(bytes.begin(), bytes.end(), '\0');
        return std::string(bytes.begin(), terminator);
    }

    [[nodiscard]] bool validCounterStringLength(const UINT length) noexcept
    {
        return length <= maxCounterStringBytes;
    }
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_query(
    const std::uint64_t deviceHandle,
    const gm_structs::ID3D11QueryDesc& desc)
{
    const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
    if (!device)
    {
        return failedCreate(E_HANDLE);
    }

    const D3D11_QUERY_DESC nativeDesc = toNative(desc);
    Microsoft::WRL::ComPtr<ID3D11Query> query;
    const HRESULT hresult = device->CreateQuery(&nativeDesc, &query);
    return finishCreate(hresult, query.Get(), gm_enums::ID3D11HandleKind::Query);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_predicate(
    const std::uint64_t deviceHandle,
    const gm_structs::ID3D11QueryDesc& desc)
{
    const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
    if (!device)
    {
        return failedCreate(E_HANDLE);
    }

    const D3D11_QUERY_DESC nativeDesc = toNative(desc);
    Microsoft::WRL::ComPtr<ID3D11Predicate> predicate;
    const HRESULT hresult = device->CreatePredicate(&nativeDesc, &predicate);
    return finishCreate(hresult, predicate.Get(), gm_enums::ID3D11HandleKind::Predicate);
}

gm_structs::ID3D11CreateHandleResult id3d11_device_create_counter(
    const std::uint64_t deviceHandle,
    const gm_structs::ID3D11CounterDesc& desc)
{
    const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
    if (!device)
    {
        return failedCreate(E_HANDLE);
    }

    const D3D11_COUNTER_DESC nativeDesc = toNative(desc);
    Microsoft::WRL::ComPtr<ID3D11Counter> counter;
    const HRESULT hresult = device->CreateCounter(&nativeDesc, &counter);
    return finishCreate(hresult, counter.Get(), gm_enums::ID3D11HandleKind::Counter);
}

std::uint32_t id3d11_asynchronous_get_data_size(const std::uint64_t asynchronousHandle)
{
    const auto asynchronous = id3d11::acquireInterface<ID3D11Asynchronous>(
        asynchronousHandle);
    if (!asynchronous)
    {
        return 0;
    }

    const UINT size = asynchronous->GetDataSize();
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return size;
}

gm_structs::ID3D11QueryDesc id3d11_query_get_desc(const std::uint64_t queryHandle)
{
    const auto query = id3d11::acquireInterface<ID3D11Query>(queryHandle);
    if (!query)
    {
        return {};
    }

    D3D11_QUERY_DESC desc{};
    query->GetDesc(&desc);
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return fromNative(desc);
}

gm_structs::ID3D11CounterDesc id3d11_counter_get_desc(const std::uint64_t counterHandle)
{
    const auto counter = id3d11::acquireInterface<ID3D11Counter>(counterHandle);
    if (!counter)
    {
        return {};
    }

    D3D11_COUNTER_DESC desc{};
    counter->GetDesc(&desc);
    id3d11::BridgeState::instance().setLastHresult(S_OK);
    return fromNative(desc);
}

gm_structs::ID3D11CheckCounterResult id3d11_device_check_counter(
    const std::uint64_t deviceHandle,
    const gm_structs::ID3D11CounterDesc& desc)
{
    gm_structs::ID3D11CheckCounterResult output{};
    const auto device = id3d11::acquireInterface<ID3D11Device>(deviceHandle);
    if (!device)
    {
        output.hresult = E_HANDLE;
        return output;
    }

    const D3D11_COUNTER_DESC nativeDesc = toNative(desc);
    D3D11_COUNTER_TYPE type = D3D11_COUNTER_TYPE_FLOAT32;
    UINT activeCounters = 0;
    UINT nameLength = 0;
    UINT unitsLength = 0;
    UINT descriptionLength = 0;
    HRESULT hresult = device->CheckCounter(
        &nativeDesc,
        &type,
        &activeCounters,
        nullptr,
        &nameLength,
        nullptr,
        &unitsLength,
        nullptr,
        &descriptionLength);
    if (FAILED(hresult))
    {
        output.hresult = static_cast<std::int32_t>(hresult);
        id3d11::BridgeState::instance().setLastHresult(hresult);
        return output;
    }
    if (!validCounterStringLength(nameLength) ||
        !validCounterStringLength(unitsLength) ||
        !validCounterStringLength(descriptionLength))
    {
        output.hresult = E_OUTOFMEMORY;
        id3d11::BridgeState::instance().setLastHresult(E_OUTOFMEMORY);
        return output;
    }

    std::vector<char> name(static_cast<std::size_t>(nameLength) + 1U, '\0');
    std::vector<char> units(static_cast<std::size_t>(unitsLength) + 1U, '\0');
    std::vector<char> description(static_cast<std::size_t>(descriptionLength) + 1U, '\0');
    ++nameLength;
    ++unitsLength;
    ++descriptionLength;
    hresult = device->CheckCounter(
        &nativeDesc,
        &type,
        &activeCounters,
        name.data(),
        &nameLength,
        units.data(),
        &unitsLength,
        description.data(),
        &descriptionLength);

    output.hresult = static_cast<std::int32_t>(hresult);
    if (SUCCEEDED(hresult))
    {
        output.type = static_cast<std::uint32_t>(type);
        output.activeCounters = activeCounters;
        output.name = readCounterString(name);
        output.units = readCounterString(units);
        output.description = readCounterString(description);
    }
    id3d11::BridgeState::instance().setLastHresult(hresult);
    return output;
}
