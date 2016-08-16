/**
 * \brief Generic wrapper around Vulkan objects owned by VkDevice
 */

#ifndef VULKANWRAPPER_DEVICEOBJECT_HPP
#define VULKANWRAPPER_DEVICEOBJECT_HPP

#include <utility>

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

namespace vkw
{
namespace detail
{

template <typename HandleType>
class DeviceObject
{
public:
    typedef void (VKAPI_PTR *Destroyer)(VkDevice, HandleType, const VkAllocationCallbacks *);

    DeviceObject(VkDevice deviceHandle_in, HandleType handle_in, Destroyer destroyer_in) noexcept
        : deviceHandle(deviceHandle_in)
        , handle(handle_in)
        , destroyer(destroyer_in)
    {
    }

    ~DeviceObject()
    {
        if (deviceHandle != nullptr && handle != nullptr && destroyer != nullptr)
        {
            destroyer(deviceHandle, handle, nullptr);
        }
    }

    DeviceObject(const DeviceObject& other) = delete;
    DeviceObject(DeviceObject&& other) noexcept
        : DeviceObject(nullptr, nullptr, nullptr)
    {
        std::swap(deviceHandle, other.deviceHandle);
        std::swap(handle, other.handle);
        std::swap(destroyer, other.destroyer);
    }

    DeviceObject& operator = (const DeviceObject& other) = delete;
    DeviceObject& operator = (DeviceObject&& other)
    {
        std::swap(deviceHandle, other.deviceHandle);
        std::swap(handle, other.handle);
        std::swap(destroyer, other.destroyer);
        return *this;
    }

    HandleType operator * () const noexcept
    {
        return handle;
    }

    const HandleType& getHandle() const noexcept
    {
        return handle;
    }

    HandleType releaseHandle() noexcept
    {
        HandleType temp = handle;

        deviceHandle = nullptr;
        handle = nullptr;
        destroyer = nullptr;

        return temp;
    }

private:
    VkDevice deviceHandle;
    HandleType handle;
    Destroyer destroyer;
};

} // namespace detail
} // namespace vkw

#endif // VULKANWRAPPER_DEVICEOBJECT_HPP
