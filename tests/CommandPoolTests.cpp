#include <gtest/gtest.h>

#include "vulkanwrapper/Instance.hpp"
#include "vulkanwrapper/Device.hpp"
#include "vulkanwrapper/CommandPool.hpp"

#include "InstanceMock.hpp"
#include "DeviceMock.hpp"

namespace
{

class CommandPoolTest : public ::testing::Test
{
protected:
    virtual void SetUp ()
    {

    }

    void createObjects ()
    {
        instanceProcMock.setProcAddr("vkGetDeviceProcAddr", (PFN_vkVoidFunction) getDeviceProcAddr);

        instanceHandle = (VkInstance) &instanceProcMock;
        instance = vkw::Instance(instanceHandle, getInstanceProcAddr);

        deviceHandle = (VkDevice) &deviceProcMock;
        device = vkw::Device(deviceHandle, nullptr, &instance);
    }

    static void * getInstanceProcAddr (VkInstance instance, const char *name)
    {
        InstanceProcMock *mock = (InstanceProcMock *) instance;
        return (void *) mock->getProcAddr(name);
    }

    static PFN_vkVoidFunction getDeviceProcAddr (VkDevice device, const char *name)
    {
        DeviceProcMock *mock = (DeviceProcMock *) device;
        return mock->getProcAddr(name);
    }

    vkw::Instance instance;
    VkInstance instanceHandle;
    vkw::Device device;
    VkDevice deviceHandle;

    InstanceProcMock instanceProcMock;
    DeviceProcMock deviceProcMock;
};

TEST_F (CommandPoolTest, CommandPoolCreation)
{
    PFN_vkCreateCommandPool createCommandPool =
        [](VkDevice, const VkCommandPoolCreateInfo*, const VkAllocationCallbacks*, VkCommandPool *pool) -> VkResult
        {
            *pool = (VkCommandPool) 1;
            return VK_SUCCESS;
        };

    PFN_vkDestroyCommandPool destroyCommandPool =
        [](VkDevice, VkCommandPool pool, const VkAllocationCallbacks*) -> void
        {
            ASSERT_EQ(pool, (VkCommandPool) 1) << "destroyCommandPool not called with same pool handle";
        };

    deviceProcMock.setProcAddr("vkCreateCommandPool", (PFN_vkVoidFunction) createCommandPool);
    deviceProcMock.setProcAddr("vkDestroyCommandPool", (PFN_vkVoidFunction) destroyCommandPool);

    ASSERT_NO_THROW(createObjects());

    {
        VkCommandPoolCreateInfo createInfo = {};

        vkw::CommandPool commandPool;
        ASSERT_NO_THROW(commandPool = device.createCommandPool(createInfo));
    }
}

TEST_F (CommandPoolTest, CommandPoolCreationFail)
{
    PFN_vkCreateCommandPool createCommandPool =
        [](VkDevice, const VkCommandPoolCreateInfo*, const VkAllocationCallbacks*, VkCommandPool*) -> VkResult
        {
            return VK_ERROR_DEVICE_LOST;
        };

    deviceProcMock.setProcAddr("vkCreateCommandPool", (PFN_vkVoidFunction) createCommandPool);

    ASSERT_NO_THROW(createObjects());

    VkCommandPoolCreateInfo createInfo = {};
    ASSERT_THROW(device.createCommandPool(createInfo), vkw::DeviceException);
}

} // anonymous
