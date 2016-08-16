#ifndef VULKANWRAPPER_COMMANDPOOL_HPP
#define VULKANWRAPPER_COMMANDPOOL_HPP

#include <exception>
#include <string>

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

#include "DeviceObject.hpp"

namespace vkw
{

class CommandPoolException : public std::exception
{
protected:
    VkResult errorResult; //!< \internal VkResult from failing Vulkan function
    std::string details; //!< \internal Human readable string for error

public:
    CommandPoolException(VkResult errorResult_in, std::string details_in) noexcept
        : errorResult(errorResult_in)
        , details(std::move(details_in))
    {
    }

    CommandPoolException(const CommandPoolException& other) = delete;
    CommandPoolException(CommandPoolException&& other) noexcept = default;

    /**
     * \brief Get result from failing Vulkan function
     */
    VkResult getVkResult() const noexcept
    {
        return errorResult;
    }

    virtual const char * what() const noexcept
    {
        return details.c_str();
    }
};

class Device;

class CommandPool
{
public:
    CommandPool(VkCommandPool handle, Device *device_in);

    void reset(bool releaseResources = false);

    VkCommandPool getCommandPool() const noexcept
    {
        return *object;
    }

private:
    Device *device;
    detail::DeviceObject<VkCommandPool> object;
};

} // namespace vkw

#endif // VULKANWRAPPER_COMMANDPOOL_HPP
