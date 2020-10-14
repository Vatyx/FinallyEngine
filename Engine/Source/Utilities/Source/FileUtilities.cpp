
#include "Utilities/FileUtilities.h"

#include <fstream>
#include <stdexcept>

namespace Finally::FileUtilities
{

std::string ReadFile(const std::filesystem::path& fileName)
{
    std::ifstream file(fileName, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::string buffer;
    buffer.resize(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

}  // namespace Finally::FileUtilities
