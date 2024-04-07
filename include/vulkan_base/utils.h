#pragma once
#include "common.h"

namespace utils {
/**
 * \fn bool fileExists(const std::string &filename)
 *
 * \brief Check if file exists
 *
 * \param filename The file to be checked
 */
bool fileExists(const std::string &filename);

/**
 * \fn void exitFatal(const std::string& message, int32_t exitCode)
 *
 * \brief Closes the program
 *
 * \param message The error message
 * \param exitCode The exit code
 */
void exitFatal(const std::string &message, int32_t exitCode);

uint32_t alignedSize(uint32_t value, uint32_t alignment);

VkShaderModule loadShader(const char *fileName, VkDevice device);

} // namespace utils
