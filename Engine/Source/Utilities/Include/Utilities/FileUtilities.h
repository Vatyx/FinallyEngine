#pragma once

#include <filesystem>
#include <vector>

namespace Finally::FileUtilities
{

std::string ReadFile(const std::filesystem::path& fileName);

}  // namespace Finally::FileUtilities
