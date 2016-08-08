PFN_vkDestroyDevice									vkDestroyDevice;
PFN_vkDeviceWaitIdle								vkDeviceWaitIdle;
PFN_vkGetDeviceQueue								vkGetDeviceQueue;
PFN_vkCreateCommandPool								vkCreateCommandPool;
PFN_vkResetCommandPool								vkResetCommandPool;
PFN_vkDestroyCommandPool							vkDestroyCommandPool;
PFN_vkAllocateCommandBuffers						vkAllocateCommandBuffers;
PFN_vkResetCommandBuffer							vkResetCommandBuffer;
PFN_vkFreeCommandBuffers							vkFreeCommandBuffers;
PFN_vkBeginCommandBuffer							vkBeginCommandBuffer;
PFN_vkEndCommandBuffer								vkEndCommandBuffer;
PFN_vkQueueSubmit									vkQueueSubmit;
PFN_vkCmdExecuteCommands							vkCmdExecuteCommands;
PFN_vkCreateFence									vkCreateFence;
PFN_vkDestroyFence									vkDestroyFence;
PFN_vkGetFenceStatus								vkGetFenceStatus;
PFN_vkResetFences									vkResetFences;
PFN_vkWaitForFences									vkWaitForFences;
PFN_vkCreateSemaphore								vkCreateSemaphore;
PFN_vkDestroySemaphore								vkDestroySemaphore;
PFN_vkCreateEvent									vkCreateEvent;
PFN_vkDestroyEvent									vkDestroyEvent;
PFN_vkGetEventStatus								vkGetEventStatus;
PFN_vkSetEvent										vkSetEvent;
PFN_vkResetEvent									vkResetEvent;
PFN_vkCmdSetEvent									vkCmdSetEvent;
PFN_vkCmdResetEvent									vkCmdResetEvent;
PFN_vkCmdWaitEvents									vkCmdWaitEvents;
PFN_vkCmdPipelineBarrier							vkCmdPipelineBarrier;
PFN_vkCreateRenderPass								vkCreateRenderPass;
PFN_vkDestroyRenderPass								vkDestroyRenderPass;
PFN_vkCreateFramebuffer								vkCreateFramebuffer;
PFN_vkDestroyFramebuffer							vkDestroyFramebuffer;
PFN_vkCmdBeginRenderPass							vkCmdBeginRenderPass;
PFN_vkGetRenderAreaGranularity						vkGetRenderAreaGranularity;
PFN_vkCmdNextSubpass								vkCmdNextSubpass;
PFN_vkCmdEndRenderPass								vkCmdEndRenderPass;
PFN_vkCreateShaderModule							vkCreateShaderModule;
PFN_vkDestroyShaderModule							vkDestroyShaderModule;
PFN_vkCreateComputePipelines						vkCreateComputePipelines;
PFN_vkCreateGraphicsPipelines						vkCreateGraphicsPipelines;
PFN_vkDestroyPipeline								vkDestroyPipeline;
PFN_vkCreatePipelineCache							vkCreatePipelineCache;
PFN_vkMergePipelineCaches							vkMergePipelineCaches;
PFN_vkGetPipelineCacheData							vkGetPipelineCacheData;
PFN_vkDestroyPipelineCache							vkDestroyPipelineCache;
PFN_vkCmdBindPipeline								vkCmdBindPipeline;
PFN_vkGetPhysicalDeviceMemoryProperties				vkGetPhysicalDeviceMemoryProperties;
PFN_vkAllocateMemory								vkAllocateMemory;
PFN_vkFreeMemory									vkFreeMemory;
PFN_vkMapMemory										vkMapMemory;
PFN_vkFlushMappedMemoryRanges						vkFlushMappedMemoryRanges;
PFN_vkInvalidateMappedMemoryRanges					vkInvalidateMappedMemoryRanges;
PFN_vkUnmapMemory									vkUnmapMemory;
PFN_vkGetDeviceMemoryCommitment						vkGetDeviceMemoryCommitment;
PFN_vkCreateBuffer									vkCreateBuffer;
PFN_vkDestroyBuffer									vkDestroyBuffer;
PFN_vkCreateBufferView								vkCreateBufferView;
PFN_vkDestroyBufferView								vkDestroyBufferView;
PFN_vkCreateImage									vkCreateImage;
PFN_vkGetImageSubresourceLayout						vkGetImageSubresourceLayout;
PFN_vkDestroyImage									vkDestroyImage;
PFN_vkCreateImageView								vkCreateImageView;
PFN_vkDestroyImageView								vkDestroyImageView;
PFN_vkGetBufferMemoryRequirements					vkGetBufferMemoryRequirements;
PFN_vkGetImageMemoryRequirements					vkGetImageMemoryRequirements;
PFN_vkBindBufferMemory								vkBindBufferMemory;
PFN_vkBindImageMemory								vkBindImageMemory;
PFN_vkCreateSampler									vkCreateSampler;
PFN_vkDestroySampler								vkDestroySampler;
PFN_vkCreateDescriptorSetLayout						vkCreateDescriptorSetLayout;
PFN_vkDestroyDescriptorSetLayout					vkDestroyDescriptorSetLayout;
PFN_vkCreatePipelineLayout							vkCreatePipelineLayout;
PFN_vkDestroyPipelineLayout							vkDestroyPipelineLayout;
PFN_vkCreateDescriptorPool							vkCreateDescriptorPool;
PFN_vkDestroyDescriptorPool							vkDestroyDescriptorPool;
PFN_vkAllocateDescriptorSets						vkAllocateDescriptorSets;
PFN_vkFreeDescriptorSets							vkFreeDescriptorSets;
PFN_vkResetDescriptorPool							vkResetDescriptorPool;
PFN_vkUpdateDescriptorSets							vkUpdateDescriptorSets;
PFN_vkCmdBindDescriptorSets							vkCmdBindDescriptorSets;
PFN_vkCmdPushConstants								vkCmdPushConstants;
PFN_vkCmdClearColorImage							vkCmdClearColorImage;
PFN_vkCmdClearDepthStencilImage						vkCmdClearDepthStencilImage;
PFN_vkCmdClearAttachments							vkCmdClearAttachments;
PFN_vkCmdFillBuffer									vkCmdFillBuffer;
PFN_vkCmdUpdateBuffer								vkCmdUpdateBuffer;
PFN_vkCreateQueryPool								vkCreateQueryPool;
PFN_vkDestroyQueryPool								vkDestroyQueryPool;
PFN_vkCmdResetQueryPool								vkCmdResetQueryPool;
PFN_vkCmdBeginQuery									vkCmdBeginQuery;
PFN_vkCmdEndQuery									vkCmdEndQuery;
PFN_vkGetQueryPoolResults							vkGetQueryPoolResults;
PFN_vkCmdCopyQueryPoolResults						vkCmdCopyQueryPoolResults;
PFN_vkCmdWriteTimestamp								vkCmdWriteTimestamp;
PFN_vkCmdCopyBuffer									vkCmdCopyBuffer;
PFN_vkCmdCopyImage									vkCmdCopyImage;
PFN_vkCmdCopyBufferToImage							vkCmdCopyBufferToImage;
PFN_vkCmdCopyImageToBuffer							vkCmdCopyImageToBuffer;
PFN_vkCmdBlitImage									vkCmdBlitImage;
PFN_vkCmdResolveImage								vkCmdResolveImage;
PFN_vkCmdBindIndexBuffer							vkCmdBindIndexBuffer;
PFN_vkCmdDraw										vkCmdDraw;
PFN_vkCmdDrawIndexed								vkCmdDrawIndexed;
PFN_vkCmdDrawIndirect								vkCmdDrawIndirect;
PFN_vkCmdDrawIndexedIndirect						vkCmdDrawIndexedIndirect;
PFN_vkCmdBindVertexBuffers							vkCmdBindVertexBuffers;
PFN_vkCmdSetViewport								vkCmdSetViewport;
PFN_vkCmdSetLineWidth								vkCmdSetLineWidth;
PFN_vkCmdSetDepthBias								vkCmdSetDepthBias;
PFN_vkCmdSetBlendConstants							vkCmdSetBlendConstants;
PFN_vkCmdSetScissor									vkCmdSetScissor;
PFN_vkCmdSetDepthBounds								vkCmdSetDepthBounds;
PFN_vkCmdSetStencilCompareMask						vkCmdSetStencilCompareMask;
PFN_vkCmdSetStencilWriteMask						vkCmdSetStencilWriteMask;
PFN_vkCmdSetStencilReference						vkCmdSetStencilReference;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties	vkGetPhysicalDeviceSparseImageFormatProperties;
PFN_vkGetImageSparseMemoryRequirements				vkGetImageSparseMemoryRequirements;
PFN_vkQueueBindSparse								vkQueueBindSparse;
PFN_vkCmdDispatch									vkCmdDispatch;
PFN_vkCmdDispatchIndirect							vkCmdDispatchIndirect;
