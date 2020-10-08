#pragma once

#include "Math/Vector.h"

#include <vector>

namespace Finally::Core
{

struct Vertex
{
    FVector3 position;
    FVector3 normal;
    FVector2 uV;
};

struct Mesh
{
    std::vector<Vertex> vertices;
};


}