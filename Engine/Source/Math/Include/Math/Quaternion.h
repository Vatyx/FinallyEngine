#pragma once

#include "Vector.h"

#include <type_traits>

namespace Finally
{

struct Quat
{
    struct
    {
        float X;
        float Y;
        float Z;
        float W;
    };

    float Elements[4];

    constexpr Quat() noexcept : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {}  // NOLINT(cppcoreguidelines-pro-type-member-init)
    constexpr Quat(float InX, float InY, float InZ, float InW) noexcept
        : X(InX),
          Y(InY),
          Z(InZ),
          W(InW) {}  // NOLINT(cppcoreguidelines-pro-type-member-init)
};

static_assert(std::is_standard_layout_v<Quat>, "Quat is not standard layout");

}  // namespace Finally
