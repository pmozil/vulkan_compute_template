#pragma once

#include <vulkan/vulkan_core.h>
#ifndef BASIC_COMPUTE_PIPELINE_H
#define BASIC_COMPUTE_PIPELINE_H

#include "sync_objects.h"
#include "vulkan_base/vk_device.h"
#include <memory>

struct IntegralPushContant {
    double start_x;
    double end_x;
    double splits_x;

    double start_y;
    double end_y;
    double splits_y;
};

class SimpleComputePipeline {
    std::shared_ptr<device::DeviceHandler> m_deviceHandler;
    VkDescriptorSetLayout
        *m_descriptorSetLayout;        /**< The descriptor set layout **/
    VkPipelineLayout pipelineLayout{}; /**< The pipeline layout. */
    VkPipeline pipeline{};             /**< The compute pipeline. */

    /**
     * \brief Performs cleanup operations for the graphics pipeline.
     */
    void cleanup();
    void pushConstant(VkCommandBuffer buf, void const *push_const,
                      size_t pconst_size);

      public:
    SimpleComputePipeline() = delete;
    SimpleComputePipeline(SimpleComputePipeline &&) = delete;
    SimpleComputePipeline(SimpleComputePipeline const &) = delete;
    SimpleComputePipeline &operator=(SimpleComputePipeline &&) = delete;
    SimpleComputePipeline &operator=(SimpleComputePipeline const &) = delete;

    SimpleComputePipeline(
        std::string shader_path,
        std::shared_ptr<device::DeviceHandler> const &m_deviceHandler,
        VkDescriptorSetLayout *layout);
    ~SimpleComputePipeline() { cleanup(); }

    void dispatch(VkCommandBuffer buf, VkDescriptorSet const *descriptorSet,
                  SyncObjects const &objs, size_t iter, void const *pConst,
                  size_t pconst_size,
                  std::array<uint32_t, 3> const &disp_sizes);
    void dispatch_s(VkCommandBuffer buf, VkDescriptorSet const *descriptorSet,
                    SyncObjects const &objs, size_t iter, void const *pConst,
                    size_t pconst_size,
                    std::array<uint32_t, 3> const &disp_sizes);
};

#endif
