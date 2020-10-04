#pragma once

#include "Math/Vector.h"

namespace Finally::Renderer
{

struct Vertex
{
    FVector3 Position;
    FVector3 Normal;
    FVector2 UV;
};

}  // namespace Finally::Renderer