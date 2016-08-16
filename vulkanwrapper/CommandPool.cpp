#include "CommandPool.hpp"

#include "Device.hpp"

namespace vkw
{

CommandPool::CommandPool(VkCommandPool handle, Device *device_in)
    : device(device_in)
    , object(device->getDevice(), handle, device->functionPtrs.vkDestroyCommandPool)
{
}

void CommandPool::reset(bool releaseResources)
{
    VkCommandPoolResetFlags flags = 0;

    if (releaseResources)
    {
        flags |= VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT;
    }

    VkResult result = device->functionPtrs.vkResetCommandPool(device->getDevice(), *object, flags);

    if (result != VK_SUCCESS)
    {
        throw CommandPoolException(result, "Failed to reset command pool");
    }
}

} // namespace vkw
