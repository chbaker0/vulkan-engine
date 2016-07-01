#include <iostream>
#include <cassert>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkanwrapper/Instance.hpp"
#include "vulkanwrapper/Device.hpp"

using namespace std;

void errorCallback(int error, const char *description)
{
	cerr << error << ": " << description << endl;
}

void * getInstanceProcAddrWrapper(VkInstance instance, const char *pname)
{
	return (void *) glfwGetInstanceProcAddress(instance, pname);
}

int main()
{
	glfwSetErrorCallback(errorCallback);
	
	if(glfwInit() == GLFW_FALSE)
	{
		cerr << "Could not initialize GLFW.\n";
		return 1;
	}
	
	if(glfwVulkanSupported() == GLFW_FALSE)
	{
		cerr << "Vulkan not supported.\n";
		return 1;
	}

	PFN_vkCreateInstance vkCreateInstance = (PFN_vkCreateInstance) glfwGetInstanceProcAddress(nullptr, "vkCreateInstance");

	std::uint32_t extensionCount;
	const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

	++extensionCount;
	std::vector<const char*> extensions(extensionCount);

	for(unsigned int i = 0; i < extensionCount; ++i)
	{
		extensions[i] = glfwExtensions[i];
	}

	extensions[extensionCount - 1] = "VK_EXT_debug_report";

	VkInstanceCreateInfo instanceCreateInfo =
		{
			VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, // sType
			nullptr,								// pNext
			0,										// flags
			nullptr,								// pApplicationInfo
			0,										// enabledLayerCount
			nullptr,								// ppEnabledLayerNames
			extensionCount,							// enabledExtensionCount
			extensions,								// ppEnabledExtensionNames
		};

	VkInstance instanceHandle;
	if(vkCreateInstance(&instanceCreateInfo, nullptr, &instanceHandle) != VK_SUCCESS)
	{
		cerr << "Could not create Vulkan instance.\n";
		return 1;
	}

	vkw::Instance instance(instanceHandle, getInstanceProcAddrWrapper);

	auto physicalDevices = instance.enumeratePhysicalDevices();
	cout << physicalDevices.size() << endl;

	auto deviceQueues = instance.getPhysicalDeviceQueueFamilyProperties(physicalDevices[0]);

	unsigned int universalQueueIndex = 0;

	for(unsigned int i = 0; i < deviceQueues.size(); ++i)
	{
		if(deviceQueues[i].queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_TRANSFER_BIT | VK_QUEUE_COMPUTE_BIT))
		{
			universalQueueIndex = i;
		}
	}

	float queuePriority = 1.0;

	VkDeviceQueueCreateInfo queueCreateInfo =
		{
			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, // sType
			nullptr, // pNext
			0, // flags
			universalQueueIndex, // queueFamilyIndex
			1, // queueCount
			&queuePriority // pQueuePriorities
		};

	VkPhysicalDeviceFeatures features = instance.getPhysicalDeviceFeatures(physicalDevices[0]);
	
	VkDeviceCreateInfo deviceCreateInfo =
		{
			VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, // sType
			nullptr, // pNext
			0, // flags
			1, // queueCreateInfoCount
			&queueCreateInfo, // pQueueCreateInfos
			0, // enabledLayerCount
			nullptr, // ppEnabledLayerNames
			0, // enabledExtensionsCount
			nullptr, // ppEnabledExtensionNames
			&features // pEnabledFeatures
		};

	vkw::Device device = instance.createDevice(physicalDevices[0], deviceCreateInfo);
}
