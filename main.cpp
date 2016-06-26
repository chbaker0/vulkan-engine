#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkanwrapper/Instance.hpp"

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

	VkInstanceCreateInfo instanceCreateInfo =
		{
			VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, // sType
			nullptr,								// pNext
			0,										// flags
			nullptr,								// pApplicationInfo
			0,										// enabledLayerCount
			nullptr,								// ppEnabledLayerNames
			0,										// enabledExtensionCount
			nullptr,								// ppEnabledExtensionNames
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
}
