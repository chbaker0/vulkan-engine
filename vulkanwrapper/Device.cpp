#include "Device.hpp"
#include "Instance.hpp"

#include <cassert>

namespace vkw
{

Device::Device(VkDevice handleIn, VkPhysicalDevice physicalDeviceIn, Instance *instanceIn)
    : handle(handleIn)
    , physicalDevice(physicalDeviceIn)
    , instance(instanceIn)
{
#define X(name) functionPtrs.name = (PFN_##name) instance->functionPtrs.vkGetDeviceProcAddr(handle, #name); assert(functionPtrs.name != nullptr);

    VKW_DEVICE_FUNCTION_LIST

#undef X
}

Device::~Device()
{
    if (handle != nullptr)
    {
        assert(functionPtrs.vkDestroyDevice != nullptr);

        functionPtrs.vkDestroyDevice(handle, nullptr);
    }
}

} // namespace vkw
