#pragma once

#include <cstdint>

namespace Finally::Renderer
{

enum class ShaderType : uint8_t
{
    Vertex,
    Fragment,
    Compute,
    Geometry,
    TeslationControl,
    TeslationEvaluation,
    MAX
};

}