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

class InstanceException : public std::exception
{
protected:
	VkResult errorResult;
	std::string details;

public:
	InstanceException(VkResult errorResult_in, std::string details_in) noexcept
		: errorResult(errorResult_in)
		, details(std::move(details_in))
	{}

	InstanceException(const InstanceException& other) = default;
	InstanceException(InstanceException&& other) noexcept = default;

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

class Instance
{
protected:
	VkInstance handle;

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

	Instance(VkInstance handle_in, GetProcAddrPtr getProcAddr);
	Instance(const Instance& other) = delete;
	Instance(Instance&& other) noexcept
		: handle(VK_NULL_HANDLE)
	{
		std::swap(handle, other.handle);
		std::swap(functionPtrs, other.functionPtrs);
	}

	~Instance();

	Instance& operator = (const Instance& other) = delete;
	Instance& operator = (Instance&& other) noexcept
	{
		std::swap(handle, other.handle);
		std::swap(functionPtrs, other.functionPtrs);
		return *this;
	}

	VkInstance getInstance() noexcept
	{
		return handle;
	}
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
	Device createDevice(VkPhysicalDevice phyDev, const VkDeviceCreateInfo& createInfo);
};

} // namespace vkw

#endif // VULKANWRAPPER_INSTANCE_HPP
