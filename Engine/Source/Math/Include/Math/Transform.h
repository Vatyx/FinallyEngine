#pragma once

#include "Quaternion.h"
#include "Vector.h"

namespace Finally
{

struct Transform
{
    FVector3 Location;
    Quat Rotation;
    FVector3 Size;
};

}  // namespace Finally
