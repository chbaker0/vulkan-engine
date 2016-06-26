std::vector<VkPhysicalDevice> enumeratePhysicalDevices()
{
	std::uint32_t physicalDeviceCount;
	VkResult result = functionPtrs.vkEnumeratePhysicalDevices(handle, &physicalDeviceCount, nullptr);

	if(result < 0)
	{
		throw InstanceException(result, "Failed to get physical device count");
	}

	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);

	result = functionPtrs.vkEnumeratePhysicalDevices(handle, &physicalDeviceCount, &physicalDevices[0]);

	if(result < 0)
	{
		throw InstanceException(result, "Failed to enumerate physical devices");
	}

	return std::move(physicalDevices);
}

VkPhysicalDeviceProperties getPhysicalDeviceProperties(VkPhysicalDevice physicalDevice) noexcept
{
	VkPhysicalDeviceProperties properties;
	functionPtrs.vkGetPhysicalDeviceProperties(physicalDevice, &properties);
	return properties;
}

std::vector<VkQueueFamilyProperties> getPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice)
{
	std::uint32_t queueFamilyCount;
	functionPtrs.vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);

	functionPtrs.vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, &queueFamilyProperties[0]);

	return std::move(queueFamilyProperties);
}
