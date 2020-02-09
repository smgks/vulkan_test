//
// Created by Veto on 06.02.2020.
//

#ifndef VULKAN_TEST_DEVICEVULKAN_H
#define VULKAN_TEST_DEVICEVULKAN_H

#include <iostream>
#include <vector>
#include <array>
#include <vulkan/vulkan.h>

#include "Allocator.h"

class DeviceVulkan{
public:
    DeviceVulkan();
    ~DeviceVulkan();

private:
    void initLayers(); // TODO : init layers there
    void init();
    void initQueue();
    void initDevice();
    void getDeviceLayers();
    void getExtensions(); // TODO : init ext there
    void createBuffer();
    void createImage();
private:
    const std::vector<const char *> m_layers{
            "VK_LAYER_LUNARG_api_dump",
            "VK_LAYER_LUNARG_standard_validation"
    };

    Allocator alloc{};

    /* logical device */
    VkDevice m_device;
    /* queue */
    std::vector<VkQueueFamilyProperties> m_queue_prop;
    /* physical device and info*/
    VkResult m_res{};   // TODO: may be i should use it?
    VkInstance m_inst;
    VkPhysicalDevice m_physical_device;
    VkPhysicalDeviceProperties m_physical_device_properties;

    VkPhysicalDeviceMemoryProperties m_physical_device_mem_prop;

    VkApplicationInfo m_app_info{
            VK_STRUCTURE_TYPE_APPLICATION_INFO,
            nullptr,
            "Vulkan test app",
            1,
            nullptr,
            VK_MAKE_VERSION(1,0,0)
    };
    VkInstanceCreateInfo m_instance_info{
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            nullptr,
            0,
            &m_app_info,
    };
    /* logical device */
    VkDeviceCreateInfo device_instance_info;

};


#endif //VULKAN_TEST_DEVICEVULKAN_H
