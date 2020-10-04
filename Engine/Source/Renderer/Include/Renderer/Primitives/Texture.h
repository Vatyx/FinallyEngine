#pragma once

#include <cstdint>

namespace Finally::Renderer
{

struct Texture2D
{
    void* Data;
    uint32_t Width;
    uint32_t Height;
};

}  // namespace Finally::Renderer