#pragma once

#include <string>
#include <vector>

namespace Finally::FileUtilities
{

std::vector<char> ReadFile(const std::string& FileName);

}  // namespace Finally::FileUtilities
