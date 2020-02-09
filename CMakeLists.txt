cmake_minimum_required(VERSION 3.15)
project(vulkan_test)

find_package(Vulkan REQUIRED)
set(CMAKE_CXX_STANDARD 20)

add_executable(vulkan_test main.cpp device/DeviceVulkan.cpp device/DeviceVulkan.h device/Allocator.cpp device/Allocator.h)
target_compile_definitions(vulkan_test PRIVATE VK_USE_PLATFORM_WIN32_KHR)
target_include_directories(vulkan_test PRIVATE Vulkan::Vulkan)
target_link_libraries(vulkan_test Vulkan::Vulkan)
