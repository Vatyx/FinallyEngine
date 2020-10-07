#pragma once

#include <concepts>
#include <cstdint>
#include <vector>

namespace Finally::Core
{

const size_t StartingCapacity = 40;

using IDType = uint32_t;
using IndexType = uint32_t;

struct ID
{
    ID(IDType InId, IndexType InIndex) : Id(InId), Index(InIndex) {}

    IDType Id;
    IndexType Index;
};

template <typename T>
class SparseSet
{
public:
    SparseSet() = default;

    SparseSet(const SparseSet&) = default;
    SparseSet& operator=(const SparseSet&) = default;
    SparseSet(SparseSet&&) noexcept = default;
    SparseSet& operator=(SparseSet&&) noexcept = default;

    bool Contains(const ID& Id);
    T* Find(const ID& Id);
    ID Add(T&& Element);
    void Remove(const ID& Id);

private:
    [[nodiscard]] IDType GenerateNextId() { return NextID++; }
    [[nodiscard]] bool IsFreelistValid() const { return FreelistHead != UINT32_MAX; }
    [[nodiscard]] IndexType ConsumeFreelistSlot();
    void InsertFreelistSlot(IndexType Slot);

    std::vector<ID> IndicesArray;
    std::vector<T> ElementsArray;

    IDType NextID = 0;
    IndexType FreelistHead = UINT32_MAX;
};

}  // namespace Finally::ECS