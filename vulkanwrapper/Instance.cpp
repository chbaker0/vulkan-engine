#include "Instance.hpp"

#include <cassert>

namespace vkw
{

Instance::Instance(VkInstance handle_in, GetProcAddrPtr getProcAddr)
{
	handle = handle_in;
	
#define LOAD_FUNCTION(X) functionPtrs.X = (PFN_##X) getProcAddr(handle, #X); assert(functionPtrs.X != nullptr)

	LOAD_FUNCTION(vkGetInstanceProcAddr);
	LOAD_FUNCTION(vkGetDeviceProcAddr);
	LOAD_FUNCTION(vkEnumeratePhysicalDevices);
	LOAD_FUNCTION(vkGetPhysicalDeviceProperties);
	LOAD_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties);
	LOAD_FUNCTION(vkDestroyInstance);
	
#undef LOAD_FUNCTION
}

Instance::~Instance()
{
	functionPtrs.vkDestroyInstance(handle, nullptr);
}

} // namespace vkw
