#pragma once

#ifndef VK_COMMON_H
#define VK_COMMON_H

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>
#include <vulkan/vulkan.h>

constexpr size_t VK_API_VERSION = VK_API_VERSION_1_3;
constexpr size_t GLOBAL_VERSION = VK_MAKE_VERSION(1, 0, 0);

#ifndef NDEBUG
constexpr bool enableValidationLayers = true;
static constexpr std::array<const char *, 1> VALIDATION_LAYERS = {
    "VK_LAYER_KHRONOS_validation",
};
#else
constexpr bool enableValidationLayers = false;
static constexpr std::array<const char *, 0> VALIDATION_LAYERS = {};
#endif

inline constexpr void UNUSED(auto val) { (void)(val); }

// Data structure to store queue family indices
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    std::optional<uint32_t> computeFamily;
    std::optional<uint32_t> transferFamily;

    // Check if all required queue families are present
    [[nodiscard]] inline bool isComplete() const {
        return computeFamily.has_value();
    }

    // Check if a dedicated transfer queue family is available
    [[nodiscard]] inline bool hasDedicatedTransfer() const {
        return transferFamily.has_value();
    }
};

// Macro for checking Vulkan function calls for errors
#define VK_CHECK(f)                                                            \
    {                                                                          \
        VkResult res = (f);                                                    \
        if (res != VK_SUCCESS) {                                               \
            std::cout << "Fatal : VkResult is \"" << res << "\" in "           \
                      << __FILE__ << " at line " << __LINE__ << "\n";          \
            assert(res == VK_SUCCESS);                                         \
        }                                                                      \
    }

static constexpr size_t DEFAULT_FENCE_TIMEOUT =
    std::numeric_limits<size_t>::max();

#endif
