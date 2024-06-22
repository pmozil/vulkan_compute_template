#include "exceptions.h"
#include "parse_file.h"
#include "simple_compute_pipeline.h"
#include "sync_objects.h"
#include "vulkan_base/buffer.h"
#include "vulkan_base/command_buffer.h"
#include "vulkan_base/descriptor_set_manip.h"
#include "vulkan_base/sync_objects.h"
#include "vulkan_base/vk_device.h"
#include "vulkan_base/vk_instance.h"

#include <memory>
#include <vulkan/vulkan_core.h>

int main() {
    std::vector<const char *> validation_layers = {
        "VK_LAYER_KHRONOS_validation",
    };
    std::vector<const char *> devExt = {
        VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME,
        // VK_KHR_SPIRV_1_4_EXTENSION_NAME,
        // VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME,
        // VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
    };

    const int n_vals = 10'000'000;
    auto instance = std::make_unique<vk_instance::Instance>();
    auto device = std::make_shared<device::DeviceHandler>(
        devExt, validation_layers, *instance, nullptr);
    auto cmd_buf =
        std::make_shared<command_buffer::CommandBufferHandler>(device);
    auto sync_objs = std::make_shared<SyncObjects>(device, 1);

    std::array<uint32_t, 3> sizes = {100, 100, 100};

    auto buf = std::make_shared<buffer::Buffer>(
        device, cmd_buf, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
            VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        VK_SHARING_MODE_EXCLUSIVE, sizeof(int) * n_vals);
    buf->map();
    int *vals = reinterpret_cast<int *>(buf->mapped);

    for (int i = 0; i < n_vals; i++) {
        if (i % 2 == 0) {
            vals[(i / 2)] = (i / 2);
        } else {
            vals[9'999'999 - (i / 2)] = 9'999'999 - (i / 2);
        }
    }

    VkDescriptorSetLayout layout{};
    createLayout(*device, &layout);

    VkDescriptorPool pool{};
    createDescriptorPool(*device, &pool);

    VkDescriptorSet descriptorSet{};
    createDescriptorSet(*device, &layout, pool, descriptorSet, &buf->buffer,
                        sizes.data());

    std::string path = "./build/shaders/compute.comp.spv";
    auto pipeline = SimpleComputePipeline(path, device, &layout);

    VkCommandBuffer cbuf =
        cmd_buf->createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, VK_FALSE);

    pipeline.dispatch_s(cbuf, &descriptorSet, *sync_objs, 0, &n_vals,
                        sizeof(n_vals), sizes);

    vkFreeCommandBuffers(*device, cmd_buf->commandPool, 1, &cbuf);
    cleanupDescriptors(*device, layout, pool);

    return 0;
}
