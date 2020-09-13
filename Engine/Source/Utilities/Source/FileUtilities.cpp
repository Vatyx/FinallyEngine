
#include "Utilities/FileUtilities.h"

#include <fstream>
#include <stdexcept>

namespace Finally::FileUtilities
{

std::vector<char> ReadFile(const std::string& FileName)
{
    std::ifstream File(FileName, std::ios::ate | std::ios::binary);

    if (!File.is_open()) { throw std::runtime_error("Failed to open file!"); }

    size_t            FileSize = (size_t)File.tellg();
    std::vector<char> Buffer(FileSize);

    File.seekg(0);
    File.read(Buffer.data(), FileSize);

    File.close();

    return Buffer;
}

}  // namespace Finally::FileUtilities
