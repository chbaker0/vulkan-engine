#include "Device.hpp"
#include "Instance.hpp"

#include <cassert>

namespace vkw
{

Device::Device(VkDevice handleIn, VkPhysicalDevice physicalDeviceIn, Instance *instanceIn)
	: handle(handleIn)
	, physicalDevice(physicalDeviceIn)
	, instance(instanceIn)
{
#define LOAD_FUNCTION(X) functionPtrs.X = (PFN_##X) instance->functionPtrs.vkGetDeviceProcAddr(handle, #X); assert(functionPtrs.X != nullptr)

	LOAD_FUNCTION(vkDestroyDevice);
	LOAD_FUNCTION(vkDeviceWaitIdle);
	LOAD_FUNCTION(vkGetDeviceQueue);
	LOAD_FUNCTION(vkCreateCommandPool);
	LOAD_FUNCTION(vkResetCommandPool);
	LOAD_FUNCTION(vkDestroyCommandPool);
	LOAD_FUNCTION(vkAllocateCommandBuffers);
	LOAD_FUNCTION(vkResetCommandBuffer);
	LOAD_FUNCTION(vkFreeCommandBuffers);
	LOAD_FUNCTION(vkBeginCommandBuffer);
	LOAD_FUNCTION(vkEndCommandBuffer);
	LOAD_FUNCTION(vkQueueSubmit);
	LOAD_FUNCTION(vkCmdExecuteCommands);
	LOAD_FUNCTION(vkCreateFence);
	LOAD_FUNCTION(vkDestroyFence);
	LOAD_FUNCTION(vkGetFenceStatus);
	LOAD_FUNCTION(vkResetFences);
	LOAD_FUNCTION(vkWaitForFences);
	LOAD_FUNCTION(vkCreateSemaphore);
	LOAD_FUNCTION(vkDestroySemaphore);
	LOAD_FUNCTION(vkCreateEvent);
	LOAD_FUNCTION(vkDestroyEvent);
	LOAD_FUNCTION(vkGetEventStatus);
	LOAD_FUNCTION(vkSetEvent);
	LOAD_FUNCTION(vkResetEvent);
	LOAD_FUNCTION(vkCmdSetEvent);
	LOAD_FUNCTION(vkCmdResetEvent);
	LOAD_FUNCTION(vkCmdWaitEvents);
	LOAD_FUNCTION(vkCmdPipelineBarrier);
	LOAD_FUNCTION(vkCreateRenderPass);
	LOAD_FUNCTION(vkDestroyRenderPass);
	LOAD_FUNCTION(vkCreateFramebuffer);
	LOAD_FUNCTION(vkDestroyFramebuffer);
	LOAD_FUNCTION(vkCmdBeginRenderPass);
	LOAD_FUNCTION(vkGetRenderAreaGranularity);
	LOAD_FUNCTION(vkCmdNextSubpass);
	LOAD_FUNCTION(vkCmdEndRenderPass);
	LOAD_FUNCTION(vkCreateShaderModule);
	LOAD_FUNCTION(vkDestroyShaderModule);
	LOAD_FUNCTION(vkCreateComputePipelines);
	LOAD_FUNCTION(vkCreateGraphicsPipelines);
	LOAD_FUNCTION(vkDestroyPipeline);
	LOAD_FUNCTION(vkCreatePipelineCache);
	LOAD_FUNCTION(vkMergePipelineCaches);
	LOAD_FUNCTION(vkGetPipelineCacheData);
	LOAD_FUNCTION(vkDestroyPipelineCache);
	LOAD_FUNCTION(vkCmdBindPipeline);
	LOAD_FUNCTION(vkGetPhysicalDeviceMemoryProperties);
	LOAD_FUNCTION(vkAllocateMemory);
	LOAD_FUNCTION(vkFreeMemory);
	LOAD_FUNCTION(vkMapMemory);
	LOAD_FUNCTION(vkFlushMappedMemoryRanges);
	LOAD_FUNCTION(vkInvalidateMappedMemoryRanges);
	LOAD_FUNCTION(vkUnmapMemory);
	LOAD_FUNCTION(vkGetDeviceMemoryCommitment);
	LOAD_FUNCTION(vkCreateBuffer);
	LOAD_FUNCTION(vkDestroyBuffer);
	LOAD_FUNCTION(vkCreateBufferView);
	LOAD_FUNCTION(vkDestroyBufferView);
	LOAD_FUNCTION(vkCreateImage);
	LOAD_FUNCTION(vkGetImageSubresourceLayout);
	LOAD_FUNCTION(vkDestroyImage);
	LOAD_FUNCTION(vkCreateImageView);
	LOAD_FUNCTION(vkDestroyImageView);
	LOAD_FUNCTION(vkGetBufferMemoryRequirements);
	LOAD_FUNCTION(vkGetImageMemoryRequirements);
	LOAD_FUNCTION(vkBindBufferMemory);
	LOAD_FUNCTION(vkBindImageMemory);
	LOAD_FUNCTION(vkCreateSampler);
	LOAD_FUNCTION(vkDestroySampler);
	LOAD_FUNCTION(vkCreateDescriptorSetLayout);
	LOAD_FUNCTION(vkDestroyDescriptorSetLayout);
	LOAD_FUNCTION(vkCreatePipelineLayout);
	LOAD_FUNCTION(vkDestroyPipelineLayout);
	LOAD_FUNCTION(vkCreateDescriptorPool);
	LOAD_FUNCTION(vkDestroyDescriptorPool);
	LOAD_FUNCTION(vkAllocateDescriptorSets);
	LOAD_FUNCTION(vkFreeDescriptorSets);
	LOAD_FUNCTION(vkResetDescriptorPool);
	LOAD_FUNCTION(vkUpdateDescriptorSets);
	LOAD_FUNCTION(vkCmdBindDescriptorSets);
	LOAD_FUNCTION(vkCmdPushConstants);
	LOAD_FUNCTION(vkCmdClearColorImage);
	LOAD_FUNCTION(vkCmdClearDepthStencilImage);
	LOAD_FUNCTION(vkCmdClearAttachments);
	LOAD_FUNCTION(vkCmdFillBuffer);
	LOAD_FUNCTION(vkCmdUpdateBuffer);
	LOAD_FUNCTION(vkCreateQueryPool);
	LOAD_FUNCTION(vkDestroyQueryPool);
	LOAD_FUNCTION(vkCmdResetQueryPool);
	LOAD_FUNCTION(vkCmdBeginQuery);
	LOAD_FUNCTION(vkCmdEndQuery);
	LOAD_FUNCTION(vkGetQueryPoolResults);
	LOAD_FUNCTION(vkCmdCopyQueryPoolResults);
	LOAD_FUNCTION(vkCmdWriteTimestamp);
	LOAD_FUNCTION(vkCmdCopyBuffer);
	LOAD_FUNCTION(vkCmdCopyImage);
	LOAD_FUNCTION(vkCmdCopyBufferToImage);
	LOAD_FUNCTION(vkCmdCopyImageToBuffer);
	LOAD_FUNCTION(vkCmdBlitImage);
	LOAD_FUNCTION(vkCmdResolveImage);
	LOAD_FUNCTION(vkCmdBindIndexBuffer);
	LOAD_FUNCTION(vkCmdDraw);
	LOAD_FUNCTION(vkCmdDrawIndexed);
	LOAD_FUNCTION(vkCmdDrawIndirect);
	LOAD_FUNCTION(vkCmdDrawIndexedIndirect);
	LOAD_FUNCTION(vkCmdBindVertexBuffers);
	LOAD_FUNCTION(vkCmdSetViewport);
	LOAD_FUNCTION(vkCmdSetLineWidth);
	LOAD_FUNCTION(vkCmdSetDepthBias);
	LOAD_FUNCTION(vkCmdSetBlendConstants);
	LOAD_FUNCTION(vkCmdSetScissor);
	LOAD_FUNCTION(vkCmdSetDepthBounds);
	LOAD_FUNCTION(vkCmdSetStencilCompareMask);
	LOAD_FUNCTION(vkCmdSetStencilWriteMask);
	LOAD_FUNCTION(vkCmdSetStencilReference);
	LOAD_FUNCTION(vkGetPhysicalDeviceSparseImageFormatProperties);
	LOAD_FUNCTION(vkGetImageSparseMemoryRequirements);
	LOAD_FUNCTION(vkQueueBindSparse);
	LOAD_FUNCTION(vkCmdDispatch);
	LOAD_FUNCTION(vkCmdDispatchIndirect);

	
#undef LOAD_FUNCTION
}

Device::~Device()
{
	functionPtrs.vkDestroyDevice(handle, nullptr);
}

} // namespace vkw
