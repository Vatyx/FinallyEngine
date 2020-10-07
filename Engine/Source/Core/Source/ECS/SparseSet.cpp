#include "Core/ECS/SparseSet.h"

namespace Finally::Core
{

template <typename T>
bool SparseSet<T>::Contains(const ID& Id)
{
    const ID& FoundId = IndicesArray[Id.Index];
    return FoundId.Id == Id.Id;
}

template <typename T>
T* SparseSet<T>::Find(const ID& Id)
{
    const ID& FoundId = IndicesArray[Id.Index];
    if (FoundId.Id == Id.Id)
    {
        return ElementsArray[FoundId.Index];
    }
    else
    {
        return nullptr;
    }
}

template <typename T>
ID SparseSet<T>::Add(T&& Element)
{
    IDType NewID = GenerateNextId();
    ElementsArray.emplace_back(Element);

    if (IsFreelistValid())
    {
        IndexType Slot = ConsumeFreelistSlot();
        IndicesArray[Slot].Index = ElementsArray.size() - 1;
        IndicesArray[Slot].Id = NewID;
        return ID{ NewID, Slot };
    }

    IndicesArray.emplace(NewID, ElementsArray.size() - 1);
    return ID{ NewID, IndicesArray.size() - 1 };
}

template <typename T>
void SparseSet<T>::Remove(const ID& Id)
{
}

template <typename T>
IndexType SparseSet<T>::ConsumeFreelistSlot()
{
    assert(IsFreelistValid());

    IndexType Slot = FreelistHead;
    FreelistHead = IndicesArray[FreelistHead].Index;
    return Slot;
}

template <typename T>
void SparseSet<T>::InsertFreelistSlot(IndexType Slot)
{
    IndicesArray[Slot].Index = FreelistHead;
    FreelistHead = Slot;
}

}  // namespace Finally::ECS