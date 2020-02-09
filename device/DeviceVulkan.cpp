//
// Created by Veto on 06.02.2020.
//

#include "DeviceVulkan.h"

DeviceVulkan::DeviceVulkan() {
    initLayers();
    init();
    initDevice();
    initQueue();
    getDeviceLayers();
    getExtensions();
    createBuffer();
    createImage();
}

void DeviceVulkan::init() {
    std::vector<VkPhysicalDevice> arr_device;
    auto tmp = vkCreateInstance(
            &m_instance_info,
            nullptr /*new VkAllocationCallbacks(alloc)*/, // its sucks and not compiles
            &m_inst) == VK_SUCCESS;
    if(tmp){
        std::cout << "success" << std::endl;
        uint32_t _count = 0;
        m_res = vkEnumeratePhysicalDevices(m_inst, &_count, nullptr);
        arr_device.resize(_count);
        m_res = vkEnumeratePhysicalDevices(m_inst, &_count, &arr_device[0]);

        vkGetPhysicalDeviceProperties(arr_device.at(0), &m_physical_device_properties);
        std::cout << "physical device: " << m_physical_device_properties.deviceName << "\napi version: " << m_physical_device_properties.apiVersion << std::endl;
        if (m_res == VK_SUCCESS) {
            vkGetPhysicalDeviceMemoryProperties(arr_device.at(0), &m_physical_device_mem_prop);
            m_physical_device = arr_device.at(0);
        }
    }
}

void DeviceVulkan::initQueue() {
    uint32_t _count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(m_physical_device, &_count, nullptr);
    m_queue_prop.resize(_count);
    vkGetPhysicalDeviceQueueFamilyProperties(m_physical_device, &_count, &m_queue_prop.at(0));
}

void DeviceVulkan::initDevice() {
    VkPhysicalDeviceFeatures _supported_features;
    VkPhysicalDeviceFeatures _requested_features;
    vkGetPhysicalDeviceFeatures(m_physical_device, &_supported_features);

    _requested_features.multiDrawIndirect = _supported_features.multiDrawIndirect;
    _requested_features.tessellationShader = VK_TRUE;
    _requested_features.geometryShader = VK_TRUE;

    static std::vector<float> _priority{1};

    const VkDeviceQueueCreateInfo _queue_info{
            VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            nullptr,
            0,
            0,
            1,
            &_priority[0]
    };

   const VkDeviceCreateInfo _device_info{
            VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            nullptr,
            0,
            1,
            &_queue_info,
            0,
            nullptr,
            0,
            nullptr,
            &_requested_features
    };
//_device_info.pQueueCreateInfos[0].pQueuePriorities = NULL;
    m_res = vkCreateDevice(
            m_physical_device,
            &_device_info,
            nullptr,
            &m_device
    );
}

void DeviceVulkan::initLayers() {
    m_instance_info.enabledLayerCount = 2;
    m_instance_info.ppEnabledLayerNames = &m_layers[0];

    uint32_t _count = 0;
    std::vector<VkLayerProperties> _layers_prop_vec;
    auto tmp = vkEnumerateInstanceLayerProperties(&_count, nullptr) == VK_SUCCESS;
    _layers_prop_vec.resize(_count);
    tmp = vkEnumerateInstanceLayerProperties(
            &_count,
            &_layers_prop_vec[0]
    )  == VK_SUCCESS;
    std::cout << "inst layers: " << std::endl;
    for (const auto &_i : _layers_prop_vec) {
        std::cout << _i.layerName << " : " << std::endl;
    }
    std::cout << std::endl;
}

void DeviceVulkan::getExtensions() {
    uint32_t _count;
    std::vector<VkExtensionProperties> _inst_ext_vec;
    vkEnumerateInstanceExtensionProperties(
            nullptr,
            &_count,
            nullptr
            );
    if(_count > 0 ){
        _inst_ext_vec.resize(_count);
        vkEnumerateInstanceExtensionProperties(
                nullptr,
                &_count,
                &_inst_ext_vec[0]
                );
        std::cout << "instance ext: " << std::endl;
        for (const auto &_i : _inst_ext_vec){
            std::cout << _i.extensionName << std::endl;
        }
        std::cout << std::endl;
    }
    vkEnumerateDeviceExtensionProperties(
            m_physical_device,
            nullptr,
            &_count,
            nullptr
            );
    if(_count > 0 ){
        _inst_ext_vec.resize(_count);
        vkEnumerateDeviceExtensionProperties(
                m_physical_device,
                nullptr,
                &_count,
                &_inst_ext_vec[0]
        );
        std::cout << "device ext: " << std::endl;
        for (const auto &_i : _inst_ext_vec){
            std::cout << _i.extensionName << std::endl;
        }
        std::cout << std::endl;
    }
}

void DeviceVulkan::getDeviceLayers() {
    uint32_t _count = 0;
    std::vector<VkLayerProperties> _layers_prop_vec;

    vkEnumerateDeviceLayerProperties(
            m_physical_device,
            &_count,
            nullptr);
    _layers_prop_vec.resize(_count);
    vkEnumerateDeviceLayerProperties(
            m_physical_device,
            &_count,
            &_layers_prop_vec[0]);
    std::cout << "device layers: " << std::endl;
    for (const auto &_i : _layers_prop_vec) {
        std::cout << _i.layerName << " : " << std::endl;
    }
    std::cout << std::endl;
}

DeviceVulkan::~DeviceVulkan() {
    vkDeviceWaitIdle(m_device);
    vkDestroyDevice(m_device, nullptr);
    vkDestroyInstance(m_inst, nullptr);
}

void DeviceVulkan::createBuffer() {
    static const VkBufferCreateInfo _buffer_create_info{
        VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        nullptr,
        0,
        1024*1024,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_SHARING_MODE_EXCLUSIVE,
        0,
        nullptr
        };
    VkBuffer _buffer = VK_NULL_HANDLE;

    m_res = vkCreateBuffer(m_device, &_buffer_create_info, nullptr, &_buffer);
}

void DeviceVulkan::createImage() {
    VkImage _image = VK_NULL_HANDLE;
    static const VkImageCreateInfo _img_image{
        VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        nullptr,
        0,
        VK_IMAGE_TYPE_2D,
        VK_FORMAT_R8G8B8A8_UNORM,
        {1024,1024,1},
        10,
        1,
        VK_SAMPLE_COUNT_1_BIT,
        VK_IMAGE_TILING_OPTIMAL,
        VK_IMAGE_USAGE_SAMPLED_BIT,
        VK_SHARING_MODE_EXCLUSIVE,
        0,
        nullptr,
        VK_IMAGE_LAYOUT_UNDEFINED,
    };
    m_res = vkCreateImage(m_device, &_img_image, nullptr, &_image);
}
