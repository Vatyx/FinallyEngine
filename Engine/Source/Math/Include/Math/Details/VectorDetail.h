#pragma once

#include "Math/Details/NumericalConcept.h"

namespace Finally::Math::Details
{

template <Numerical T, size_t Size>
struct Vector
{
    T Data[Size]{};

    constexpr Vector() noexcept = default;

    template<typename... Ts>
    constexpr explicit Vector(Ts... Values) noexcept
    {
        size_t i = 0;
        ((Data[i++] = Values), ...);
    }
};

template <Numerical T>
struct Vector3
{
    union
    {
        struct
        {
            T X, Y, Z;
        };

        struct
        {
            T R, G, B;
        };

        T Data[3];
    };

    constexpr Vector3() noexcept : Data{} {}
    constexpr Vector3(T InX, T InY, T InZ) noexcept : X(InX), Y(InY), Z(InZ) {}
};

//template <Numerical T>
//struct Vector2
//{
//    union
//    {
//        struct
//        {
//            T X, Y;
//        };
//
//        struct
//        {
//            T R, G;
//        };
//
//        T Elements[2];
//    };
//
//    constexpr Vector2() noexcept : Elements{} {}
//    constexpr Vector2(T InX, T InY) noexcept : X(InX), Y(InY) {}
//};
//
//
//template <Numerical T>
//struct Vector4
//{
//    union
//    {
//        struct
//        {
//            T X, Y, Z, W;
//        };
//
//        struct
//        {
//            T R, G, B, A;
//        };
//
//        T Elements[4];
//    };
//
//    constexpr Vector4() noexcept : Elements{} {}
//    constexpr Vector4(T InX, T InY, T InZ, T InW) noexcept : X(InX), Y(InY), Z(InZ), W(InW) {}
//};

}  // namespace Finally::Math::Details
