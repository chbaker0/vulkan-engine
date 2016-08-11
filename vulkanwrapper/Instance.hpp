/**
 * \brief Wrapper around Vulkan instance functions
 */

#ifndef VULKANWRAPPER_INSTANCE_HPP
#define VULKANWRAPPER_INSTANCE_HPP

#include <exception>
#include <string>
#include <utility>
#include <vector>

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

namespace vkw
{

/**
 * \brief Exception for instance-level failures
 *
 * Represents a failure that occurs inside an Instance.
 */
class InstanceException : public std::exception
{
protected:
    VkResult errorResult; //!< \internal VkResult from failing Vulkan function
    std::string details; //!< \internal Human readable string for error

public:
    InstanceException(VkResult errorResult_in, std::string details_in) noexcept
        : errorResult(errorResult_in)
        , details(std::move(details_in))
    {}

    InstanceException(const InstanceException& other) = default;
    InstanceException(InstanceException&& other) noexcept = default;

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

/**
 * \brief Wrapper around VkInstance
 *
 * Wraps VkInstance and all instance-level functions; holds all instance-level function pointers.
 */
class Instance
{
protected:
    VkInstance handle; //!< \internal Wrapped Vulkan handle

public:
    struct FunctionPtrs
    {
        #include "InstanceFunctionPtrs.inl"
    };

    FunctionPtrs functionPtrs;

    typedef void * (*GetProcAddrPtr)(VkInstance, const char *);

    Instance() noexcept
        : handle(VK_NULL_HANDLE)
    {
    }

    /**
     * Copies VkInstance handle and populates function pointer table.
     *
     * \param handle_in VkInstance handle to be wrapped; takes ownership
     * \param getProcAddr Pointer to function for obtaining Vulkan global and instance-level functions
     */
    Instance(VkInstance handle_in, GetProcAddrPtr getProcAddr);
    Instance(const Instance& other) = delete;
    Instance(Instance&& other) noexcept
        : handle(VK_NULL_HANDLE)
    {
        std::swap(handle, other.handle);
        std::swap(functionPtrs, other.functionPtrs);
    }

    /**
     * \brief Destroys wrapped VkInstance.
     */
    ~Instance();

    Instance& operator = (const Instance& other) = delete;
    Instance& operator = (Instance&& other) noexcept
    {
        std::swap(handle, other.handle);
        std::swap(functionPtrs, other.functionPtrs);
        return *this;
    }

    /**
     * \brief Get wrapped handle; doesn't give up ownership.
     */
    const VkInstance& getInstance() const noexcept
    {
        return handle;
    }

    /**
     * \brief Get wrapped handle and take ownership of it.
     */
    VkInstance releaseInstance() noexcept
    {
        VkInstance tempHandle = handle;
        handle = nullptr;
        return tempHandle;
    }

    std::vector<VkPhysicalDevice> enumeratePhysicalDevices();
    VkPhysicalDeviceProperties getPhysicalDeviceProperties(VkPhysicalDevice physicalDevice) noexcept;
    std::vector<VkQueueFamilyProperties> getPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice);
    VkPhysicalDeviceFeatures getPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice) noexcept;

    /**
     * \brief Create Device
     *
     * Uses a physical device handle and VkDeviceCreateInfo structure to internally call
     * vkCreateInstance, and then creates Device object to wrap new Vulkan device. Since
     * Device holds pointer to the Instance it is created from, this Instance must last
     * at least as long as the created Device.
     */
    Device createDevice(VkPhysicalDevice phyDev, const VkDeviceCreateInfo& createInfo);
};

} // namespace vkw

#endif // VULKANWRAPPER_INSTANCE_HPP
