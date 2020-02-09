//
// Created by Veto on 07.02.2020.
//

#ifndef VULKAN_TEST_ALLOCATOR_H
#define VULKAN_TEST_ALLOCATOR_H


#include <vulkan/vulkan.h>
#include <memory>

class Allocator {
public:
    inline operator VkAllocationCallbacks() const;

private:
    static void* VKAPI_CALL Allocation(
            void* pUserData,
            size_t size,
            size_t alignment,
            VkSystemAllocationScope allocationScope
            );
    inline void* Allocation(
            size_t size,
            size_t alignment,
            VkSystemAllocationScope allocationScope
    );
    static void* VKAPI_CALL Reallocation(
            void* pUserData,
            void* pOriginal,
            size_t size,
            size_t alignment,
            VkSystemAllocationScope allocationScope
            );
    inline void* Reallocation(
            void* pOriginal,
            size_t size,
            size_t alignment,
            VkSystemAllocationScope allocationScope
    );
    static void VKAPI_CALL Free(
            void* pUserData,
            void* pMemory
            );
    inline void VKAPI_CALL Free(
            void* pMemory
    );
};


#endif //VULKAN_TEST_ALLOCATOR_H
