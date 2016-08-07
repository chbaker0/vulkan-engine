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

	static VKAPI_ATTR VkBool32 VKAPI_CALL vulkanCallback(VkDebugReportFlagsEXT,
														 VkDebugReportObjectTypeEXT,
														 uint64_t,
														 size_t,
														 int32_t,
														 const char *,
														 const char *pMessage,
														 void *)
	{
		std::cerr << pMessage << std::endl;
		return VK_FALSE;
	}

	static void * getInstanceProcAddrWrapper (VkInstance instance, const char *pname)
	{
		return (void *) glfwGetInstanceProcAddress(instance, pname);
	}

    void createInstance (const char **extensions, unsigned int extensionCount,
						 const char **layers, unsigned int layerCount,
						 vkw::Instance& instance) const
	{
		PFN_vkCreateInstance vkCreateInstance = (PFN_vkCreateInstance) glfwGetInstanceProcAddress(nullptr, "vkCreateInstance");
		ASSERT_NE(vkCreateInstance, nullptr) << "Could not get pointer for vkCreateInstance";

		std::uint32_t glfwExtensionCount;
		const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		ASSERT_NE(glfwExtensions, nullptr) << "Could not get GLFW required extensions";

		std::vector<const char *> allExtensions;

		for (unsigned int i = 0; i < glfwExtensionCount; ++i)
		{
			allExtensions.push_back(glfwExtensions[i]);
		}

		for (unsigned int i = 0; i < extensionCount; ++i)
		{
			allExtensions.push_back(extensions[i]);
		}

		VkInstanceCreateInfo instanceCreateInfo =
			{
				VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,	// sType
				nullptr,								// pNext
				0,										// flags
				nullptr,								// pApplicationInfo
				(std::uint32_t) layerCount,				// enabledLayerCount
				layers,									// ppEnabledLayerNames
				(std::uint32_t) allExtensions.size(),	// enabledExtensionCount
				allExtensions.data(),					// ppEnabledExtensionNames
			};

		VkInstance instanceHandle;
		ASSERT_EQ(vkCreateInstance(&instanceCreateInfo, nullptr, &instanceHandle), VK_SUCCESS) << "Could not create Vulkan instance";

	    instance = vkw::Instance(instanceHandle, getInstanceProcAddrWrapper);
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
	vkw::Instance instance;
	ASSERT_NO_THROW(createInstance(nullptr, 0, nullptr, 0, instance));
}

TEST_F(InstanceTest, InstanceCreationLayers)
{
	const char *extensions[] =
		{
			"VK_EXT_debug_report"
		};

	const char *layers[] =
		{
			"VK_LAYER_LUNARG_standard_validation"
		};

	vkw::Instance instance;
	ASSERT_NO_THROW(createInstance(extensions, 1, layers, 1, instance));

    auto vkCreateDebugReportCallbackEXT
		= (PFN_vkCreateDebugReportCallbackEXT) glfwGetInstanceProcAddress(instance.getInstance(), "vkCreateDebugReportCallbackEXT");
	ASSERT_NE(vkCreateDebugReportCallbackEXT, nullptr) << "Could not get pointer for vkCreateDebugReportCallbackEXT";

	auto vkDestroyDebugReportCallbackEXT
		= (PFN_vkDestroyDebugReportCallbackEXT) glfwGetInstanceProcAddress(instance.getInstance(), "vkDestroyDebugReportCallbackEXT");
	ASSERT_NE(vkDestroyDebugReportCallbackEXT, nullptr) << "Could not get pointer for vkDestroyDebugReportCallbackEXT";

	VkDebugReportCallbackCreateInfoEXT callbackCreateInfo;
	callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	callbackCreateInfo.pNext = nullptr;
	callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
	callbackCreateInfo.pfnCallback = &vulkanCallback;
	callbackCreateInfo.pUserData = nullptr;

	VkDebugReportCallbackEXT callback;
	ASSERT_EQ(vkCreateDebugReportCallbackEXT(instance.getInstance(), &callbackCreateInfo, nullptr, &callback), VK_SUCCESS) << "Could not create debug report callback object";

	vkDestroyDebugReportCallbackEXT(instance.getInstance(), callback, nullptr);
}
