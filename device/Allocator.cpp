//
// Created by Veto on 07.02.2020.
//

#include "Allocator.h"

Allocator::operator VkAllocationCallbacks() const {
    return VkAllocationCallbacks{
            const_cast<Allocator*>(this),
            &Allocation,
            &Reallocation,
            &Free,
            nullptr, nullptr
    };
}

void *Allocator::Allocation(
        void *pUserData,
        size_t size,
        size_t alignment,
        VkSystemAllocationScope allocationScope) {
    return static_cast<Allocator*>(pUserData)->Allocation(size,alignment,allocationScope);

}

void *Allocator::Allocation(
        size_t size,
        size_t alignment,
        VkSystemAllocationScope allocationScope) {
    return _aligned_malloc(size,alignment);
}

void *Allocator::Reallocation(
        void *pUserData,
        void *pOriginal,
        size_t size,
        size_t alignment,
        VkSystemAllocationScope allocationScope) {
    return static_cast<Allocator*>(pUserData)->Reallocation(pOriginal,size,alignment,allocationScope);
}

void *Allocator::Reallocation(
        void *pOriginal,
        size_t size,
        size_t alignment,
        VkSystemAllocationScope allocationScope) {
    return _aligned_realloc(pOriginal, size, alignment);
}

void Allocator::Free(void *pUserData, void *pMemory) {
    return static_cast<Allocator*>(pUserData)->Free(pUserData);
}

void Allocator::Free(void *pMemory) {
    return _aligned_free(pMemory);
}
