/**
 * \brief Wrapper around Vulkan device functions
 */

#ifndef VULKANWRAPPER_DEVICE_HPP
#define VULKANWRAPPER_DEVICE_HPP

#include <exception>
#include <string>
#include <utility>
#include <vector>

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

namespace vkw
{

/**
 * \brief Exception for device-level failures
 *
 * Represents a failure that occurs inside a Device.
 */
class DeviceException : public std::exception
{
protected:
    VkResult errorResult; //!< \internal VkResult from failing Vulkan function
    std::string details; //!< \internal Human readable string for error

public:
    DeviceException(VkResult errorResult_in, std::string details_in) noexcept
        : errorResult(errorResult_in)
        , details(std::move(details_in))
    {}

    DeviceException(const DeviceException& other) = delete;
    DeviceException(DeviceException&& other) noexcept = default;

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

class Instance;

/**
 * \brief Wrapper around VkDevice
 *
 * Wraps VkDevice and all device-level functions; holds all device-level function pointers.
 */
class Device
{
protected:
    VkDevice handle; //!< \internal Wrapped Vulkan handle
    VkPhysicalDevice physicalDevice; //!< \internal Physical device this logical device was created from
    Instance *instance; //!< \internal Vulkan instance this logical device belongs to

public:
    struct FunctionPtrs
    {
        #include "DeviceFunctionPtrs.inl"
    };

    FunctionPtrs functionPtrs;

    Device() noexcept
        : handle(nullptr)
        , physicalDevice(nullptr)
        , instance(nullptr)
    {
    }

    /**
     * Copies VkDevice and VkPhysicalDevice handles and populates function pointer table.
     *
     * \param handle VkDevice handle to be wrapped; takes ownership
     * \param physicalDevice VkPhysicalDevice handle that the logical device was created from
     * \param instance Pointer to parent Instance; functionPtrs is populated using this.
     */
    Device(VkDevice handle, VkPhysicalDevice physicalDevice, Instance *instance);
    Device(const Device& other) = delete;
    Device(Device&& other) noexcept
        : handle(nullptr)
        , physicalDevice(nullptr)
        , instance(nullptr)
    {
        std::swap(handle, other.handle);
        std::swap(physicalDevice, other.physicalDevice);
        std::swap(instance, other.instance);
        std::swap(functionPtrs, other.functionPtrs);
    }

    /**
     * \brief Destroys wrapped VkDevice.
     */
    ~Device();

    Device& operator = (const Device& other) = delete;
    Device& operator = (Device&& other) noexcept
    {
        std::swap(handle, other.handle);
        std::swap(physicalDevice, other.physicalDevice);
        std::swap(instance, other.instance);
        std::swap(functionPtrs, other.functionPtrs);
        return *this;
    }

    /**
     * \brief Get wrapped handle; doesn't give up ownership.
     */
    const VkDevice& getDevice() const noexcept
    {
        return handle;
    }

    /**
     * \brief Get wrapped handle and take ownership of it.
     */
    VkDevice releaseDevice() noexcept
    {
        VkDevice tempHandle = handle;
        handle = nullptr;
        return tempHandle;
    }

    /**
     * \brief Get handle to physical device that this logical device was created from.
     */
    const VkPhysicalDevice& getPhysicalDevice() const noexcept
    {
        return physicalDevice;
    }

    /**
     * \brief Get parent Instance.
     */
    Instance * getInstance() noexcept
    {
        return instance;
    }

    const Instance * getInstance() const noexcept
    {
        return instance;
    }
};

} // namespace vkw

#endif // VULKANWRAPPER_DEVICE_HPP
