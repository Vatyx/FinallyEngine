
#pragma once

namespace Finally::Math
{

struct Vector
{
    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;

    Vector() = default;
    Vector(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}
};

}
