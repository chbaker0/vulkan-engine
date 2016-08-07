#include <iostream>
#include <cstdint>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkanwrapper/Instance.hpp"
#include <gtest/gtest.h>

namespace
{

class InstanceTest : public ::testing::Test
{
protected:

	static void errorCallback (int error, const char *description)
	{
		std::cerr << "GLFW error: " << error << "; " << description << std::endl;
	}

	static void * getInstanceProcAddrWrapper (VkInstance instance, const char *pname)
	{
		return (void *) glfwGetInstanceProcAddress(instance, pname);
	}

	virtual void SetUp ()
	{
		ASSERT_EQ(glfwInit(), GLFW_TRUE) << "Could not initialize GLFW";
		ASSERT_EQ(glfwVulkanSupported(), GLFW_TRUE) << "Vulkan is not supported";
	}

	virtual void TearDown ()
	{
		glfwTerminate();
	}
};

} // anonymous

TEST_F(InstanceTest, InstanceCreation)
{
	PFN_vkCreateInstance vkCreateInstance = (PFN_vkCreateInstance) glfwGetInstanceProcAddress(nullptr, "vkCreateInstance");
	ASSERT_NE(vkCreateInstance, nullptr) << "Could not get pointer for vkCreateInstance";

	std::uint32_t glfwExtensionCount;
	const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	ASSERT_NE(glfwExtensions, nullptr) << "Could not get GLFW required extensions";

	std::vector<const char *> extensions;

	for (unsigned int i = 0; i < glfwExtensionCount; ++i)
	{
		extensions.push_back(glfwExtensions[i]);
	}

	VkInstanceCreateInfo instanceCreateInfo =
		{
			VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,	// sType
			nullptr,								// pNext
			0,										// flags
			nullptr,								// pApplicationInfo
		    0,										// enabledLayerCount
		    nullptr,								// ppEnabledLayerNames
		    (uint32_t) extensions.size(),			// enabledExtensionCount
			extensions.data(),						// ppEnabledExtensionNames
		};

	VkInstance instanceHandle;
	ASSERT_EQ(vkCreateInstance(&instanceCreateInfo, nullptr, &instanceHandle), VK_SUCCESS) << "Could not create Vulkan instance";

	vkw::Instance instance;

	ASSERT_NO_THROW(instance = vkw::Instance(instanceHandle, getInstanceProcAddrWrapper));
}
