#include "vulkan_base/sync_objects.h"
#include <vulkan/vulkan_core.h>

SyncObjects::SyncObjects(std::shared_ptr<device::DeviceHandler> deviceHandler,
                         std::size_t count, bool create_timed_semaphores)
    : m_deviceHandler(std::move(deviceHandler)) {
    semaphores.resize(count);
    fences.resize(count);
    if (create_timed_semaphores) {
        timed_semaphores = std::vector<VkSemaphore>(count);
    }

    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreInfo.flags = 0;

    VkSemaphoreTypeCreateInfo timelineCreateInfo;
    timelineCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
    timelineCreateInfo.pNext = nullptr;
    timelineCreateInfo.semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE;
    timelineCreateInfo.initialValue = 0;

    VkSemaphoreCreateInfo timedSemaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreInfo.flags = 0;
    timedSemaphoreInfo.pNext = &timelineCreateInfo;

    VkFenceCreateInfo fenceInfo = {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < count; i++) {
        if (vkCreateSemaphore(*m_deviceHandler, &semaphoreInfo, nullptr,
                              &semaphores[i]) != VK_SUCCESS ||
            vkCreateFence(*m_deviceHandler, &fenceInfo, nullptr, &fences[i]) !=
                VK_SUCCESS) {
            throw std::runtime_error(
                "failed to create synchronization objects!");
        }
        if (create_timed_semaphores) {
            if (vkCreateSemaphore(*m_deviceHandler, &timedSemaphoreInfo,
                                  nullptr,
                                  &(*timed_semaphores)[i]) != VK_SUCCESS) {
                throw std::runtime_error(
                    "failed to create synchronization objects!");
            }
        }
    }
}

SyncObjects::~SyncObjects() {
    for (size_t i = 0; i < semaphores.size(); i++) {
        vkDestroySemaphore(*m_deviceHandler, semaphores[i], nullptr);
        vkDestroyFence(*m_deviceHandler, fences[i], nullptr);
    }
}
