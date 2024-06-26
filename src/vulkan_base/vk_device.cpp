#include "vulkan_base/vk_device.h"
#include "vulkan_base/common.h"
#include "vulkan_base/create_info.h"

#include <cstring>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vulkan/vulkan_core.h>

namespace device {
bool DeviceHandler::m_checkDeviceExtensions(VkPhysicalDevice device) {
    uint32_t extensionCount{};
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                         nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                         availableExtensions.data());

    std::set<std::string> requiredExtensions(m_deviceExtensions.begin(),
                                             m_deviceExtensions.end());

    for (const auto &extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

bool DeviceHandler::m_deviceIsSuitable(VkPhysicalDevice device) {
    QueueFamilyIndices indices = getQueueFamilyIndices(device);

    bool extensionsSupported = m_checkDeviceExtensions(device);

    return indices.isComplete() && extensionsSupported;
}

long int DeviceHandler::m_rateDevice(VkPhysicalDevice device) {
    if (!m_deviceIsSuitable(device)) {
        return -1;
    }

    long int score = 0;

    vkGetPhysicalDeviceProperties(device, &properties);
    vkGetPhysicalDeviceFeatures(device, &enabledFeatures);

    score += properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
                 ? DISCRETE_GPU_BONUS
                 : INTEGRATED_GPU_BONUS;
    score += properties.limits.maxImageDimension2D;
    score *= enabledFeatures.geometryShader;

    return score;
}

void DeviceHandler::m_pickDevice() {
    std::multimap<int, VkPhysicalDevice> candidates;
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, devices.data());

    for (const auto &device : devices) {
        int score = m_rateDevice(device);
        candidates.emplace(std::make_pair(score, device));
    }

    if (candidates.rbegin()->first > 0) {
        physicalDevice = candidates.rbegin()->second;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

    } else {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

void DeviceHandler::m_createLogicalDevice(VkPhysicalDeviceFeatures2 *pNext,
                                          VkAllocationCallbacks *pAllocator) {
    QueueFamilyIndices indices = getQueueFamilyIndices(physicalDevice);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.computeFamily.value()};

    if (indices.hasDedicatedTransfer()) {
        uniqueQueueFamilies = {
            indices.computeFamily.value(),
            indices.transferFamily.value(),
        };
    }

    float queuePriority = 1.0F;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo =
            create_info::queueCreateInfo(queueFamily, &queuePriority);
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures = {};
    // deviceFeatures.bufferDeviceAddress = VK_TRUE;

    VkDeviceCreateInfo createInfo =
        create_info::deviceCreateInfo(queueCreateInfos, m_deviceExtensions,
                                      m_validationLayers, &deviceFeatures);

    if (pNext != VK_NULL_HANDLE) {
        pNext->features = enabledFeatures;
        createInfo.pEnabledFeatures = nullptr;
        createInfo.pNext = pNext;
    }

    VK_CHECK(vkCreateDevice(physicalDevice, &createInfo, pAllocator,
                            &logicalDevice));

    vkGetDeviceQueue(logicalDevice, indices.computeFamily.value(), 0,
                     &computeQueue);

    if (indices.hasDedicatedTransfer()) {
        vkGetDeviceQueue(logicalDevice, indices.transferFamily.value(), 0,
                         &transferQueue);
    }
}

QueueFamilyIndices
DeviceHandler::getQueueFamilyIndices(VkPhysicalDevice &device) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                             nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                             queueFamilies.data());

    int idx = 0;
    for (const auto &queueFamily : queueFamilies) {
        const VkQueueFlags maskedFlags =
            (~VK_QUEUE_SPARSE_BINDING_BIT & queueFamily.queueFlags);
        if (static_cast<bool>(maskedFlags & VK_QUEUE_COMPUTE_BIT)) {
            indices.computeFamily = idx;
        }

        if (static_cast<bool>(maskedFlags & VK_QUEUE_TRANSFER_BIT) &&
            !static_cast<bool>(maskedFlags & VK_QUEUE_GRAPHICS_BIT)) {
            indices.transferFamily = idx;
        }

        if (indices.isComplete()) {
            break;
        }

        idx++;
    }

    return indices;
}

DeviceHandler::DeviceHandler(std::vector<const char *> &devExt,
                             std::vector<const char *> &validations,
                             VkInstance m_vkInstance,
                             VkPhysicalDeviceFeatures2 *pNext)
    : m_deviceExtensions(devExt), m_validationLayers(validations),
      m_vkInstance(m_vkInstance) {
    m_pickDevice();
    m_createLogicalDevice(pNext);
}

uint32_t DeviceHandler::getMemoryType(uint32_t typeBits,
                                      VkMemoryPropertyFlags mem_props,
                                      VkBool32 *memTypeFound) const {
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
        if ((typeBits & 1) == 1) {
            if ((memoryProperties.memoryTypes[i].propertyFlags & mem_props) ==
                mem_props) {
                if (memTypeFound != nullptr) {
                    *memTypeFound = static_cast<VkBool32>(true);
                }
                return i;
            }
        }
        typeBits >>= 1;
    }

    if (memTypeFound != nullptr) {
        *memTypeFound = static_cast<VkBool32>(false);
        return 0;
    }
    throw std::runtime_error("Could not find a matching memory type");
}

VkResult DeviceHandler::createBuffer(VkBufferUsageFlags usageFlags,
                                     VkMemoryPropertyFlags memoryPropertyFlags,
                                     VkDeviceSize size, VkBuffer *buffer,
                                     VkDeviceMemory *memory, void *data) const {
    // Create the buffer handle
    VkBufferCreateInfo bufferCreateInfo =
        create_info::bufferCreateInfo(usageFlags, size);
    VK_CHECK(vkCreateBuffer(logicalDevice, &bufferCreateInfo, nullptr, buffer));

    // Create the memory backing up the buffer handle
    VkMemoryRequirements memReqs;
    vkGetBufferMemoryRequirements(logicalDevice, *buffer, &memReqs);

    VkMemoryAllocateInfo memAlloc = create_info::memoryAllocInfo(
        memReqs.size,
        getMemoryType(memReqs.memoryTypeBits, memoryPropertyFlags));
    // If the buffer has VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT set we also
    // need to enable the appropriate flag during allocation
    VkMemoryAllocateFlagsInfoKHR allocFlagsInfo{};
    if (static_cast<bool>(usageFlags &
                          VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT)) {
        allocFlagsInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO_KHR;
        allocFlagsInfo.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR;
        memAlloc.pNext = &allocFlagsInfo;
    }
    VK_CHECK(vkAllocateMemory(logicalDevice, &memAlloc, nullptr, memory));

    // If a pointer to the buffer data has been passed, map the buffer and copy
    // over the data
    if (data != nullptr) {
        void *mapped{};
        VK_CHECK(vkMapMemory(logicalDevice, *memory, 0, size, 0, &mapped));
        std::memcpy(mapped, data, size);
        // If host coherency hasn't been requested, do a manual flush to make
        // writes visible
        if ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0) {
            VkMappedMemoryRange mappedRange{};
            mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
            mappedRange.memory = *memory;
            mappedRange.offset = 0;
            mappedRange.size = size;
            vkFlushMappedMemoryRanges(logicalDevice, 1, &mappedRange);
        }
        vkUnmapMemory(logicalDevice, *memory);
    }

    // Attach the memory to the buffer object
    VK_CHECK(vkBindBufferMemory(logicalDevice, *buffer, *memory, 0));

    return VK_SUCCESS;
}
} // namespace device
