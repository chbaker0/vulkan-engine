#include "Instance.hpp"
#include "Device.hpp"

#include <cassert>

namespace vkw
{

Instance::Instance(VkInstance handle_in, GetProcAddrPtr getProcAddr)
    : handle(handle_in)
{
#define X(name) functionPtrs.name = (PFN_##name) getProcAddr(handle, #name); assert(functionPtrs.name != nullptr);

    VKW_INSTANCE_FUNCTION_LIST

#undef X
}

Instance::~Instance()
{
    if (handle != nullptr)
    {
        assert(functionPtrs.vkDestroyInstance != nullptr);

        functionPtrs.vkDestroyInstance(handle, nullptr);
    }
}

std::vector<VkPhysicalDevice> Instance::enumeratePhysicalDevices()
{
    std::uint32_t physicalDeviceCount;
    VkResult result = functionPtrs.vkEnumeratePhysicalDevices(handle, &physicalDeviceCount, nullptr);

    if(result < 0)
    {
        throw InstanceException(result, "Failed to get physical device count");
    }

    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);

    result = functionPtrs.vkEnumeratePhysicalDevices(handle, &physicalDeviceCount, &physicalDevices[0]);

    if(result < 0)
    {
        throw InstanceException(result, "Failed to enumerate physical devices");
    }

    return physicalDevices;
}

VkPhysicalDeviceProperties Instance::getPhysicalDeviceProperties(VkPhysicalDevice physicalDevice) noexcept
{
    VkPhysicalDeviceProperties properties;
    functionPtrs.vkGetPhysicalDeviceProperties(physicalDevice, &properties);
    return properties;
}

std::vector<VkQueueFamilyProperties> Instance::getPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice)
{
    std::uint32_t queueFamilyCount;
    functionPtrs.vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);

    functionPtrs.vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, &queueFamilyProperties[0]);

    return queueFamilyProperties;
}

VkPhysicalDeviceFeatures Instance::getPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice) noexcept
{
    VkPhysicalDeviceFeatures features;

    functionPtrs.vkGetPhysicalDeviceFeatures(physicalDevice, &features);

    return features;
}

Device Instance::createDevice(VkPhysicalDevice phyDev, const VkDeviceCreateInfo& createInfo)
{
    VkDevice deviceHandle;

    VkResult result = functionPtrs.vkCreateDevice(phyDev, &createInfo, nullptr, &deviceHandle);

    if(result < 0)
    {
        throw InstanceException(result, "Failed to create logical device");
    }

    return Device(deviceHandle, phyDev, this);
}

} // namespace vkw
