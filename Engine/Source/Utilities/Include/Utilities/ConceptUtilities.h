#pragma once

#include <concepts>
#include <type_traits>

namespace Finally
{

template <typename Class, typename BaseClass>
concept IsBaseOf = std::is_base_of<BaseClass, Class>::value;

template <typename T, typename U>
concept Return = std::same_as<T, U>;

template <typename T>
concept RvalueRef = std::is_rvalue_reference_v<T&&>;

}
