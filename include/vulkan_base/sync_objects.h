#pragma once

#ifndef SYNC_OBJECTS_H
#define SYNC_OBJECTS_H

#include "common.h"
#include "vk_device.h"
#include <memory>

class SyncObjects {
  std::shared_ptr<device::DeviceHandler> m_deviceHandler;

public:
  SyncObjects(SyncObjects &&) = delete;
  SyncObjects(SyncObjects const &) = delete;
  SyncObjects &operator=(SyncObjects &&) = delete;
  SyncObjects &operator=(SyncObjects const &) = delete;

  std::vector<VkSemaphore> semaphores{};
  std::vector<VkFence> fences{};

  SyncObjects(std::shared_ptr<device::DeviceHandler> deviceHandler,
              std::size_t count);
  ~SyncObjects();
};

#endif
