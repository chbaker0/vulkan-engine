#include <iostream>
#include <cstdint>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkanwrapper/Instance.hpp"
#include "vulkanwrapper/Device.hpp"
#include <gtest/gtest.h>

namespace
{

class DeviceTest : public ::testing::Test
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

    void createInstance ()
    {
        PFN_vkCreateInstance vkCreateInstance = (PFN_vkCreateInstance) glfwGetInstanceProcAddress(nullptr, "vkCreateInstance");
        ASSERT_NE(vkCreateInstance, nullptr) << "Could not get pointer for vkCreateInstance";

        std::uint32_t glfwExtensionCount;
        const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        ASSERT_NE(glfwExtensions, nullptr) << "Could not get GLFW required extensions";

        const char *extensions[] =
        {
            "VK_EXT_debug_report"
        };

        const char *layers[] =
        {
            "VK_LAYER_LUNARG_standard_validation"
        };

        std::vector<const char *> allExtensions;

        for (unsigned int i = 0; i < glfwExtensionCount; ++i)
        {
            allExtensions.push_back(glfwExtensions[i]);
        }

        for (unsigned int i = 0; i < sizeof(extensions) / sizeof(const char *); ++i)
        {
            allExtensions.push_back(extensions[i]);
        }

        VkInstanceCreateInfo instanceCreateInfo =
            {
                VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, // sType
                nullptr,                                // pNext
                0,                                      // flags
                nullptr,                                // pApplicationInfo
                sizeof(layers) / sizeof(const char *),  // enabledLayerCount
                layers,                                 // ppEnabledLayerNames
                (std::uint32_t) allExtensions.size(),   // enabledExtensionCount
                allExtensions.data(),                   // ppEnabledExtensionNames
            };

        VkInstance instanceHandle;
        ASSERT_EQ(vkCreateInstance(&instanceCreateInfo, nullptr, &instanceHandle), VK_SUCCESS) << "Could not create Vulkan instance";

        instance = vkw::Instance(instanceHandle, getInstanceProcAddrWrapper);
    }

    virtual void SetUp ()
    {
        ASSERT_EQ(glfwInit(), GLFW_TRUE) << "Could not initialize GLFW";
        ASSERT_EQ(glfwVulkanSupported(), GLFW_TRUE) << "Vulkan is not supported";

        ASSERT_NO_THROW(ASSERT_NO_FATAL_FAILURE(createInstance()));

        auto vkCreateDebugReportCallbackEXT
            = (PFN_vkCreateDebugReportCallbackEXT) glfwGetInstanceProcAddress(instance.getInstance(), "vkCreateDebugReportCallbackEXT");
        ASSERT_NE(vkCreateDebugReportCallbackEXT, nullptr) << "Could not get pointer for vkCreateDebugReportCallbackEXT";

        vkDestroyDebugReportCallbackEXT
            = (PFN_vkDestroyDebugReportCallbackEXT) glfwGetInstanceProcAddress(instance.getInstance(), "vkDestroyDebugReportCallbackEXT");
        ASSERT_NE(vkDestroyDebugReportCallbackEXT, nullptr) << "Could not get pointer for vkDestroyDebugReportCallbackEXT";

        VkDebugReportCallbackCreateInfoEXT callbackCreateInfo;
        callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        callbackCreateInfo.pNext = nullptr;
        callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
        callbackCreateInfo.pfnCallback = &vulkanCallback;
        callbackCreateInfo.pUserData = nullptr;

        ASSERT_EQ(vkCreateDebugReportCallbackEXT(instance.getInstance(), &callbackCreateInfo, nullptr, &debugReportCallback), VK_SUCCESS) << "Could not create debug report callback object";
    }

    virtual void TearDown ()
    {
        vkDestroyDebugReportCallbackEXT(instance.getInstance(), debugReportCallback, nullptr);

        // Destroy instance
        instance = vkw::Instance();

        glfwTerminate();
    }

    vkw::Instance instance;
    VkDebugReportCallbackEXT debugReportCallback;
    PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
};

TEST_F(DeviceTest, DeviceCreation)
{
    std::vector<VkPhysicalDevice> physicalDevices;
    ASSERT_NO_THROW(physicalDevices = instance.enumeratePhysicalDevices());

    for (const VkPhysicalDevice physDev : physicalDevices)
    {
        const VkPhysicalDeviceFeatures features = instance.getPhysicalDeviceFeatures(physDev);

        const std::vector<VkQueueFamilyProperties> queueFamilyProperties = instance.getPhysicalDeviceQueueFamilyProperties(physDev);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos(queueFamilyProperties.size());

        for (unsigned int queueFamilyNdx = 0; queueFamilyNdx < queueFamilyProperties.size(); ++queueFamilyNdx)
        {
            const float queuePriority = 1.0f;

            queueCreateInfos[queueFamilyNdx] =
                VkDeviceQueueCreateInfo
                {
                    VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, // sType
                    nullptr,                                    // pNext
                    0,                                          // flags
                    queueFamilyNdx,                             // queueFamilyIndex
                    1,                                          // queueCount
                    &queuePriority                              // pQueuePriorities
                };
        }

        VkDeviceCreateInfo devCreateInfo =
        {
			VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,    // sType
			nullptr,                                 // pNext
			0,                                       // flags
			(std::uint32_t) queueCreateInfos.size(), // queueCreateInfoCount
			queueCreateInfos.data(),                 // pQueueCreateInfos
		    0,                                       // enabledLayerCount
		    nullptr,                                 // ppEnabledLayerNames
			0,                                       // ppEnabledExtensionNames
		    nullptr,                                 // enabledExtensionsCount
			&features                                // pEnabledFeatures
        };

        vkw::Device device;
        ASSERT_NO_THROW(device = instance.createDevice(physDev, devCreateInfo));
    }
}

} // anonymous
