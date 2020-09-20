#pragma once

#include <type_traits>

namespace Finally
{

template <typename T>
concept Numerical = std::is_integral_v<T> || std::is_floating_point_v<T>;

}
