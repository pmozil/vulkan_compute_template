#include "vulkan_base/command_buffer.h"
#include "vulkan_base/create_info.h"

namespace command_buffer {
CommandBufferHandler::CommandBufferHandler(
    std::shared_ptr<device::DeviceHandler> m_deviceHandler)
    : m_deviceHandler(m_deviceHandler) {
    m_createCommandPool();
}

void CommandBufferHandler::m_createCommandPool() {
    QueueFamilyIndices queueFamilyIndices =
        m_deviceHandler->getQueueFamilyIndices(m_deviceHandler->physicalDevice);

    if (!queueFamilyIndices.computeFamily.has_value()) {
        return;
    }

    VkCommandPoolCreateInfo poolInfo =
        create_info::commandPoolCreateInfo(*queueFamilyIndices.computeFamily);
    VK_CHECK(vkCreateCommandPool(m_deviceHandler->logicalDevice, &poolInfo,
                                 nullptr, &commandPool));
}

void CommandBufferHandler::cleanup() {
    vkDestroyCommandPool(*m_deviceHandler, commandPool, nullptr);
}

[[nodiscard]] VkCommandPool CommandBufferHandler::createCommandPool(
    uint32_t queueFamilyIndex, VkCommandPoolCreateFlags createFlags) const {
    VkCommandPoolCreateInfo commandPoolCreateInfo =
        create_info::commandPoolCreateInfo(queueFamilyIndex);
    commandPoolCreateInfo.flags = createFlags;
    VkCommandPool comPool{};
    VK_CHECK(vkCreateCommandPool(*m_deviceHandler, &commandPoolCreateInfo,
                                 nullptr, &comPool));
    return comPool;
}

[[nodiscard]] VkCommandBuffer
CommandBufferHandler::createCommandBuffer(VkCommandBufferLevel level,
                                          bool begin) const {
    VkCommandBufferAllocateInfo allocInfo =
        create_info::commandBufferAllocInfo(commandPool, 1);
    allocInfo.level = level;

    VkCommandBuffer cmdBuffer{};
    VK_CHECK(
        vkAllocateCommandBuffers(*m_deviceHandler, &allocInfo, &cmdBuffer));
    // If requested, also start recording for the new command buffer
    if (begin) {
        VkCommandBufferBeginInfo bufferBeginInfo{};
        bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        VK_CHECK(vkBeginCommandBuffer(cmdBuffer, &bufferBeginInfo));
    }
    return cmdBuffer;
}

void CommandBufferHandler::flushCommandBuffer(VkCommandBuffer buf,
                                              VkQueue queue, bool free) {
    if (buf == VK_NULL_HANDLE) {
        return;
    }

    VK_CHECK(vkEndCommandBuffer(buf));

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &buf;
    // Create fence to ensure that the command buffer has finished executing
    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = 0;

    VkFence fence{};
    VK_CHECK(vkCreateFence(*m_deviceHandler, &fenceInfo, nullptr, &fence));
    // Submit to the queue
    VK_CHECK(vkQueueSubmit(queue, 1, &submitInfo, fence));
    // Wait for the fence to signal that command buffer has finished executing
    VK_CHECK(vkWaitForFences(*m_deviceHandler, 1, &fence, VK_TRUE,
                             DEFAULT_FENCE_TIMEOUT));
    vkDestroyFence(*m_deviceHandler, fence, nullptr);
    if (free) {
        vkFreeCommandBuffers(*m_deviceHandler, commandPool, 1, &buf);
    }
}
} // namespace command_buffer
