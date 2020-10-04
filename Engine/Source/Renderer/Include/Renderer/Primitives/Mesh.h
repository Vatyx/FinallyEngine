#pragma once

#include "Renderer/Primitives/Vertex.h"

#include <vector>

namespace Finally::Renderer
{

struct Mesh
{
    std::vector<Vertex> Vertices;
    std::vector<uint32_t> Indices;
};

};  // namespace Finally::Renderer