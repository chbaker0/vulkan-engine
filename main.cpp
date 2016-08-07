#include <iostream>
#include <cassert>
#include <cstdint>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkanwrapper/Instance.hpp"
#include "vulkanwrapper/Device.hpp"

using namespace std;

void errorCallback(int error, const char *description)
{
	cerr << error << ": " << description << endl;
}

VKAPI_ATTR VkBool32 VKAPI_CALL vulkanCallback(VkDebugReportFlagsEXT,
											  VkDebugReportObjectTypeEXT,
											  uint64_t,
											  size_t,
											  int32_t,
											  const char *,
											  const char *pMessage,
											  void *)
{
	cerr << pMessage << endl;
	return VK_FALSE;
}

void * getInstanceProcAddrWrapper(VkInstance instance, const char *pname)
{
	return (void *) glfwGetInstanceProcAddress(instance, pname);
}

namespace
{

const char *extensions[] =
{
	"VK_EXT_debug_report"
};

const char *layers[] =
{
	"VK_LAYER_LUNARG_standard_validation"
};

} // anonymous

vkw::Instance createInstance ()
{
	PFN_vkCreateInstance vkCreateInstance = (PFN_vkCreateInstance) glfwGetInstanceProcAddress(nullptr, "vkCreateInstance");

	std::uint32_t extensionCount;
	const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

	std::vector<const char*> extensionsVec(extensionCount);

	for (unsigned int i = 0; i < extensionCount; ++i)
	{
		extensionsVec[i] = glfwExtensions[i];
	}

	for (unsigned int i = 0; i < sizeof(extensions) / sizeof(const char*); ++i)
	{
		extensionsVec.push_back(extensions[i]);
	}

	VkInstanceCreateInfo instanceCreateInfo =
		{
			VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, // sType
			nullptr,								// pNext
			0,										// flags
			nullptr,								// pApplicationInfo
		    sizeof(layers) / sizeof (const char *),	// enabledLayerCount
		    layers,									// ppEnabledLayerNames
		    (uint32_t) extensionsVec.size(),		// enabledExtensionCount
			extensionsVec.data(),					// ppEnabledExtensionNames
		};

	VkInstance instanceHandle;
	if(vkCreateInstance(&instanceCreateInfo, nullptr, &instanceHandle) != VK_SUCCESS)
	{
		cerr << "Could not create Vulkan instance.\n";
	    throw std::runtime_error("Could not create vulkan instance.");
	}

	vkw::Instance instance(instanceHandle, getInstanceProcAddrWrapper);

	return instance;
}

vkw::Device createDevice (vkw::Instance& instance)
{
	
}

bool run ()
{
	glfwSetErrorCallback(errorCallback);
	
	if(glfwInit() == GLFW_FALSE)
	{
		cerr << "Could not initialize GLFW.\n";
		return false;
	}
	
	if(glfwVulkanSupported() == GLFW_FALSE)
	{
		cerr << "Vulkan not supported.\n";
		return false;
	}

	vkw::Instance instance = createInstance();

	PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT) glfwGetInstanceProcAddress(instance.getInstance(), "vkCreateDebugReportCallbackEXT");
	PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT) glfwGetInstanceProcAddress(instance.getInstance(), "vkDestroyDebugReportCallbackEXT");

	assert(vkCreateDebugReportCallbackEXT != nullptr);
	assert(vkDestroyDebugReportCallbackEXT != nullptr);

	VkDebugReportCallbackCreateInfoEXT callbackCreateInfo;
	callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	callbackCreateInfo.pNext = nullptr;
	callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
	callbackCreateInfo.pfnCallback = &vulkanCallback;
	callbackCreateInfo.pUserData = nullptr;

	VkDebugReportCallbackEXT callback;
	vkCreateDebugReportCallbackEXT(instance.getInstance(), &callbackCreateInfo, nullptr, &callback);
	
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
			0, // ppEnabledExtensionNames
		    nullptr, // enabledExtensionsCount
			&features // pEnabledFeatures
		};

	vkw::Device device = instance.createDevice(physicalDevices[0], deviceCreateInfo);

	vkDestroyDebugReportCallbackEXT(instance.getInstance(), callback, nullptr);

	return true;
}

int main ()
{
	try
	{
		return run() ? 0 : 1;
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;

		return 1;
	}
	catch (...)
	{
		cerr << "Unknown exception" << endl;

		return 1;
	}

	return 0;
}
