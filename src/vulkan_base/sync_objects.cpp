#include "vulkan_base/sync_objects.h"

SyncObjects::SyncObjects(std::shared_ptr<device::DeviceHandler> deviceHandler,
                         std::size_t count)
    : m_deviceHandler(deviceHandler) {
  semaphores.resize(count);
  fences.resize(count);

  VkSemaphoreCreateInfo semaphoreInfo = {};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkFenceCreateInfo fenceInfo = {};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  for (size_t i = 0; i < count; i++) {
    if (vkCreateSemaphore(*m_deviceHandler, &semaphoreInfo, nullptr,
                          &semaphores[i]) != VK_SUCCESS ||
        vkCreateFence(*m_deviceHandler, &fenceInfo, nullptr, &fences[i]) !=
            VK_SUCCESS) {
      throw std::runtime_error("failed to create synchronization objects!");
    }
  }
}

SyncObjects::~SyncObjects() {
  for (size_t i = 0; i < semaphores.size(); i++) {
    vkDestroySemaphore(*m_deviceHandler, semaphores[i], nullptr);
    vkDestroyFence(*m_deviceHandler, fences[i], nullptr);
  }
}
