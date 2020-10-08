#pragma once

#include <type_traits>

namespace Finally
{

template <typename Class, typename BaseClass>
concept IsBaseOf = std::is_base_of<BaseClass, Class>::value;

}
