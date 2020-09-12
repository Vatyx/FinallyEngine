#pragma once

#include <type_traits>

namespace Finally {
namespace EnumUtilities
{

template< typename Enumeration >
constexpr std::size_t EnumCount() noexcept
{
	static_assert(std::is_enum< Enumeration >::value, "Not an enum");
	return static_cast<std::size_t>(Enumeration::MAX);
}

template< typename Enumeration >
constexpr std::size_t EnumIndex(const Enumeration value) noexcept
{
	static_assert(std::is_enum< Enumeration >::value, "Not an enum");
	return static_cast<std::size_t>(value);
}

} // namespace EnumUtilities
} // namespace Finally
