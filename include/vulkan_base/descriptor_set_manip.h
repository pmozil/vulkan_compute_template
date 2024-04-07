#pragma once

#ifndef DESCRIPTOR_SET_MANIP_H
#define DESCRIPTOR_SET_MANIP_H

#include "common.h"

void createLayout(VkDevice device, VkDescriptorSetLayout *layout);

void createDescriptorSet(VkDevice device, VkDescriptorSetLayout *layout,
                         VkDescriptorPool &descriptorPool,
                         VkDescriptorSet &descriptorSet, VkBuffer *buf,
                         const uint32_t sizes[3]);

void createDescriptorPool(VkDevice device, VkDescriptorPool *descriptorPool);

void cleanupDescriptors(VkDevice device, VkDescriptorSetLayout &layout,
                        VkDescriptorPool &pool);

#endif
