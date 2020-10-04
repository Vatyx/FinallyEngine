#pragma once

#include "Math/Details/NumericalConcept.h"

namespace Finally
{

template <Numerical T, size_t Rows, size_t Columns>
struct Matrix
{
    T Data[Columns][Rows]{};

    constexpr Matrix() = default;

    template <typename... Ts>
    constexpr explicit Matrix(Ts... Values) noexcept
    {
        size_t i = 0;
        ((Data[i++] = Values), ...);
    }
};

}  // namespace Finally
