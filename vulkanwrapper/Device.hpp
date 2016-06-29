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

class DeviceException : std::exception
{
protected:
	VkResult errorResult;
	std::string details;

public:
	DeviceException(VkResult errorResult_in, std::string details_in) noexcept
		: errorResult(errorResult_in)
		, details(std::move(details_in))
	{}

	DeviceException(const DeviceException& other) = delete;
	DeviceException(DeviceException&& other) noexcept = default;

	VkResult getVkResult() const noexcept
	{
		return errorResult;
	}

	virtual const char * what() const noexcept
	{
		return details.c_str();
	}
};

class Device
{
protected:
	VkDevice handle;
	VkPhysicalDevice physicalDevice;
	Instance *instance;

public:
	struct FunctionPtrs
	{
		
	};

	FunctionPtrs functionPtrs;

	Device() = delete;
	Device(VkDevice handle, VkPhysicalDevice physicalDevice, Instance *instance);
	Device(const Device& other) = delete;
	Device(Device&& other) noexcept
		: handle(other.handle)
		, physicalDevice(other.physicalDevice)
		, instance(other.instance)
	{}

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

	VkDevice getDevice() noexcept
	{
		return handle;
	}
	VkDevice releaseDevice() noexcept
	{
		VkDevice tempHandle = handle;
		handle = nullptr;
		return tempHandle;
	}

	VkPhysicalDevice getPhysicalDevice() noexcept
	{
		return physicalDevice;
	}

	Instance * getInstance() noexcept
	{
		return instance;
	}
}

} // namespace vkw

#endif // VULKANWRAPPER_DEVICE_HPP
