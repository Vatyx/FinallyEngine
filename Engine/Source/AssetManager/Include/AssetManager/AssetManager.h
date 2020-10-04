#pragma once

#include <string_view>

namespace Finally
{

class AssetManager
{
public:
    AssetManager() = default;

    void LoadPath(std::string_view Path);

    void ImportPath(std::string_view Path);
};

}