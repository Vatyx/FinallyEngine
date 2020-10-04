#pragma once

#include "Math/Details/VectorDetail.h"

#include <cstdint>
#include <type_traits>

namespace Finally
{

using FVector3 = Math::Details::Vector3<float>;
using FVector2 = Math::Details::Vector<float, 2>;
using FVector4 = Math::Details::Vector<float, 4>;

static_assert(std::is_standard_layout_v<FVector2>, "FVector2 is not standard layout");
static_assert(std::is_standard_layout_v<FVector3>, "FVector3 is not standard layout");
static_assert(std::is_standard_layout_v<FVector4>, "FVector4 is not standard layout");

using IVector3 = Math::Details::Vector3<int32_t>;
using IVector2 = Math::Details::Vector<int32_t, 2>;
using IVector4 = Math::Details::Vector<int32_t, 4>;

static_assert(std::is_standard_layout_v<IVector2>, "IVector2 is not standard layout");
static_assert(std::is_standard_layout_v<IVector3>, "IVector3 is not standard layout");
static_assert(std::is_standard_layout_v<IVector4>, "IVector4 is not standard layout");

}  // namespace Finally
