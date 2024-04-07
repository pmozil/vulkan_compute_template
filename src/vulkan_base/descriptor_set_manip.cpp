#include "vulkan_base/descriptor_set_manip.h"
#include "vulkan_base/create_info.h"
#include <vector>

void createLayout(VkDevice device, VkDescriptorSetLayout *layout) {
  std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings = {
      create_info::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                              VK_SHADER_STAGE_COMPUTE_BIT, 0),
  };

  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = 1;
  layoutInfo.pBindings = setLayoutBindings.data();

  VK_CHECK(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, layout));
}

void createDescriptorPool(VkDevice device, VkDescriptorPool *descriptorPool) {
  std::array<VkDescriptorPoolSize, 1> poolSizes{};
  poolSizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
  poolSizes[0].descriptorCount = 1;

  VkDescriptorPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  poolInfo.poolSizeCount = 1;
  poolInfo.pPoolSizes = poolSizes.data();
  poolInfo.maxSets = 1;

  VK_CHECK(vkCreateDescriptorPool(device, &poolInfo, nullptr, descriptorPool));
}

void createDescriptorSet(VkDevice device, VkDescriptorSetLayout *layout,
                         VkDescriptorPool &descriptorPool,
                         VkDescriptorSet &descriptorSet, VkBuffer *buf,
                         const uint32_t sizes[3]) {
  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptorPool;
  allocInfo.descriptorSetCount = 1;
  allocInfo.pSetLayouts = layout;

  VK_CHECK(vkAllocateDescriptorSets(device, &allocInfo, &descriptorSet));

  VkDescriptorBufferInfo storageBufferInfo{};
  storageBufferInfo.buffer = *buf;
  storageBufferInfo.offset = 0;
  storageBufferInfo.range = sizeof(double) * sizes[0] * sizes[1];

  std::array<VkWriteDescriptorSet, 1> descriptorWrites{};
  descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  descriptorWrites[0].dstSet = descriptorSet;
  descriptorWrites[0].dstBinding = 0;
  descriptorWrites[0].dstArrayElement = 0;
  descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
  descriptorWrites[0].descriptorCount = 1;
  descriptorWrites[0].pBufferInfo = &storageBufferInfo;

  vkUpdateDescriptorSets(device, 1, descriptorWrites.data(), 0, nullptr);
}

void cleanupDescriptors(VkDevice device,
                        VkDescriptorSetLayout &layout, VkDescriptorPool &pool) {
  vkDestroyDescriptorPool(device, pool, nullptr);
  vkDestroyDescriptorSetLayout(device, layout, nullptr);
}
