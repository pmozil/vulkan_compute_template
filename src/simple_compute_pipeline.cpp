#include "simple_compute_pipeline.h"
#include "common.h"
#include "vulkan_base/sync_objects.h"
#include "vulkan_base/utils.h"
#include <stdexcept>
#include <vulkan/vulkan_core.h>

SimpleComputePipeline::SimpleComputePipeline(
    std::string shader_path,
    std::shared_ptr<device::DeviceHandler> const &m_deviceHandler,
    VkDescriptorSetLayout *layout)
    : m_deviceHandler{m_deviceHandler}, m_descriptorSetLayout{layout} {
    if (!utils::fileExists(shader_path)) {
        std::string msg{"No shader named "};
        msg += shader_path;
        msg += "\n";
        utils::exitFatal(msg, 2);
    }

    // Create shader modules
    VkShaderModule computeShaderModule =
        utils::loadShader(shader_path.data(), *m_deviceHandler);

    VkPipelineShaderStageCreateInfo computeShaderStageInfo{};
    computeShaderStageInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    computeShaderStageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    computeShaderStageInfo.module = computeShaderModule;
    computeShaderStageInfo.pName = "main";

    VkPushConstantRange push_constant;
    push_constant.offset = 0;
    push_constant.size = sizeof(IntegralPushContant);
    push_constant.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = m_descriptorSetLayout;
    pipelineLayoutInfo.pPushConstantRanges = &push_constant;
    pipelineLayoutInfo.pushConstantRangeCount = 1;

    if (vkCreatePipelineLayout(*m_deviceHandler, &pipelineLayoutInfo, nullptr,
                               &pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create compute pipeline layout!");
    }

    VkComputePipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    pipelineInfo.layout = pipelineLayout;
    pipelineInfo.stage = computeShaderStageInfo;
    if (vkCreateComputePipelines(*m_deviceHandler, VK_NULL_HANDLE, 1,
                                 &pipelineInfo, nullptr,
                                 &pipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create compute pipeline!");
    }

    vkDestroyShaderModule(*m_deviceHandler, computeShaderModule, nullptr);
}

void SimpleComputePipeline::cleanup() {
    vkDestroyPipeline(m_deviceHandler->logicalDevice, pipeline, nullptr);
    vkDestroyPipelineLayout(m_deviceHandler->logicalDevice, pipelineLayout,
                            nullptr);
}

void SimpleComputePipeline::pushConstant(VkCommandBuffer buf,
                                         void const *push_const,
                                         size_t pconst_size) {
    vkCmdPushConstants(buf, pipelineLayout, VK_SHADER_STAGE_COMPUTE_BIT, 0,
                       pconst_size, push_const);
}

void SimpleComputePipeline::dispatch(
    VkCommandBuffer buf, VkDescriptorSet const *descriptorSet,
    SyncObjects const &objs, size_t iter, void const *pConst,
    size_t pconst_size, std::array<uint32_t, 3> const &disp_sizes) {
    size_t const cur_it = iter % objs.fences.size();
    vkWaitForFences(*m_deviceHandler, 1, &objs.fences[cur_it], VK_TRUE,
                    DEFAULT_FENCE_TIMEOUT);
    vkResetFences(*m_deviceHandler, 1, &objs.fences[cur_it]);
    vkResetCommandBuffer(buf, 0);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    VK_CHECK(vkBeginCommandBuffer(buf, &beginInfo));
    vkCmdBindPipeline(buf, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
    vkCmdBindDescriptorSets(buf, VK_PIPELINE_BIND_POINT_COMPUTE, pipelineLayout,
                            0, 1, descriptorSet, 0, nullptr);
    pushConstant(buf, pConst, pconst_size);
    if (pConst != nullptr) {
        vkCmdDispatch(buf, disp_sizes[0], disp_sizes[1], disp_sizes[2]);
    }

    VK_CHECK(vkEndCommandBuffer(buf));

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &buf;
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &objs.semaphores[cur_it];

    vkQueueWaitIdle(m_deviceHandler->computeQueue);
    VK_CHECK(vkQueueSubmit(m_deviceHandler->computeQueue, 1, &submitInfo,
                           objs.fences[cur_it]));
}

void SimpleComputePipeline::dispatch_s(
    VkCommandBuffer buf, VkDescriptorSet const *descriptorSet,
    SyncObjects const &objs, size_t iter, void const *pConst,
    size_t pconst_size, std::array<uint32_t, 3> const &disp_sizes) {
    size_t const cur_it = iter % objs.fences.size();
    vkWaitForFences(*m_deviceHandler, 1, &objs.fences[cur_it], VK_TRUE,
                    DEFAULT_FENCE_TIMEOUT);
    vkResetFences(*m_deviceHandler, 1, &objs.fences[cur_it]);
    vkResetCommandBuffer(buf, 0);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    VK_CHECK(vkBeginCommandBuffer(buf, &beginInfo));
    vkCmdBindPipeline(buf, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
    vkCmdBindDescriptorSets(buf, VK_PIPELINE_BIND_POINT_COMPUTE, pipelineLayout,
                            0, 1, descriptorSet, 0, nullptr);
    pushConstant(buf, pConst, pconst_size);
    if (pConst != nullptr) {
        vkCmdDispatch(buf, disp_sizes[0], disp_sizes[1], disp_sizes[2]);
    }

    VK_CHECK(vkEndCommandBuffer(buf));

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &buf;
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &objs.semaphores[cur_it];

    vkQueueWaitIdle(m_deviceHandler->computeQueue);
    VK_CHECK(vkQueueSubmit(m_deviceHandler->computeQueue, 1, &submitInfo,
                           objs.fences[cur_it]));
    vkQueueWaitIdle(m_deviceHandler->computeQueue);
}
