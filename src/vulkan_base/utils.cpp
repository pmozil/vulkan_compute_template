#include "vulkan_base/common.h"

#include <fstream>

namespace utils {
void exitFatal(const std::string &message, int32_t exitCode) {
#if defined(_WIN32)
    if (!errorModeSilent) {
        MessageBox(NULL, message.c_str(), NULL, MB_OK | MB_ICONERROR);
    }
#elif defined(__ANDROID__)
    LOGE("Fatal error: %s", message.c_str());
    vks::android::showAlert(message.c_str());
#endif
    std::cerr << message << "\n";
#if !defined(__ANDROID__)
    exit(exitCode);
#endif
}

bool fileExists(const std::string &filename) {
    std::ifstream file(filename.c_str());
    return !file.fail();
}

uint32_t alignedSize(uint32_t value, uint32_t alignment) {
    return (value + alignment - 1) & ~(alignment - 1);
}

VkShaderModule loadShader(const char *fileName, VkDevice device) {
    std::ifstream input(fileName,
                        std::ios::binary | std::ios::in | std::ios::ate);

    if (!input.is_open()) {
        std::cerr << "Error: Could not open shader file \"" << fileName << "\""
                  << "\n";
        return VK_NULL_HANDLE;
    }

    ssize_t size = input.tellg();
    input.seekg(0, std::ios::beg);
    char *shaderCode = new char[size];
    input.read(shaderCode, size);
    input.close();

    assert(size > 0);

    VkShaderModule shaderModule{};
    VkShaderModuleCreateInfo moduleCreateInfo{};
    moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    moduleCreateInfo.codeSize = size;
    moduleCreateInfo.pCode = reinterpret_cast<uint32_t *>(shaderCode);

    VK_CHECK(vkCreateShaderModule(device, &moduleCreateInfo, nullptr,
                                  &shaderModule));

    delete[] shaderCode;

    return shaderModule;
}
} // namespace utils
