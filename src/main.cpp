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

#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <vulkan/vulkan_core.h>

double doIntegration(IntegralPushContant &pConst,
                     SimpleComputePipeline &pipeline,
                     uint32_t const workGroupSizes[3], VkCommandBuffer cbuf,
                     VkDescriptorSet *descriptorSet, SyncObjects const &objs,
                     double const *vals);

inline std::chrono::high_resolution_clock::time_point
get_current_time_fenced() {
  std::atomic_thread_fence(std::memory_order_seq_cst);
  auto res_time = std::chrono::high_resolution_clock::now();
  std::atomic_thread_fence(std::memory_order_seq_cst);
  return res_time;
}

template <class D> inline long long to_us(const D &d) {
  return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Wrong arguments count\n"
              << "Usage: " << argv[0]
              << " <function_number> <path_to_config_file>\n";
    return Invalid_Number_Of_Arguments;
  }

  unsigned int which_function_to_calculate =
      static_cast<unsigned int>(std::stoi(argv[1]));
  const std::string configuration_file = argv[2];

  std::unordered_map<std::string, double> params =
      process_config(configuration_file);

  const std::array<std::string, 9> requiredParams{
      "init_steps_x", "init_steps_y", "x_start", "x_end",   "y_start",
      "y_end",        "abs_err",      "rel_err", "max_iter"};

  for (const std::string &elem : requiredParams) {
    if (params.find(elem) == params.end()) {
      std::cout << "Error: Missing required parameter in configuration file: "
                << elem << '\n';
      exit(Missing_Required_Parameter);
    }
  }

  IntegralPushContant pConst = {
      .start_x = params["x_start"],
      .end_x = params["x_end"],
      .splits_x = params["init_steps_x"],

      .start_y = params["y_start"],
      .end_y = params["y_end"],
      .splits_y = params["init_steps_y"],
  };

  std::vector<const char *> validation_layers = {
      "VK_LAYER_KHRONOS_validation",
  };
  std::vector<const char *> devExt = {
      // VK_KHR_SPIRV_1_4_EXTENSION_NAME,
      // VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME,
      // VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
  };

  auto instance = std::make_unique<vk_instance::Instance>();
  auto device = std::make_shared<device::DeviceHandler>(
      devExt, validation_layers, *instance, nullptr);
  auto cmd_buf = std::make_shared<command_buffer::CommandBufferHandler>(device);
  auto sync_objs = std::make_shared<SyncObjects>(device, 1);

  uint32_t *lims = device->properties.limits.maxComputeWorkGroupSize;
  uint32_t sizes[3] = {
      std::min(16U, lims[0]),
      std::min(16U, lims[1]),
      std::min(1U, lims[2]),
  };

  auto buf = std::make_shared<buffer::Buffer>(
      device, cmd_buf, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
          VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
      VK_SHARING_MODE_EXCLUSIVE, sizeof(double) * sizes[0] * sizes[1]);
  buf->map();
  double const *vals = reinterpret_cast<double *>(buf->mapped);

  VkDescriptorSetLayout layout{};
  createLayout(*device, &layout);

  VkDescriptorPool pool{};
  createDescriptorPool(*device, &pool);

  VkDescriptorSet descriptorSet{};
  createDescriptorSet(*device, &layout, pool, descriptorSet, &buf->buffer,
                      sizes);

  std::string path{};
  switch (which_function_to_calculate) {
  case 3:
    path = "./build/shaders/func3.comp.spv";
    break;
  case 2:
    path = "./build/shaders/func2.comp.spv";
    break;
  default:
    path = "./build/shaders/func1.comp.spv";
    break;
  }
  auto pipeline = SimpleComputePipeline(path, device, &layout);

  VkCommandBuffer cbuf =
      cmd_buf->createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, VK_FALSE);

  auto start = get_current_time_fenced();
  double abs_err = 0;
  double rel_err = 0;
  double prev_res = 0;
  double res = 0;
  size_t iters = 0;
  do {
    res = doIntegration(pConst, pipeline, sizes, cbuf, &descriptorSet,
                        *sync_objs, vals);
    abs_err = std::abs(prev_res - res);
    rel_err = std::abs(abs_err / res);
    prev_res = res;

    pConst.splits_x *= 2;
    pConst.splits_y *= 2;

    iters++;
  } while (abs_err >= params["abs_err"] && rel_err >= params["rel_err"] &&
           iters < params["max_iter"]);
  auto end = get_current_time_fenced();

  std::cout << res << '\n';
  std::cout << abs_err << '\n';
  std::cout << rel_err << '\n';
  std::cout << to_us(end - start) << '\n';

  vkFreeCommandBuffers(*device, cmd_buf->commandPool, 1, &cbuf);
  cleanupDescriptors(*device, layout, pool);

  return 0;
}

double doIntegration(IntegralPushContant &pConst,
                     SimpleComputePipeline &pipeline,
                     uint32_t const workGroupSizes[3], VkCommandBuffer cbuf,
                     VkDescriptorSet *descriptorSet, SyncObjects const &objs,
                     double const *vals) {
  pipeline.doIteration(cbuf, descriptorSet, objs, 0, &pConst, workGroupSizes);
  double res = 0.0F;
  for (size_t i = 0; i < workGroupSizes[0] * workGroupSizes[1]; i++) {
    res += vals[i];
  }
  double const area = (pConst.end_x - pConst.start_x) *
                      (pConst.end_y - pConst.start_y) /
                      (pConst.splits_x * pConst.splits_y);
  res *= area;
  return res;
}
