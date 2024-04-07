#pragma once

#ifndef COMMAND_BUFFER_H
#define COMMAND_BUFFER_H

#include "common.h"
#include "vulkan_base/vk_device.h"

#include <memory>

namespace command_buffer {
/**
 * \class CommandBufferHandler
 * \brief Wrapper class for Vulkan command buffer handling.
 *
 * The CommandBufferHandler class provides an interface for managing Vulkan
 * command buffers.
 */
class CommandBufferHandler {
public:
  CommandBufferHandler(CommandBufferHandler &&) = delete;
  CommandBufferHandler(CommandBufferHandler const &) = delete;
  CommandBufferHandler &operator=(CommandBufferHandler &&) = delete;
  CommandBufferHandler &operator=(CommandBufferHandler const &) = delete;
  /**
   * \brief Constructs a CommandBufferHandler object.
   *
   * \param m_deviceHandler The device handler used for command buffer
   * operations. \param m_swapChain The swap chain associated with the command
   * buffers. \param m_graphicsPipeline The graphics pipeline associated with
   * the command buffers.
   */
  CommandBufferHandler(std::shared_ptr<device::DeviceHandler> m_deviceHandler);

  /**
   * \brief Destructor for the CommandBufferHandler object.
   *
   * Cleans up the command buffer handler resources.
   */
  ~CommandBufferHandler() { cleanup(); }

  // operator VkCommandPool *() { return &commandPool; }
  operator VkCommandPool const &() const { return commandPool; }
  operator VkCommandPool &() { return commandPool; }

  VkCommandPool commandPool{}; /**< The Vulkan command pool. */

  /**
   * \brief Cleans up the command buffer handler resources.
   *
   * This function destroys the Vulkan command pool.
   */
  void cleanup();

  /**
   * \fn VkCommandPool createCommandPool(uint32_t
   * queueFamilyIndex, VkCommandPoolCreateFlags createFlags =
   * VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
   *
   * \brief Creates a
   * command pool for the specified queue family index.
   *
   * \param queueFamilyIndex The index of the queue family associated with the
   * command pool.
   * \param createFlags The optional create flags for the
   * command pool.
   *
   * \return The created command pool.
   */
  [[nodiscard]] VkCommandPool
  createCommandPool(uint32_t queueFamilyIndex,
                    VkCommandPoolCreateFlags createFlags =
                        VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT) const;

  /**
   * \fn VkCommandBuffer createCommandBuffer(VkCommandBufferLevel level,
   * VkCommandPool pool, bool begin = false)
   *
   * \brief Creates a command
   * buffer of the specified level from the given command pool.
   *
   * \param level The level of the command buffer.
   * \param pool The command pool from which to allocate the command buffer.
   * \param begin Whether to begin the command buffer recording.
   *
   * \return The created command buffer.
   */
  [[nodiscard]] VkCommandBuffer createCommandBuffer(VkCommandBufferLevel level,
                                                    bool begin = false) const;

  /**
   * \fn flushCommandBuffer(VkCommandBuffer buf, VkQueue queue)
   *
   * \brief Sends the command buffer to a queue
   *
   * \param buf The buffer
   * \param queue The queue
   * \param free Whether to free the buffer adter
   */
  void flushCommandBuffer(VkCommandBuffer buf, VkQueue queue, bool free = true);

protected:
  std::shared_ptr<device::DeviceHandler>
      m_deviceHandler; /**< The device handler used for command buffer
                          operations. */

  /**
   * \brief Creates the Vulkan command pool.
   *
   * This function creates the Vulkan command pool for allocating command
   * buffers.
   */
  void m_createCommandPool();
};

} // namespace command_buffer

#endif
