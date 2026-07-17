#pragma once

#include "ID3D11_native.h"

#include <cstdint>
#include <mutex>
#include <vector>

#include <wrl/client.h>

namespace id3d11
{
    class HandleRegistry final
    {
    public:
        using Handle = std::uint64_t;
        using Kind = gm_enums::ID3D11HandleKind;

        static HandleRegistry& instance() noexcept;

        [[nodiscard]] Handle intern(IUnknown* object, Kind kind);
        [[nodiscard]] bool valid(Handle handle) const noexcept;
        [[nodiscard]] Kind kind(Handle handle) const noexcept;
        [[nodiscard]] Microsoft::WRL::ComPtr<IUnknown> acquire(
            Handle handle,
            Kind expectedKind = Kind::Invalid) const noexcept;
        bool release(Handle handle) noexcept;
        void clear() noexcept;

    private:
        struct Slot final
        {
            Microsoft::WRL::ComPtr<IUnknown> object;
            Kind kind = Kind::Invalid;
            std::uint32_t generation = 1;
            bool occupied = false;
        };

        HandleRegistry() = default;

        [[nodiscard]] static Handle encode(std::uint32_t index, std::uint32_t generation) noexcept;
        [[nodiscard]] static bool decode(
            Handle handle,
            std::uint32_t& index,
            std::uint32_t& generation) noexcept;
        [[nodiscard]] const Slot* find(Handle handle) const noexcept;
        [[nodiscard]] Slot* find(Handle handle) noexcept;
        static void advanceGeneration(Slot& slot) noexcept;

        mutable std::mutex mutex_;
        std::vector<Slot> slots_;
        std::vector<std::uint32_t> freeSlots_;
    };
}
