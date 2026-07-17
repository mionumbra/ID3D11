#include "HandleRegistry.hpp"

#include <limits>
#include <utility>

namespace id3d11
{
    HandleRegistry& HandleRegistry::instance() noexcept
    {
        static HandleRegistry registry;
        return registry;
    }

    HandleRegistry::Handle HandleRegistry::intern(IUnknown* object, const Kind kind)
    {
        if (object == nullptr || kind == Kind::Invalid)
        {
            return 0;
        }

        Microsoft::WRL::ComPtr<IUnknown> identity;
        if (FAILED(object->QueryInterface(IID_PPV_ARGS(&identity))))
        {
            return 0;
        }

        const std::scoped_lock lock(mutex_);
        for (std::uint32_t index = 0; index < slots_.size(); ++index)
        {
            const Slot& slot = slots_[index];
            if (slot.occupied && slot.kind == kind && slot.object.Get() == identity.Get())
            {
                return encode(index, slot.generation);
            }
        }

        std::uint32_t index = 0;
        if (!freeSlots_.empty())
        {
            index = freeSlots_.back();
            freeSlots_.pop_back();
        }
        else
        {
            if (slots_.size() >= std::numeric_limits<std::uint32_t>::max())
            {
                return 0;
            }

            index = static_cast<std::uint32_t>(slots_.size());
            slots_.emplace_back();
        }

        Slot& slot = slots_[index];
        slot.object = std::move(identity);
        slot.kind = kind;
        slot.occupied = true;
        return encode(index, slot.generation);
    }

    bool HandleRegistry::valid(const Handle handle) const noexcept
    {
        const std::scoped_lock lock(mutex_);
        return find(handle) != nullptr;
    }

    HandleRegistry::Kind HandleRegistry::kind(const Handle handle) const noexcept
    {
        const std::scoped_lock lock(mutex_);
        const Slot* slot = find(handle);
        return slot == nullptr ? Kind::Invalid : slot->kind;
    }

    Microsoft::WRL::ComPtr<IUnknown> HandleRegistry::acquire(
        const Handle handle,
        const Kind expectedKind) const noexcept
    {
        const std::scoped_lock lock(mutex_);
        const Slot* slot = find(handle);
        if (slot == nullptr || (expectedKind != Kind::Invalid && slot->kind != expectedKind))
        {
            return {};
        }

        return slot->object;
    }

    bool HandleRegistry::release(const Handle handle) noexcept
    {
        const std::scoped_lock lock(mutex_);
        Slot* slot = find(handle);
        if (slot == nullptr)
        {
            return false;
        }

        std::uint32_t index = 0;
        std::uint32_t generation = 0;
        static_cast<void>(decode(handle, index, generation));
        slot->object.Reset();
        slot->kind = Kind::Invalid;
        slot->occupied = false;
        advanceGeneration(*slot);
        freeSlots_.push_back(index);
        return true;
    }

    void HandleRegistry::clear() noexcept
    {
        const std::scoped_lock lock(mutex_);
        freeSlots_.clear();
        freeSlots_.reserve(slots_.size());

        for (std::uint32_t index = 0; index < slots_.size(); ++index)
        {
            Slot& slot = slots_[index];
            slot.object.Reset();
            slot.kind = Kind::Invalid;
            slot.occupied = false;
            advanceGeneration(slot);
            freeSlots_.push_back(index);
        }
    }

    HandleRegistry::Handle HandleRegistry::encode(
        const std::uint32_t index,
        const std::uint32_t generation) noexcept
    {
        return (static_cast<Handle>(generation) << 32U) |
            (static_cast<Handle>(index) + 1U);
    }

    bool HandleRegistry::decode(
        const Handle handle,
        std::uint32_t& index,
        std::uint32_t& generation) noexcept
    {
        const std::uint32_t encodedIndex = static_cast<std::uint32_t>(handle);
        generation = static_cast<std::uint32_t>(handle >> 32U);
        if (encodedIndex == 0 || generation == 0)
        {
            return false;
        }

        index = encodedIndex - 1U;
        return true;
    }

    const HandleRegistry::Slot* HandleRegistry::find(const Handle handle) const noexcept
    {
        std::uint32_t index = 0;
        std::uint32_t generation = 0;
        if (!decode(handle, index, generation) || index >= slots_.size())
        {
            return nullptr;
        }

        const Slot& slot = slots_[index];
        return slot.occupied && slot.generation == generation ? &slot : nullptr;
    }

    HandleRegistry::Slot* HandleRegistry::find(const Handle handle) noexcept
    {
        return const_cast<Slot*>(static_cast<const HandleRegistry*>(this)->find(handle));
    }

    void HandleRegistry::advanceGeneration(Slot& slot) noexcept
    {
        ++slot.generation;
        if (slot.generation == 0)
        {
            slot.generation = 1;
        }
    }
}
