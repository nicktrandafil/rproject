/*
  MIT License

  Copyright (c) 2019 Nicolai Trandafil

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#pragma once

#include <yenxo/preprocessor.hpp>
#include <yenxo/type_name.hpp>

#include <boost/hana/detail/preprocessor.hpp>
#include <boost/hana/detail/struct_macros.hpp>
#include <boost/hana/tuple.hpp>

#include <array>
#include <cassert>
#include <iostream>
#include <stdexcept>

namespace yenxo {

/// Enum value is not handled or the value is not of the enum at all
///
/// \ingroup group-exceptions
class BadEnumValue : public std::runtime_error {
public:
    template <class E>
    explicit BadEnumValue(E v)
            : std::runtime_error("'" + std::to_string(std::underlying_type_t<E>(v)) + "'"
                                 + " is not of type '"
                                 + std::string(typeName(boost::hana::type_c<E>)) + "'") {
    }
};

} // namespace yenxo

// Enum init
// Given a tuple (x) || (x,) || (x,1,) || (x,1,"x") || (x,,"x") || (x,,)
// produces       x  ||  x   ||  x = 1 ||  x = 1    || x        || x
#define YENXO_EQe(...) YENXO_EQe_IMPL(BOOST_HANA_PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define YENXO_EQe_IMPL(N, ...)                                                           \
    BOOST_HANA_PP_CONCAT(YENXO_EQe_IMPL_, N)                                             \
    (__VA_ARGS__)
#define YENXO_EQe_IMPL_1(x) x
#define YENXO_EQe_IMPL_2(x, y) YENXO_EQe_IMPL_2_EMPTY(IS_EMPTY(y), x, y)
#define YENXO_EQe_IMPL_2_EMPTY(_01, x, y)                                                \
    BOOST_HANA_PP_CONCAT(YENXO_EQe_IMPL_2_EMPTY_, _01)                                   \
    (x, y)
#define YENXO_EQe_IMPL_2_EMPTY_0(x, y) x = y
#define YENXO_EQe_IMPL_2_EMPTY_1(x, y) x
#define YENXO_EQe_IMPL_3(x, y, ...) YENXO_EQe_IMPL_2_EMPTY(IS_EMPTY(y), x, y)
#define YENXO_EQe_IMPL_4(x, y, ...) YENXO_EQe_IMPL_2_EMPTY(IS_EMPTY(y), x, y)
#define YENXO_EQe_IMPL_5(x, y, ...) YENXO_EQe_IMPL_2_EMPTY(IS_EMPTY(y), x, y)
#define YENXO_EQe_IMPL_6(x, y, ...) YENXO_EQe_IMPL_2_EMPTY(IS_EMPTY(y), x, y)
#define YENXO_EQe_IMPL_7(x, y, ...) YENXO_EQe_IMPL_2_EMPTY(IS_EMPTY(y), x, y)
#define YENXO_EQe_IMPL_8(x, y, ...) YENXO_EQe_IMPL_2_EMPTY(IS_EMPTY(y), x, y)
#define YENXO_EQe_IMPL_9(x, y, ...) YENXO_EQe_IMPL_2_EMPTY(IS_EMPTY(y), x, y)
#define YENXO_EQe_IMPL_10(x, y, ...) YENXO_EQe_IMPL_2_EMPTY(IS_EMPTY(y), x, y)
#define YENXO_EQe_IMPL_11(x, y, ...) YENXO_EQe_IMPL_2_EMPTY(IS_EMPTY(y), x, y)
#define YENXO_EQe_IMPL_12(x, y, ...) YENXO_EQe_IMPL_2_EMPTY(IS_EMPTY(y), x, y)

// Enum string representation
// Given a tuple (x) || (x,) || (x,1,) || (x,1,"x") || (x,,"x") || (x,,)
// produces      #x  || #x   || #x     || "x"       || "x"      || #x
#define YENXO_STRe(...) YENXO_STRe_IMPL(BOOST_HANA_PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define YENXO_STRe_IMPL(N, ...)                                                          \
    BOOST_HANA_PP_CONCAT(YENXO_STRe_IMPL_, N)                                            \
    (__VA_ARGS__)
#define YENXO_STRe_IMPL_1(x) #x
#define YENXO_STRe_IMPL_2(x, ...) #x
#define YENXO_STRe_IMPL_3(y, z, x) YENXO_STRe_IMPL_3_EMPTY(IS_EMPTY(x), y, x)
#define YENXO_STRe_IMPL_4(y, z, x, ...)                                                  \
    YENXO_STRe_IMPL_3_EMPTY(IS_EMPTY(x), y, x), __VA_ARGS__
#define YENXO_STRe_IMPL_5(y, z, x, ...)                                                  \
    YENXO_STRe_IMPL_3_EMPTY(IS_EMPTY(x), y, x), __VA_ARGS__
#define YENXO_STRe_IMPL_6(y, z, x, ...)                                                  \
    YENXO_STRe_IMPL_3_EMPTY(IS_EMPTY(x), y, x), __VA_ARGS__
#define YENXO_STRe_IMPL_7(y, z, x, ...)                                                  \
    YENXO_STRe_IMPL_3_EMPTY(IS_EMPTY(x), y, x), __VA_ARGS__
#define YENXO_STRe_IMPL_8(y, z, x, ...)                                                  \
    YENXO_STRe_IMPL_3_EMPTY(IS_EMPTY(x), y, x), __VA_ARGS__
#define YENXO_STRe_IMPL_9(y, z, x, ...)                                                  \
    YENXO_STRe_IMPL_3_EMPTY(IS_EMPTY(x), y, x), __VA_ARGS__
#define YENXO_STRe_IMPL_10(y, z, x, ...)                                                 \
    YENXO_STRe_IMPL_3_EMPTY(IS_EMPTY(x), y, x), __VA_ARGS__
#define YENXO_STRe_IMPL_11(y, z, x, ...)                                                 \
    YENXO_STRe_IMPL_3_EMPTY(IS_EMPTY(x), y, x), __VA_ARGS__
#define YENXO_STRe_IMPL_12(y, z, x, ...)                                                 \
    YENXO_STRe_IMPL_3_EMPTY(IS_EMPTY(x), y, x), __VA_ARGS__
#define YENXO_STRe_IMPL_3_EMPTY(_01, x, y)                                               \
    BOOST_HANA_PP_CONCAT(YENXO_STRe_IMPL_3_EMPTY_, _01)                                  \
    (x, y)
#define YENXO_STRe_IMPL_3_EMPTY_0(x, y) y
#define YENXO_STRe_IMPL_3_EMPTY_1(x, y) #x

// Resolve a value entry argument
// If argument is a tuple produces: (x, YENXO_EQe x, YENXO_STRe x) else (x, x, #x)
#define YENXO_RESOLVE_VALUEe(e) YENXO_RESOLVE_VALUEe_IMPL(IS_TUPLE(e), e)
#define YENXO_RESOLVE_VALUEe_IMPL(_01, e)                                                \
    BOOST_HANA_PP_CONCAT(YENXO_RESOLVE_VALUEe_IMPL_, _01)                                \
    (e)
#define YENXO_RESOLVE_VALUEe_IMPL_0(e) (e, e, #e) // not tuple
#define YENXO_RESOLVE_VALUEe_IMPL_1(e)                                                   \
    (BOOST_HANA_PP_FRONT e, YENXO_EQe e, YENXO_STRe e) // tuple

// 3tuple argument extraction
#define YENXO_FIRST3e(x, ...) x
#define YENXO_SECOND3e(x, y, ...) y
#define YENXO_THIRD3e(x, y, ...) BOOST_HANA_PP_FRONT(__VA_ARGS__)
#define YENXO_RESTe(x, y, ...) __VA_ARGS__

/// Generates an enum and `yenxo::EnumTraits` for it
/// \ingroup group-enum
///
/// Example
/// -------
/// @include example/define_enum.cpp
#ifdef YENXO_DOXYGEN_INVOKED
auto YENXO_DEFINE_ENUM(...) = ;
#define DEFINE_STRUCT(Type, ...) see documentation
#else
#define YENXO_DEFINE_ENUM(Type, ...)                                                     \
    YENXO_DEFINE_ENUM_IMPL(BOOST_HANA_PP_NARG(__VA_ARGS__), Type, __VA_ARGS__)
#endif

#define YENXO_DEFINE_ENUM_IMPL(N, Type, ...)                                             \
    BOOST_HANA_PP_CONCAT(YENXO_DEFINE_ENUM_IMPL_, N)                                     \
    (Type, __VA_ARGS__)

#define YENXO_DEFINE_ENUM_IMPL_1(Type, e1)                                               \
    YENXO_DEFINE_ENUM_IMPL_1_(Type, YENXO_RESOLVE_VALUEe(e1))
#define YENXO_DEFINE_ENUM_IMPL_1_(Type, e1)                                              \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1};                                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 1;                              \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1};                                                 \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1));     \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_2(Type, e1, e2)                                           \
    YENXO_DEFINE_ENUM_IMPL_2_(Type, YENXO_RESOLVE_VALUEe(e1), YENXO_RESOLVE_VALUEe(e2))
#define YENXO_DEFINE_ENUM_IMPL_2_(Type, e1, e2)                                          \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1, YENXO_SECOND3e e2};              \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 2;                              \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2};                                                 \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2));     \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_3(Type, e1, e2, e3)                                       \
    YENXO_DEFINE_ENUM_IMPL_3_(Type,                                                      \
                              YENXO_RESOLVE_VALUEe(e1),                                  \
                              YENXO_RESOLVE_VALUEe(e2),                                  \
                              YENXO_RESOLVE_VALUEe(e3))
#define YENXO_DEFINE_ENUM_IMPL_3_(Type, e1, e2, e3)                                      \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1, YENXO_SECOND3e e2, YENXO_SECOND3e e3};                    \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 3;                              \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3};                                                 \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3));     \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_4(Type, e1, e2, e3, e4)                                   \
    YENXO_DEFINE_ENUM_IMPL_4_(Type,                                                      \
                              YENXO_RESOLVE_VALUEe(e1),                                  \
                              YENXO_RESOLVE_VALUEe(e2),                                  \
                              YENXO_RESOLVE_VALUEe(e3),                                  \
                              YENXO_RESOLVE_VALUEe(e4))
#define YENXO_DEFINE_ENUM_IMPL_4_(Type, e1, e2, e3, e4)                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1, YENXO_SECOND3e e2, YENXO_SECOND3e e3, YENXO_SECOND3e e4}; \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 4;                              \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4};                                                 \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4));     \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_5(Type, e1, e2, e3, e4, e5)                               \
    YENXO_DEFINE_ENUM_IMPL_5_(Type,                                                      \
                              YENXO_RESOLVE_VALUEe(e1),                                  \
                              YENXO_RESOLVE_VALUEe(e2),                                  \
                              YENXO_RESOLVE_VALUEe(e3),                                  \
                              YENXO_RESOLVE_VALUEe(e4),                                  \
                              YENXO_RESOLVE_VALUEe(e5))
#define YENXO_DEFINE_ENUM_IMPL_5_(Type, e1, e2, e3, e4, e5)                              \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5};                                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 5;                              \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5};                                                 \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5));     \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_6(Type, e1, e2, e3, e4, e5, e6)                           \
    YENXO_DEFINE_ENUM_IMPL_6_(Type,                                                      \
                              YENXO_RESOLVE_VALUEe(e1),                                  \
                              YENXO_RESOLVE_VALUEe(e2),                                  \
                              YENXO_RESOLVE_VALUEe(e3),                                  \
                              YENXO_RESOLVE_VALUEe(e4),                                  \
                              YENXO_RESOLVE_VALUEe(e5),                                  \
                              YENXO_RESOLVE_VALUEe(e6))
#define YENXO_DEFINE_ENUM_IMPL_6_(Type, e1, e2, e3, e4, e5, e6)                          \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6};                                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 6;                              \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6};                                                 \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6));     \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_7(Type, e1, e2, e3, e4, e5, e6, e7)                       \
    YENXO_DEFINE_ENUM_IMPL_7_(Type,                                                      \
                              YENXO_RESOLVE_VALUEe(e1),                                  \
                              YENXO_RESOLVE_VALUEe(e2),                                  \
                              YENXO_RESOLVE_VALUEe(e3),                                  \
                              YENXO_RESOLVE_VALUEe(e4),                                  \
                              YENXO_RESOLVE_VALUEe(e5),                                  \
                              YENXO_RESOLVE_VALUEe(e6),                                  \
                              YENXO_RESOLVE_VALUEe(e7))
#define YENXO_DEFINE_ENUM_IMPL_7_(Type, e1, e2, e3, e4, e5, e6, e7)                      \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7};                                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 7;                              \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7};                                                 \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7));     \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_8(Type, e1, e2, e3, e4, e5, e6, e7, e8)                   \
    YENXO_DEFINE_ENUM_IMPL_8_(Type,                                                      \
                              YENXO_RESOLVE_VALUEe(e1),                                  \
                              YENXO_RESOLVE_VALUEe(e2),                                  \
                              YENXO_RESOLVE_VALUEe(e3),                                  \
                              YENXO_RESOLVE_VALUEe(e4),                                  \
                              YENXO_RESOLVE_VALUEe(e5),                                  \
                              YENXO_RESOLVE_VALUEe(e6),                                  \
                              YENXO_RESOLVE_VALUEe(e7),                                  \
                              YENXO_RESOLVE_VALUEe(e8))
#define YENXO_DEFINE_ENUM_IMPL_8_(Type, e1, e2, e3, e4, e5, e6, e7, e8)                  \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7,                                  \
                                     YENXO_SECOND3e e8};                                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 8;                              \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7,                                                  \
                Enum::YENXO_FIRST3e e8};                                                 \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8));     \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_9(Type, e1, e2, e3, e4, e5, e6, e7, e8, e9)               \
    YENXO_DEFINE_ENUM_IMPL_9_(Type,                                                      \
                              YENXO_RESOLVE_VALUEe(e1),                                  \
                              YENXO_RESOLVE_VALUEe(e2),                                  \
                              YENXO_RESOLVE_VALUEe(e3),                                  \
                              YENXO_RESOLVE_VALUEe(e4),                                  \
                              YENXO_RESOLVE_VALUEe(e5),                                  \
                              YENXO_RESOLVE_VALUEe(e6),                                  \
                              YENXO_RESOLVE_VALUEe(e7),                                  \
                              YENXO_RESOLVE_VALUEe(e8),                                  \
                              YENXO_RESOLVE_VALUEe(e9))
#define YENXO_DEFINE_ENUM_IMPL_9_(Type, e1, e2, e3, e4, e5, e6, e7, e8, e9)              \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7,                                  \
                                     YENXO_SECOND3e e8,                                  \
                                     YENXO_SECOND3e e9};                                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 9;                              \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7,                                                  \
                Enum::YENXO_FIRST3e e8,                                                  \
                Enum::YENXO_FIRST3e e9};                                                 \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9));     \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_10(Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10)         \
    YENXO_DEFINE_ENUM_IMPL_10_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10))
#define YENXO_DEFINE_ENUM_IMPL_10_(Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10)        \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7,                                  \
                                     YENXO_SECOND3e e8,                                  \
                                     YENXO_SECOND3e e9,                                  \
                                     YENXO_SECOND3e e10};                                \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 10;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7,                                                  \
                Enum::YENXO_FIRST3e e8,                                                  \
                Enum::YENXO_FIRST3e e9,                                                  \
                Enum::YENXO_FIRST3e e10};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_11(Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11)    \
    YENXO_DEFINE_ENUM_IMPL_11_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11))
#define YENXO_DEFINE_ENUM_IMPL_11_(Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11)   \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7,                                  \
                                     YENXO_SECOND3e e8,                                  \
                                     YENXO_SECOND3e e9,                                  \
                                     YENXO_SECOND3e e10,                                 \
                                     YENXO_SECOND3e e11};                                \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 11;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7,                                                  \
                Enum::YENXO_FIRST3e e8,                                                  \
                Enum::YENXO_FIRST3e e9,                                                  \
                Enum::YENXO_FIRST3e e10,                                                 \
                Enum::YENXO_FIRST3e e11};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_12(                                                       \
        Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12)                         \
    YENXO_DEFINE_ENUM_IMPL_12_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12))
#define YENXO_DEFINE_ENUM_IMPL_12_(                                                      \
        Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12)                         \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7,                                  \
                                     YENXO_SECOND3e e8,                                  \
                                     YENXO_SECOND3e e9,                                  \
                                     YENXO_SECOND3e e10,                                 \
                                     YENXO_SECOND3e e11,                                 \
                                     YENXO_SECOND3e e12};                                \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 12;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7,                                                  \
                Enum::YENXO_FIRST3e e8,                                                  \
                Enum::YENXO_FIRST3e e9,                                                  \
                Enum::YENXO_FIRST3e e10,                                                 \
                Enum::YENXO_FIRST3e e11,                                                 \
                Enum::YENXO_FIRST3e e12};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_13(                                                       \
        Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13)                    \
    YENXO_DEFINE_ENUM_IMPL_13_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13))
#define YENXO_DEFINE_ENUM_IMPL_13_(                                                      \
        Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13)                    \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7,                                  \
                                     YENXO_SECOND3e e8,                                  \
                                     YENXO_SECOND3e e9,                                  \
                                     YENXO_SECOND3e e10,                                 \
                                     YENXO_SECOND3e e11,                                 \
                                     YENXO_SECOND3e e12,                                 \
                                     YENXO_SECOND3e e13};                                \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 13;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7,                                                  \
                Enum::YENXO_FIRST3e e8,                                                  \
                Enum::YENXO_FIRST3e e9,                                                  \
                Enum::YENXO_FIRST3e e10,                                                 \
                Enum::YENXO_FIRST3e e11,                                                 \
                Enum::YENXO_FIRST3e e12,                                                 \
                Enum::YENXO_FIRST3e e13};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_14(                                                       \
        Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14)               \
    YENXO_DEFINE_ENUM_IMPL_14_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14))
#define YENXO_DEFINE_ENUM_IMPL_14_(                                                      \
        Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14)               \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7,                                  \
                                     YENXO_SECOND3e e8,                                  \
                                     YENXO_SECOND3e e9,                                  \
                                     YENXO_SECOND3e e10,                                 \
                                     YENXO_SECOND3e e11,                                 \
                                     YENXO_SECOND3e e12,                                 \
                                     YENXO_SECOND3e e13,                                 \
                                     YENXO_SECOND3e e14};                                \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 14;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7,                                                  \
                Enum::YENXO_FIRST3e e8,                                                  \
                Enum::YENXO_FIRST3e e9,                                                  \
                Enum::YENXO_FIRST3e e10,                                                 \
                Enum::YENXO_FIRST3e e11,                                                 \
                Enum::YENXO_FIRST3e e12,                                                 \
                Enum::YENXO_FIRST3e e13,                                                 \
                Enum::YENXO_FIRST3e e14};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_15(                                                       \
        Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15)          \
    YENXO_DEFINE_ENUM_IMPL_15_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15))
#define YENXO_DEFINE_ENUM_IMPL_15_(                                                      \
        Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15)          \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7,                                  \
                                     YENXO_SECOND3e e8,                                  \
                                     YENXO_SECOND3e e9,                                  \
                                     YENXO_SECOND3e e10,                                 \
                                     YENXO_SECOND3e e11,                                 \
                                     YENXO_SECOND3e e12,                                 \
                                     YENXO_SECOND3e e13,                                 \
                                     YENXO_SECOND3e e14,                                 \
                                     YENXO_SECOND3e e15};                                \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 15;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7,                                                  \
                Enum::YENXO_FIRST3e e8,                                                  \
                Enum::YENXO_FIRST3e e9,                                                  \
                Enum::YENXO_FIRST3e e10,                                                 \
                Enum::YENXO_FIRST3e e11,                                                 \
                Enum::YENXO_FIRST3e e12,                                                 \
                Enum::YENXO_FIRST3e e13,                                                 \
                Enum::YENXO_FIRST3e e14,                                                 \
                Enum::YENXO_FIRST3e e15};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_16(                                                       \
        Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16)     \
    YENXO_DEFINE_ENUM_IMPL_16_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16))
#define YENXO_DEFINE_ENUM_IMPL_16_(                                                      \
        Type, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16)     \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7,                                  \
                                     YENXO_SECOND3e e8,                                  \
                                     YENXO_SECOND3e e9,                                  \
                                     YENXO_SECOND3e e10,                                 \
                                     YENXO_SECOND3e e11,                                 \
                                     YENXO_SECOND3e e12,                                 \
                                     YENXO_SECOND3e e13,                                 \
                                     YENXO_SECOND3e e14,                                 \
                                     YENXO_SECOND3e e15,                                 \
                                     YENXO_SECOND3e e16};                                \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 16;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7,                                                  \
                Enum::YENXO_FIRST3e e8,                                                  \
                Enum::YENXO_FIRST3e e9,                                                  \
                Enum::YENXO_FIRST3e e10,                                                 \
                Enum::YENXO_FIRST3e e11,                                                 \
                Enum::YENXO_FIRST3e e12,                                                 \
                Enum::YENXO_FIRST3e e13,                                                 \
                Enum::YENXO_FIRST3e e14,                                                 \
                Enum::YENXO_FIRST3e e15,                                                 \
                Enum::YENXO_FIRST3e e16};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_17(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17)                                                   \
    YENXO_DEFINE_ENUM_IMPL_17_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17))
#define YENXO_DEFINE_ENUM_IMPL_17_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17)                                                  \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7,                                  \
                                     YENXO_SECOND3e e8,                                  \
                                     YENXO_SECOND3e e9,                                  \
                                     YENXO_SECOND3e e10,                                 \
                                     YENXO_SECOND3e e11,                                 \
                                     YENXO_SECOND3e e12,                                 \
                                     YENXO_SECOND3e e13,                                 \
                                     YENXO_SECOND3e e14,                                 \
                                     YENXO_SECOND3e e15,                                 \
                                     YENXO_SECOND3e e16,                                 \
                                     YENXO_SECOND3e e17};                                \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 17;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7,                                                  \
                Enum::YENXO_FIRST3e e8,                                                  \
                Enum::YENXO_FIRST3e e9,                                                  \
                Enum::YENXO_FIRST3e e10,                                                 \
                Enum::YENXO_FIRST3e e11,                                                 \
                Enum::YENXO_FIRST3e e12,                                                 \
                Enum::YENXO_FIRST3e e13,                                                 \
                Enum::YENXO_FIRST3e e14,                                                 \
                Enum::YENXO_FIRST3e e15,                                                 \
                Enum::YENXO_FIRST3e e16,                                                 \
                Enum::YENXO_FIRST3e e17};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_18(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18)                                                   \
    YENXO_DEFINE_ENUM_IMPL_18_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18))
#define YENXO_DEFINE_ENUM_IMPL_18_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18)                                                  \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7,                                  \
                                     YENXO_SECOND3e e8,                                  \
                                     YENXO_SECOND3e e9,                                  \
                                     YENXO_SECOND3e e10,                                 \
                                     YENXO_SECOND3e e11,                                 \
                                     YENXO_SECOND3e e12,                                 \
                                     YENXO_SECOND3e e13,                                 \
                                     YENXO_SECOND3e e14,                                 \
                                     YENXO_SECOND3e e15,                                 \
                                     YENXO_SECOND3e e16,                                 \
                                     YENXO_SECOND3e e17,                                 \
                                     YENXO_SECOND3e e18};                                \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 18;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7,                                                  \
                Enum::YENXO_FIRST3e e8,                                                  \
                Enum::YENXO_FIRST3e e9,                                                  \
                Enum::YENXO_FIRST3e e10,                                                 \
                Enum::YENXO_FIRST3e e11,                                                 \
                Enum::YENXO_FIRST3e e12,                                                 \
                Enum::YENXO_FIRST3e e13,                                                 \
                Enum::YENXO_FIRST3e e14,                                                 \
                Enum::YENXO_FIRST3e e15,                                                 \
                Enum::YENXO_FIRST3e e16,                                                 \
                Enum::YENXO_FIRST3e e17,                                                 \
                Enum::YENXO_FIRST3e e18};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_19(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19)                                                   \
    YENXO_DEFINE_ENUM_IMPL_19_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19))
#define YENXO_DEFINE_ENUM_IMPL_19_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19)                                                  \
    enum class [[maybe_unused]] Type{YENXO_SECOND3e e1,                                  \
                                     YENXO_SECOND3e e2,                                  \
                                     YENXO_SECOND3e e3,                                  \
                                     YENXO_SECOND3e e4,                                  \
                                     YENXO_SECOND3e e5,                                  \
                                     YENXO_SECOND3e e6,                                  \
                                     YENXO_SECOND3e e7,                                  \
                                     YENXO_SECOND3e e8,                                  \
                                     YENXO_SECOND3e e9,                                  \
                                     YENXO_SECOND3e e10,                                 \
                                     YENXO_SECOND3e e11,                                 \
                                     YENXO_SECOND3e e12,                                 \
                                     YENXO_SECOND3e e13,                                 \
                                     YENXO_SECOND3e e14,                                 \
                                     YENXO_SECOND3e e15,                                 \
                                     YENXO_SECOND3e e16,                                 \
                                     YENXO_SECOND3e e17,                                 \
                                     YENXO_SECOND3e e18,                                 \
                                     YENXO_SECOND3e e19};                                \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 19;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,                                                  \
                Enum::YENXO_FIRST3e e2,                                                  \
                Enum::YENXO_FIRST3e e3,                                                  \
                Enum::YENXO_FIRST3e e4,                                                  \
                Enum::YENXO_FIRST3e e5,                                                  \
                Enum::YENXO_FIRST3e e6,                                                  \
                Enum::YENXO_FIRST3e e7,                                                  \
                Enum::YENXO_FIRST3e e8,                                                  \
                Enum::YENXO_FIRST3e e9,                                                  \
                Enum::YENXO_FIRST3e e10,                                                 \
                Enum::YENXO_FIRST3e e11,                                                 \
                Enum::YENXO_FIRST3e e12,                                                 \
                Enum::YENXO_FIRST3e e13,                                                 \
                Enum::YENXO_FIRST3e e14,                                                 \
                Enum::YENXO_FIRST3e e15,                                                 \
                Enum::YENXO_FIRST3e e16,                                                 \
                Enum::YENXO_FIRST3e e17,                                                 \
                Enum::YENXO_FIRST3e e18,                                                 \
                Enum::YENXO_FIRST3e e19};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_20(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20)                                                   \
    YENXO_DEFINE_ENUM_IMPL_20_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20))
#define YENXO_DEFINE_ENUM_IMPL_20_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20};                                     \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 20;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20};                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_21(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21)                                                   \
    YENXO_DEFINE_ENUM_IMPL_21_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21))
#define YENXO_DEFINE_ENUM_IMPL_21_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21};                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 21;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                         \
                Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                         \
                Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                         \
                Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                         \
                Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                        \
                Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                        \
                Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                        \
                Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                        \
                Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                        \
                Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                        \
                Enum::YENXO_FIRST3e e21};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_22(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22)                                                   \
    YENXO_DEFINE_ENUM_IMPL_22_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22))
#define YENXO_DEFINE_ENUM_IMPL_22_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22};                                                         \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 22;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22};                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_23(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23)                                                   \
    YENXO_DEFINE_ENUM_IMPL_23_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23))
#define YENXO_DEFINE_ENUM_IMPL_23_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23};                                     \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 23;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                 \
                       Enum::YENXO_FIRST3e e23};                                         \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_24(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24)                                                   \
    YENXO_DEFINE_ENUM_IMPL_24_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24))
#define YENXO_DEFINE_ENUM_IMPL_24_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24};                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 24;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                         \
                Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                         \
                Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                         \
                Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                         \
                Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                        \
                Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                        \
                Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                        \
                Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                        \
                Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                        \
                Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                        \
                Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                        \
                Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24};                       \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_25(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25)                                                   \
    YENXO_DEFINE_ENUM_IMPL_25_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25))
#define YENXO_DEFINE_ENUM_IMPL_25_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25};                                                         \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 25;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                 \
                       Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                 \
                       Enum::YENXO_FIRST3e e25};                                         \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_26(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26)                                                   \
    YENXO_DEFINE_ENUM_IMPL_26_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26))
#define YENXO_DEFINE_ENUM_IMPL_26_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26};                                     \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 26;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                 \
                       Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                 \
                       Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26};                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_27(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27)                                                   \
    YENXO_DEFINE_ENUM_IMPL_27_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27))
#define YENXO_DEFINE_ENUM_IMPL_27_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27};                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 27;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                         \
                Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                         \
                Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                         \
                Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                         \
                Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                        \
                Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                        \
                Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                        \
                Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                        \
                Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                        \
                Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                        \
                Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                        \
                Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                        \
                Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                        \
                Enum::YENXO_FIRST3e e27};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_28(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28)                                                   \
    YENXO_DEFINE_ENUM_IMPL_28_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28))
#define YENXO_DEFINE_ENUM_IMPL_28_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28};                                                         \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 28;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                 \
                       Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                 \
                       Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                 \
                       Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28};                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_29(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28,                                                   \
                                  e29)                                                   \
    YENXO_DEFINE_ENUM_IMPL_29_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28),                                \
                               YENXO_RESOLVE_VALUEe(e29))
#define YENXO_DEFINE_ENUM_IMPL_29_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28,                                                  \
                                   e29)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28, YENXO_SECOND3e e29};                                     \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 29;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                 \
                       Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                 \
                       Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                 \
                       Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28,                 \
                       Enum::YENXO_FIRST3e e29};                                         \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28),     \
                                           boost::hana::make_tuple(YENXO_RESTe e29));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            case Enum::YENXO_FIRST3e e29:                                                \
                return YENXO_THIRD3e e29;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_30(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28,                                                   \
                                  e29,                                                   \
                                  e30)                                                   \
    YENXO_DEFINE_ENUM_IMPL_30_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28),                                \
                               YENXO_RESOLVE_VALUEe(e29),                                \
                               YENXO_RESOLVE_VALUEe(e30))
#define YENXO_DEFINE_ENUM_IMPL_30_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28,                                                  \
                                   e29,                                                  \
                                   e30)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28, YENXO_SECOND3e e29, YENXO_SECOND3e e30};                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 30;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                         \
                Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                         \
                Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                         \
                Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                         \
                Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                        \
                Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                        \
                Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                        \
                Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                        \
                Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                        \
                Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                        \
                Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                        \
                Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                        \
                Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                        \
                Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28,                        \
                Enum::YENXO_FIRST3e e29, Enum::YENXO_FIRST3e e30};                       \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28),     \
                                           boost::hana::make_tuple(YENXO_RESTe e29),     \
                                           boost::hana::make_tuple(YENXO_RESTe e30));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            case Enum::YENXO_FIRST3e e29:                                                \
                return YENXO_THIRD3e e29;                                                \
            case Enum::YENXO_FIRST3e e30:                                                \
                return YENXO_THIRD3e e30;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_31(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28,                                                   \
                                  e29,                                                   \
                                  e30,                                                   \
                                  e31)                                                   \
    YENXO_DEFINE_ENUM_IMPL_31_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28),                                \
                               YENXO_RESOLVE_VALUEe(e29),                                \
                               YENXO_RESOLVE_VALUEe(e30),                                \
                               YENXO_RESOLVE_VALUEe(e31))
#define YENXO_DEFINE_ENUM_IMPL_31_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28,                                                  \
                                   e29,                                                  \
                                   e30,                                                  \
                                   e31)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28, YENXO_SECOND3e e29, YENXO_SECOND3e e30,                  \
            YENXO_SECOND3e e31};                                                         \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 31;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                 \
                       Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                 \
                       Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                 \
                       Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28,                 \
                       Enum::YENXO_FIRST3e e29, Enum::YENXO_FIRST3e e30,                 \
                       Enum::YENXO_FIRST3e e31};                                         \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28),     \
                                           boost::hana::make_tuple(YENXO_RESTe e29),     \
                                           boost::hana::make_tuple(YENXO_RESTe e30),     \
                                           boost::hana::make_tuple(YENXO_RESTe e31));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            case Enum::YENXO_FIRST3e e29:                                                \
                return YENXO_THIRD3e e29;                                                \
            case Enum::YENXO_FIRST3e e30:                                                \
                return YENXO_THIRD3e e30;                                                \
            case Enum::YENXO_FIRST3e e31:                                                \
                return YENXO_THIRD3e e31;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_32(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28,                                                   \
                                  e29,                                                   \
                                  e30,                                                   \
                                  e31,                                                   \
                                  e32)                                                   \
    YENXO_DEFINE_ENUM_IMPL_32_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28),                                \
                               YENXO_RESOLVE_VALUEe(e29),                                \
                               YENXO_RESOLVE_VALUEe(e30),                                \
                               YENXO_RESOLVE_VALUEe(e31),                                \
                               YENXO_RESOLVE_VALUEe(e32))
#define YENXO_DEFINE_ENUM_IMPL_32_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28,                                                  \
                                   e29,                                                  \
                                   e30,                                                  \
                                   e31,                                                  \
                                   e32)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28, YENXO_SECOND3e e29, YENXO_SECOND3e e30,                  \
            YENXO_SECOND3e e31, YENXO_SECOND3e e32};                                     \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 32;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                 \
                       Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                 \
                       Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                 \
                       Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28,                 \
                       Enum::YENXO_FIRST3e e29, Enum::YENXO_FIRST3e e30,                 \
                       Enum::YENXO_FIRST3e e31, Enum::YENXO_FIRST3e e32};                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28),     \
                                           boost::hana::make_tuple(YENXO_RESTe e29),     \
                                           boost::hana::make_tuple(YENXO_RESTe e30),     \
                                           boost::hana::make_tuple(YENXO_RESTe e31),     \
                                           boost::hana::make_tuple(YENXO_RESTe e32));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            case Enum::YENXO_FIRST3e e29:                                                \
                return YENXO_THIRD3e e29;                                                \
            case Enum::YENXO_FIRST3e e30:                                                \
                return YENXO_THIRD3e e30;                                                \
            case Enum::YENXO_FIRST3e e31:                                                \
                return YENXO_THIRD3e e31;                                                \
            case Enum::YENXO_FIRST3e e32:                                                \
                return YENXO_THIRD3e e32;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_33(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28,                                                   \
                                  e29,                                                   \
                                  e30,                                                   \
                                  e31,                                                   \
                                  e32,                                                   \
                                  e33)                                                   \
    YENXO_DEFINE_ENUM_IMPL_33_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28),                                \
                               YENXO_RESOLVE_VALUEe(e29),                                \
                               YENXO_RESOLVE_VALUEe(e30),                                \
                               YENXO_RESOLVE_VALUEe(e31),                                \
                               YENXO_RESOLVE_VALUEe(e32),                                \
                               YENXO_RESOLVE_VALUEe(e33))
#define YENXO_DEFINE_ENUM_IMPL_33_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28,                                                  \
                                   e29,                                                  \
                                   e30,                                                  \
                                   e31,                                                  \
                                   e32,                                                  \
                                   e33)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28, YENXO_SECOND3e e29, YENXO_SECOND3e e30,                  \
            YENXO_SECOND3e e31, YENXO_SECOND3e e32, YENXO_SECOND3e e33};                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 33;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                         \
                Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                         \
                Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                         \
                Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                         \
                Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                        \
                Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                        \
                Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                        \
                Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                        \
                Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                        \
                Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                        \
                Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                        \
                Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                        \
                Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                        \
                Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28,                        \
                Enum::YENXO_FIRST3e e29, Enum::YENXO_FIRST3e e30,                        \
                Enum::YENXO_FIRST3e e31, Enum::YENXO_FIRST3e e32,                        \
                Enum::YENXO_FIRST3e e33};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28),     \
                                           boost::hana::make_tuple(YENXO_RESTe e29),     \
                                           boost::hana::make_tuple(YENXO_RESTe e30),     \
                                           boost::hana::make_tuple(YENXO_RESTe e31),     \
                                           boost::hana::make_tuple(YENXO_RESTe e32),     \
                                           boost::hana::make_tuple(YENXO_RESTe e33));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            case Enum::YENXO_FIRST3e e29:                                                \
                return YENXO_THIRD3e e29;                                                \
            case Enum::YENXO_FIRST3e e30:                                                \
                return YENXO_THIRD3e e30;                                                \
            case Enum::YENXO_FIRST3e e31:                                                \
                return YENXO_THIRD3e e31;                                                \
            case Enum::YENXO_FIRST3e e32:                                                \
                return YENXO_THIRD3e e32;                                                \
            case Enum::YENXO_FIRST3e e33:                                                \
                return YENXO_THIRD3e e33;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_34(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28,                                                   \
                                  e29,                                                   \
                                  e30,                                                   \
                                  e31,                                                   \
                                  e32,                                                   \
                                  e33,                                                   \
                                  e34)                                                   \
    YENXO_DEFINE_ENUM_IMPL_34_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28),                                \
                               YENXO_RESOLVE_VALUEe(e29),                                \
                               YENXO_RESOLVE_VALUEe(e30),                                \
                               YENXO_RESOLVE_VALUEe(e31),                                \
                               YENXO_RESOLVE_VALUEe(e32),                                \
                               YENXO_RESOLVE_VALUEe(e33),                                \
                               YENXO_RESOLVE_VALUEe(e34))
#define YENXO_DEFINE_ENUM_IMPL_34_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28,                                                  \
                                   e29,                                                  \
                                   e30,                                                  \
                                   e31,                                                  \
                                   e32,                                                  \
                                   e33,                                                  \
                                   e34)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28, YENXO_SECOND3e e29, YENXO_SECOND3e e30,                  \
            YENXO_SECOND3e e31, YENXO_SECOND3e e32, YENXO_SECOND3e e33,                  \
            YENXO_SECOND3e e34};                                                         \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 34;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                 \
                       Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                 \
                       Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                 \
                       Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28,                 \
                       Enum::YENXO_FIRST3e e29, Enum::YENXO_FIRST3e e30,                 \
                       Enum::YENXO_FIRST3e e31, Enum::YENXO_FIRST3e e32,                 \
                       Enum::YENXO_FIRST3e e33, Enum::YENXO_FIRST3e e34};                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28),     \
                                           boost::hana::make_tuple(YENXO_RESTe e29),     \
                                           boost::hana::make_tuple(YENXO_RESTe e30),     \
                                           boost::hana::make_tuple(YENXO_RESTe e31),     \
                                           boost::hana::make_tuple(YENXO_RESTe e32),     \
                                           boost::hana::make_tuple(YENXO_RESTe e33),     \
                                           boost::hana::make_tuple(YENXO_RESTe e34));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            case Enum::YENXO_FIRST3e e29:                                                \
                return YENXO_THIRD3e e29;                                                \
            case Enum::YENXO_FIRST3e e30:                                                \
                return YENXO_THIRD3e e30;                                                \
            case Enum::YENXO_FIRST3e e31:                                                \
                return YENXO_THIRD3e e31;                                                \
            case Enum::YENXO_FIRST3e e32:                                                \
                return YENXO_THIRD3e e32;                                                \
            case Enum::YENXO_FIRST3e e33:                                                \
                return YENXO_THIRD3e e33;                                                \
            case Enum::YENXO_FIRST3e e34:                                                \
                return YENXO_THIRD3e e34;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_35(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28,                                                   \
                                  e29,                                                   \
                                  e30,                                                   \
                                  e31,                                                   \
                                  e32,                                                   \
                                  e33,                                                   \
                                  e34,                                                   \
                                  e35)                                                   \
    YENXO_DEFINE_ENUM_IMPL_35_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28),                                \
                               YENXO_RESOLVE_VALUEe(e29),                                \
                               YENXO_RESOLVE_VALUEe(e30),                                \
                               YENXO_RESOLVE_VALUEe(e31),                                \
                               YENXO_RESOLVE_VALUEe(e32),                                \
                               YENXO_RESOLVE_VALUEe(e33),                                \
                               YENXO_RESOLVE_VALUEe(e34),                                \
                               YENXO_RESOLVE_VALUEe(e35))
#define YENXO_DEFINE_ENUM_IMPL_35_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28,                                                  \
                                   e29,                                                  \
                                   e30,                                                  \
                                   e31,                                                  \
                                   e32,                                                  \
                                   e33,                                                  \
                                   e34,                                                  \
                                   e35)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28, YENXO_SECOND3e e29, YENXO_SECOND3e e30,                  \
            YENXO_SECOND3e e31, YENXO_SECOND3e e32, YENXO_SECOND3e e33,                  \
            YENXO_SECOND3e e34, YENXO_SECOND3e e35};                                     \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 35;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                 \
                       Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                 \
                       Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                 \
                       Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28,                 \
                       Enum::YENXO_FIRST3e e29, Enum::YENXO_FIRST3e e30,                 \
                       Enum::YENXO_FIRST3e e31, Enum::YENXO_FIRST3e e32,                 \
                       Enum::YENXO_FIRST3e e33, Enum::YENXO_FIRST3e e34,                 \
                       Enum::YENXO_FIRST3e e35};                                         \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28),     \
                                           boost::hana::make_tuple(YENXO_RESTe e29),     \
                                           boost::hana::make_tuple(YENXO_RESTe e30),     \
                                           boost::hana::make_tuple(YENXO_RESTe e31),     \
                                           boost::hana::make_tuple(YENXO_RESTe e32),     \
                                           boost::hana::make_tuple(YENXO_RESTe e33),     \
                                           boost::hana::make_tuple(YENXO_RESTe e34),     \
                                           boost::hana::make_tuple(YENXO_RESTe e35));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            case Enum::YENXO_FIRST3e e29:                                                \
                return YENXO_THIRD3e e29;                                                \
            case Enum::YENXO_FIRST3e e30:                                                \
                return YENXO_THIRD3e e30;                                                \
            case Enum::YENXO_FIRST3e e31:                                                \
                return YENXO_THIRD3e e31;                                                \
            case Enum::YENXO_FIRST3e e32:                                                \
                return YENXO_THIRD3e e32;                                                \
            case Enum::YENXO_FIRST3e e33:                                                \
                return YENXO_THIRD3e e33;                                                \
            case Enum::YENXO_FIRST3e e34:                                                \
                return YENXO_THIRD3e e34;                                                \
            case Enum::YENXO_FIRST3e e35:                                                \
                return YENXO_THIRD3e e35;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_36(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28,                                                   \
                                  e29,                                                   \
                                  e30,                                                   \
                                  e31,                                                   \
                                  e32,                                                   \
                                  e33,                                                   \
                                  e34,                                                   \
                                  e35,                                                   \
                                  e36)                                                   \
    YENXO_DEFINE_ENUM_IMPL_36_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28),                                \
                               YENXO_RESOLVE_VALUEe(e29),                                \
                               YENXO_RESOLVE_VALUEe(e30),                                \
                               YENXO_RESOLVE_VALUEe(e31),                                \
                               YENXO_RESOLVE_VALUEe(e32),                                \
                               YENXO_RESOLVE_VALUEe(e33),                                \
                               YENXO_RESOLVE_VALUEe(e34),                                \
                               YENXO_RESOLVE_VALUEe(e35),                                \
                               YENXO_RESOLVE_VALUEe(e36))
#define YENXO_DEFINE_ENUM_IMPL_36_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28,                                                  \
                                   e29,                                                  \
                                   e30,                                                  \
                                   e31,                                                  \
                                   e32,                                                  \
                                   e33,                                                  \
                                   e34,                                                  \
                                   e35,                                                  \
                                   e36)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28, YENXO_SECOND3e e29, YENXO_SECOND3e e30,                  \
            YENXO_SECOND3e e31, YENXO_SECOND3e e32, YENXO_SECOND3e e33,                  \
            YENXO_SECOND3e e34, YENXO_SECOND3e e35, YENXO_SECOND3e e36};                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 36;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                         \
                Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                         \
                Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                         \
                Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                         \
                Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                        \
                Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                        \
                Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                        \
                Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                        \
                Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                        \
                Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                        \
                Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                        \
                Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                        \
                Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                        \
                Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28,                        \
                Enum::YENXO_FIRST3e e29, Enum::YENXO_FIRST3e e30,                        \
                Enum::YENXO_FIRST3e e31, Enum::YENXO_FIRST3e e32,                        \
                Enum::YENXO_FIRST3e e33, Enum::YENXO_FIRST3e e34,                        \
                Enum::YENXO_FIRST3e e35, Enum::YENXO_FIRST3e e36};                       \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28),     \
                                           boost::hana::make_tuple(YENXO_RESTe e29),     \
                                           boost::hana::make_tuple(YENXO_RESTe e30),     \
                                           boost::hana::make_tuple(YENXO_RESTe e31),     \
                                           boost::hana::make_tuple(YENXO_RESTe e32),     \
                                           boost::hana::make_tuple(YENXO_RESTe e33),     \
                                           boost::hana::make_tuple(YENXO_RESTe e34),     \
                                           boost::hana::make_tuple(YENXO_RESTe e35),     \
                                           boost::hana::make_tuple(YENXO_RESTe e36));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            case Enum::YENXO_FIRST3e e29:                                                \
                return YENXO_THIRD3e e29;                                                \
            case Enum::YENXO_FIRST3e e30:                                                \
                return YENXO_THIRD3e e30;                                                \
            case Enum::YENXO_FIRST3e e31:                                                \
                return YENXO_THIRD3e e31;                                                \
            case Enum::YENXO_FIRST3e e32:                                                \
                return YENXO_THIRD3e e32;                                                \
            case Enum::YENXO_FIRST3e e33:                                                \
                return YENXO_THIRD3e e33;                                                \
            case Enum::YENXO_FIRST3e e34:                                                \
                return YENXO_THIRD3e e34;                                                \
            case Enum::YENXO_FIRST3e e35:                                                \
                return YENXO_THIRD3e e35;                                                \
            case Enum::YENXO_FIRST3e e36:                                                \
                return YENXO_THIRD3e e36;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_37(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28,                                                   \
                                  e29,                                                   \
                                  e30,                                                   \
                                  e31,                                                   \
                                  e32,                                                   \
                                  e33,                                                   \
                                  e34,                                                   \
                                  e35,                                                   \
                                  e36,                                                   \
                                  e37)                                                   \
    YENXO_DEFINE_ENUM_IMPL_37_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28),                                \
                               YENXO_RESOLVE_VALUEe(e29),                                \
                               YENXO_RESOLVE_VALUEe(e30),                                \
                               YENXO_RESOLVE_VALUEe(e31),                                \
                               YENXO_RESOLVE_VALUEe(e32),                                \
                               YENXO_RESOLVE_VALUEe(e33),                                \
                               YENXO_RESOLVE_VALUEe(e34),                                \
                               YENXO_RESOLVE_VALUEe(e35),                                \
                               YENXO_RESOLVE_VALUEe(e36),                                \
                               YENXO_RESOLVE_VALUEe(e37))
#define YENXO_DEFINE_ENUM_IMPL_37_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28,                                                  \
                                   e29,                                                  \
                                   e30,                                                  \
                                   e31,                                                  \
                                   e32,                                                  \
                                   e33,                                                  \
                                   e34,                                                  \
                                   e35,                                                  \
                                   e36,                                                  \
                                   e37)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28, YENXO_SECOND3e e29, YENXO_SECOND3e e30,                  \
            YENXO_SECOND3e e31, YENXO_SECOND3e e32, YENXO_SECOND3e e33,                  \
            YENXO_SECOND3e e34, YENXO_SECOND3e e35, YENXO_SECOND3e e36,                  \
            YENXO_SECOND3e e37};                                                         \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 37;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                 \
                       Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                 \
                       Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                 \
                       Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28,                 \
                       Enum::YENXO_FIRST3e e29, Enum::YENXO_FIRST3e e30,                 \
                       Enum::YENXO_FIRST3e e31, Enum::YENXO_FIRST3e e32,                 \
                       Enum::YENXO_FIRST3e e33, Enum::YENXO_FIRST3e e34,                 \
                       Enum::YENXO_FIRST3e e35, Enum::YENXO_FIRST3e e36,                 \
                       Enum::YENXO_FIRST3e e37};                                         \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28),     \
                                           boost::hana::make_tuple(YENXO_RESTe e29),     \
                                           boost::hana::make_tuple(YENXO_RESTe e30),     \
                                           boost::hana::make_tuple(YENXO_RESTe e31),     \
                                           boost::hana::make_tuple(YENXO_RESTe e32),     \
                                           boost::hana::make_tuple(YENXO_RESTe e33),     \
                                           boost::hana::make_tuple(YENXO_RESTe e34),     \
                                           boost::hana::make_tuple(YENXO_RESTe e35),     \
                                           boost::hana::make_tuple(YENXO_RESTe e36),     \
                                           boost::hana::make_tuple(YENXO_RESTe e37));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            case Enum::YENXO_FIRST3e e29:                                                \
                return YENXO_THIRD3e e29;                                                \
            case Enum::YENXO_FIRST3e e30:                                                \
                return YENXO_THIRD3e e30;                                                \
            case Enum::YENXO_FIRST3e e31:                                                \
                return YENXO_THIRD3e e31;                                                \
            case Enum::YENXO_FIRST3e e32:                                                \
                return YENXO_THIRD3e e32;                                                \
            case Enum::YENXO_FIRST3e e33:                                                \
                return YENXO_THIRD3e e33;                                                \
            case Enum::YENXO_FIRST3e e34:                                                \
                return YENXO_THIRD3e e34;                                                \
            case Enum::YENXO_FIRST3e e35:                                                \
                return YENXO_THIRD3e e35;                                                \
            case Enum::YENXO_FIRST3e e36:                                                \
                return YENXO_THIRD3e e36;                                                \
            case Enum::YENXO_FIRST3e e37:                                                \
                return YENXO_THIRD3e e37;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_38(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28,                                                   \
                                  e29,                                                   \
                                  e30,                                                   \
                                  e31,                                                   \
                                  e32,                                                   \
                                  e33,                                                   \
                                  e34,                                                   \
                                  e35,                                                   \
                                  e36,                                                   \
                                  e37,                                                   \
                                  e38)                                                   \
    YENXO_DEFINE_ENUM_IMPL_38_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28),                                \
                               YENXO_RESOLVE_VALUEe(e29),                                \
                               YENXO_RESOLVE_VALUEe(e30),                                \
                               YENXO_RESOLVE_VALUEe(e31),                                \
                               YENXO_RESOLVE_VALUEe(e32),                                \
                               YENXO_RESOLVE_VALUEe(e33),                                \
                               YENXO_RESOLVE_VALUEe(e34),                                \
                               YENXO_RESOLVE_VALUEe(e35),                                \
                               YENXO_RESOLVE_VALUEe(e36),                                \
                               YENXO_RESOLVE_VALUEe(e37),                                \
                               YENXO_RESOLVE_VALUEe(e38))
#define YENXO_DEFINE_ENUM_IMPL_38_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28,                                                  \
                                   e29,                                                  \
                                   e30,                                                  \
                                   e31,                                                  \
                                   e32,                                                  \
                                   e33,                                                  \
                                   e34,                                                  \
                                   e35,                                                  \
                                   e36,                                                  \
                                   e37,                                                  \
                                   e38)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28, YENXO_SECOND3e e29, YENXO_SECOND3e e30,                  \
            YENXO_SECOND3e e31, YENXO_SECOND3e e32, YENXO_SECOND3e e33,                  \
            YENXO_SECOND3e e34, YENXO_SECOND3e e35, YENXO_SECOND3e e36,                  \
            YENXO_SECOND3e e37, YENXO_SECOND3e e38};                                     \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 38;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                 \
                       Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                 \
                       Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                 \
                       Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28,                 \
                       Enum::YENXO_FIRST3e e29, Enum::YENXO_FIRST3e e30,                 \
                       Enum::YENXO_FIRST3e e31, Enum::YENXO_FIRST3e e32,                 \
                       Enum::YENXO_FIRST3e e33, Enum::YENXO_FIRST3e e34,                 \
                       Enum::YENXO_FIRST3e e35, Enum::YENXO_FIRST3e e36,                 \
                       Enum::YENXO_FIRST3e e37, Enum::YENXO_FIRST3e e38};                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28),     \
                                           boost::hana::make_tuple(YENXO_RESTe e29),     \
                                           boost::hana::make_tuple(YENXO_RESTe e30),     \
                                           boost::hana::make_tuple(YENXO_RESTe e31),     \
                                           boost::hana::make_tuple(YENXO_RESTe e32),     \
                                           boost::hana::make_tuple(YENXO_RESTe e33),     \
                                           boost::hana::make_tuple(YENXO_RESTe e34),     \
                                           boost::hana::make_tuple(YENXO_RESTe e35),     \
                                           boost::hana::make_tuple(YENXO_RESTe e36),     \
                                           boost::hana::make_tuple(YENXO_RESTe e37),     \
                                           boost::hana::make_tuple(YENXO_RESTe e38));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            case Enum::YENXO_FIRST3e e29:                                                \
                return YENXO_THIRD3e e29;                                                \
            case Enum::YENXO_FIRST3e e30:                                                \
                return YENXO_THIRD3e e30;                                                \
            case Enum::YENXO_FIRST3e e31:                                                \
                return YENXO_THIRD3e e31;                                                \
            case Enum::YENXO_FIRST3e e32:                                                \
                return YENXO_THIRD3e e32;                                                \
            case Enum::YENXO_FIRST3e e33:                                                \
                return YENXO_THIRD3e e33;                                                \
            case Enum::YENXO_FIRST3e e34:                                                \
                return YENXO_THIRD3e e34;                                                \
            case Enum::YENXO_FIRST3e e35:                                                \
                return YENXO_THIRD3e e35;                                                \
            case Enum::YENXO_FIRST3e e36:                                                \
                return YENXO_THIRD3e e36;                                                \
            case Enum::YENXO_FIRST3e e37:                                                \
                return YENXO_THIRD3e e37;                                                \
            case Enum::YENXO_FIRST3e e38:                                                \
                return YENXO_THIRD3e e38;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_39(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28,                                                   \
                                  e29,                                                   \
                                  e30,                                                   \
                                  e31,                                                   \
                                  e32,                                                   \
                                  e33,                                                   \
                                  e34,                                                   \
                                  e35,                                                   \
                                  e36,                                                   \
                                  e37,                                                   \
                                  e38,                                                   \
                                  e39)                                                   \
    YENXO_DEFINE_ENUM_IMPL_39_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28),                                \
                               YENXO_RESOLVE_VALUEe(e29),                                \
                               YENXO_RESOLVE_VALUEe(e30),                                \
                               YENXO_RESOLVE_VALUEe(e31),                                \
                               YENXO_RESOLVE_VALUEe(e32),                                \
                               YENXO_RESOLVE_VALUEe(e33),                                \
                               YENXO_RESOLVE_VALUEe(e34),                                \
                               YENXO_RESOLVE_VALUEe(e35),                                \
                               YENXO_RESOLVE_VALUEe(e36),                                \
                               YENXO_RESOLVE_VALUEe(e37),                                \
                               YENXO_RESOLVE_VALUEe(e38),                                \
                               YENXO_RESOLVE_VALUEe(e39))
#define YENXO_DEFINE_ENUM_IMPL_39_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28,                                                  \
                                   e29,                                                  \
                                   e30,                                                  \
                                   e31,                                                  \
                                   e32,                                                  \
                                   e33,                                                  \
                                   e34,                                                  \
                                   e35,                                                  \
                                   e36,                                                  \
                                   e37,                                                  \
                                   e38,                                                  \
                                   e39)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28, YENXO_SECOND3e e29, YENXO_SECOND3e e30,                  \
            YENXO_SECOND3e e31, YENXO_SECOND3e e32, YENXO_SECOND3e e33,                  \
            YENXO_SECOND3e e34, YENXO_SECOND3e e35, YENXO_SECOND3e e36,                  \
            YENXO_SECOND3e e37, YENXO_SECOND3e e38, YENXO_SECOND3e e39};                 \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 39;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count> values{                \
                Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                         \
                Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                         \
                Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                         \
                Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                         \
                Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                        \
                Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                        \
                Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                        \
                Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                        \
                Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                        \
                Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                        \
                Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                        \
                Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                        \
                Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                        \
                Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28,                        \
                Enum::YENXO_FIRST3e e29, Enum::YENXO_FIRST3e e30,                        \
                Enum::YENXO_FIRST3e e31, Enum::YENXO_FIRST3e e32,                        \
                Enum::YENXO_FIRST3e e33, Enum::YENXO_FIRST3e e34,                        \
                Enum::YENXO_FIRST3e e35, Enum::YENXO_FIRST3e e36,                        \
                Enum::YENXO_FIRST3e e37, Enum::YENXO_FIRST3e e38,                        \
                Enum::YENXO_FIRST3e e39};                                                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28),     \
                                           boost::hana::make_tuple(YENXO_RESTe e29),     \
                                           boost::hana::make_tuple(YENXO_RESTe e30),     \
                                           boost::hana::make_tuple(YENXO_RESTe e31),     \
                                           boost::hana::make_tuple(YENXO_RESTe e32),     \
                                           boost::hana::make_tuple(YENXO_RESTe e33),     \
                                           boost::hana::make_tuple(YENXO_RESTe e34),     \
                                           boost::hana::make_tuple(YENXO_RESTe e35),     \
                                           boost::hana::make_tuple(YENXO_RESTe e36),     \
                                           boost::hana::make_tuple(YENXO_RESTe e37),     \
                                           boost::hana::make_tuple(YENXO_RESTe e38),     \
                                           boost::hana::make_tuple(YENXO_RESTe e39));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            case Enum::YENXO_FIRST3e e29:                                                \
                return YENXO_THIRD3e e29;                                                \
            case Enum::YENXO_FIRST3e e30:                                                \
                return YENXO_THIRD3e e30;                                                \
            case Enum::YENXO_FIRST3e e31:                                                \
                return YENXO_THIRD3e e31;                                                \
            case Enum::YENXO_FIRST3e e32:                                                \
                return YENXO_THIRD3e e32;                                                \
            case Enum::YENXO_FIRST3e e33:                                                \
                return YENXO_THIRD3e e33;                                                \
            case Enum::YENXO_FIRST3e e34:                                                \
                return YENXO_THIRD3e e34;                                                \
            case Enum::YENXO_FIRST3e e35:                                                \
                return YENXO_THIRD3e e35;                                                \
            case Enum::YENXO_FIRST3e e36:                                                \
                return YENXO_THIRD3e e36;                                                \
            case Enum::YENXO_FIRST3e e37:                                                \
                return YENXO_THIRD3e e37;                                                \
            case Enum::YENXO_FIRST3e e38:                                                \
                return YENXO_THIRD3e e38;                                                \
            case Enum::YENXO_FIRST3e e39:                                                \
                return YENXO_THIRD3e e39;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT

#define YENXO_DEFINE_ENUM_IMPL_40(Type,                                                  \
                                  e1,                                                    \
                                  e2,                                                    \
                                  e3,                                                    \
                                  e4,                                                    \
                                  e5,                                                    \
                                  e6,                                                    \
                                  e7,                                                    \
                                  e8,                                                    \
                                  e9,                                                    \
                                  e10,                                                   \
                                  e11,                                                   \
                                  e12,                                                   \
                                  e13,                                                   \
                                  e14,                                                   \
                                  e15,                                                   \
                                  e16,                                                   \
                                  e17,                                                   \
                                  e18,                                                   \
                                  e19,                                                   \
                                  e20,                                                   \
                                  e21,                                                   \
                                  e22,                                                   \
                                  e23,                                                   \
                                  e24,                                                   \
                                  e25,                                                   \
                                  e26,                                                   \
                                  e27,                                                   \
                                  e28,                                                   \
                                  e29,                                                   \
                                  e30,                                                   \
                                  e31,                                                   \
                                  e32,                                                   \
                                  e33,                                                   \
                                  e34,                                                   \
                                  e35,                                                   \
                                  e36,                                                   \
                                  e37,                                                   \
                                  e38,                                                   \
                                  e39,                                                   \
                                  e40)                                                   \
    YENXO_DEFINE_ENUM_IMPL_40_(Type,                                                     \
                               YENXO_RESOLVE_VALUEe(e1),                                 \
                               YENXO_RESOLVE_VALUEe(e2),                                 \
                               YENXO_RESOLVE_VALUEe(e3),                                 \
                               YENXO_RESOLVE_VALUEe(e4),                                 \
                               YENXO_RESOLVE_VALUEe(e5),                                 \
                               YENXO_RESOLVE_VALUEe(e6),                                 \
                               YENXO_RESOLVE_VALUEe(e7),                                 \
                               YENXO_RESOLVE_VALUEe(e8),                                 \
                               YENXO_RESOLVE_VALUEe(e9),                                 \
                               YENXO_RESOLVE_VALUEe(e10),                                \
                               YENXO_RESOLVE_VALUEe(e11),                                \
                               YENXO_RESOLVE_VALUEe(e12),                                \
                               YENXO_RESOLVE_VALUEe(e13),                                \
                               YENXO_RESOLVE_VALUEe(e14),                                \
                               YENXO_RESOLVE_VALUEe(e15),                                \
                               YENXO_RESOLVE_VALUEe(e16),                                \
                               YENXO_RESOLVE_VALUEe(e17),                                \
                               YENXO_RESOLVE_VALUEe(e18),                                \
                               YENXO_RESOLVE_VALUEe(e19),                                \
                               YENXO_RESOLVE_VALUEe(e20),                                \
                               YENXO_RESOLVE_VALUEe(e21),                                \
                               YENXO_RESOLVE_VALUEe(e22),                                \
                               YENXO_RESOLVE_VALUEe(e23),                                \
                               YENXO_RESOLVE_VALUEe(e24),                                \
                               YENXO_RESOLVE_VALUEe(e25),                                \
                               YENXO_RESOLVE_VALUEe(e26),                                \
                               YENXO_RESOLVE_VALUEe(e27),                                \
                               YENXO_RESOLVE_VALUEe(e28),                                \
                               YENXO_RESOLVE_VALUEe(e29),                                \
                               YENXO_RESOLVE_VALUEe(e30),                                \
                               YENXO_RESOLVE_VALUEe(e31),                                \
                               YENXO_RESOLVE_VALUEe(e32),                                \
                               YENXO_RESOLVE_VALUEe(e33),                                \
                               YENXO_RESOLVE_VALUEe(e34),                                \
                               YENXO_RESOLVE_VALUEe(e35),                                \
                               YENXO_RESOLVE_VALUEe(e36),                                \
                               YENXO_RESOLVE_VALUEe(e37),                                \
                               YENXO_RESOLVE_VALUEe(e38),                                \
                               YENXO_RESOLVE_VALUEe(e39),                                \
                               YENXO_RESOLVE_VALUEe(e40))
#define YENXO_DEFINE_ENUM_IMPL_40_(Type,                                                 \
                                   e1,                                                   \
                                   e2,                                                   \
                                   e3,                                                   \
                                   e4,                                                   \
                                   e5,                                                   \
                                   e6,                                                   \
                                   e7,                                                   \
                                   e8,                                                   \
                                   e9,                                                   \
                                   e10,                                                  \
                                   e11,                                                  \
                                   e12,                                                  \
                                   e13,                                                  \
                                   e14,                                                  \
                                   e15,                                                  \
                                   e16,                                                  \
                                   e17,                                                  \
                                   e18,                                                  \
                                   e19,                                                  \
                                   e20,                                                  \
                                   e21,                                                  \
                                   e22,                                                  \
                                   e23,                                                  \
                                   e24,                                                  \
                                   e25,                                                  \
                                   e26,                                                  \
                                   e27,                                                  \
                                   e28,                                                  \
                                   e29,                                                  \
                                   e30,                                                  \
                                   e31,                                                  \
                                   e32,                                                  \
                                   e33,                                                  \
                                   e34,                                                  \
                                   e35,                                                  \
                                   e36,                                                  \
                                   e37,                                                  \
                                   e38,                                                  \
                                   e39,                                                  \
                                   e40)                                                  \
    enum class [[maybe_unused]] Type{                                                    \
            YENXO_SECOND3e e1,  YENXO_SECOND3e e2,  YENXO_SECOND3e e3,                   \
            YENXO_SECOND3e e4,  YENXO_SECOND3e e5,  YENXO_SECOND3e e6,                   \
            YENXO_SECOND3e e7,  YENXO_SECOND3e e8,  YENXO_SECOND3e e9,                   \
            YENXO_SECOND3e e10, YENXO_SECOND3e e11, YENXO_SECOND3e e12,                  \
            YENXO_SECOND3e e13, YENXO_SECOND3e e14, YENXO_SECOND3e e15,                  \
            YENXO_SECOND3e e16, YENXO_SECOND3e e17, YENXO_SECOND3e e18,                  \
            YENXO_SECOND3e e19, YENXO_SECOND3e e20, YENXO_SECOND3e e21,                  \
            YENXO_SECOND3e e22, YENXO_SECOND3e e23, YENXO_SECOND3e e24,                  \
            YENXO_SECOND3e e25, YENXO_SECOND3e e26, YENXO_SECOND3e e27,                  \
            YENXO_SECOND3e e28, YENXO_SECOND3e e29, YENXO_SECOND3e e30,                  \
            YENXO_SECOND3e e31, YENXO_SECOND3e e32, YENXO_SECOND3e e33,                  \
            YENXO_SECOND3e e34, YENXO_SECOND3e e35, YENXO_SECOND3e e36,                  \
            YENXO_SECOND3e e37, YENXO_SECOND3e e38, YENXO_SECOND3e e39,                  \
            YENXO_SECOND3e e40};                                                         \
    struct [[maybe_unused]] Type##Traits {                                               \
        using Enum [[maybe_unused]] = Type;                                              \
        [[maybe_unused]] static constexpr size_t count = 40;                             \
        [[maybe_unused]] static constexpr std::array<Enum, count>                        \
                values{Enum::YENXO_FIRST3e e1,  Enum::YENXO_FIRST3e e2,                  \
                       Enum::YENXO_FIRST3e e3,  Enum::YENXO_FIRST3e e4,                  \
                       Enum::YENXO_FIRST3e e5,  Enum::YENXO_FIRST3e e6,                  \
                       Enum::YENXO_FIRST3e e7,  Enum::YENXO_FIRST3e e8,                  \
                       Enum::YENXO_FIRST3e e9,  Enum::YENXO_FIRST3e e10,                 \
                       Enum::YENXO_FIRST3e e11, Enum::YENXO_FIRST3e e12,                 \
                       Enum::YENXO_FIRST3e e13, Enum::YENXO_FIRST3e e14,                 \
                       Enum::YENXO_FIRST3e e15, Enum::YENXO_FIRST3e e16,                 \
                       Enum::YENXO_FIRST3e e17, Enum::YENXO_FIRST3e e18,                 \
                       Enum::YENXO_FIRST3e e19, Enum::YENXO_FIRST3e e20,                 \
                       Enum::YENXO_FIRST3e e21, Enum::YENXO_FIRST3e e22,                 \
                       Enum::YENXO_FIRST3e e23, Enum::YENXO_FIRST3e e24,                 \
                       Enum::YENXO_FIRST3e e25, Enum::YENXO_FIRST3e e26,                 \
                       Enum::YENXO_FIRST3e e27, Enum::YENXO_FIRST3e e28,                 \
                       Enum::YENXO_FIRST3e e29, Enum::YENXO_FIRST3e e30,                 \
                       Enum::YENXO_FIRST3e e31, Enum::YENXO_FIRST3e e32,                 \
                       Enum::YENXO_FIRST3e e33, Enum::YENXO_FIRST3e e34,                 \
                       Enum::YENXO_FIRST3e e35, Enum::YENXO_FIRST3e e36,                 \
                       Enum::YENXO_FIRST3e e37, Enum::YENXO_FIRST3e e38,                 \
                       Enum::YENXO_FIRST3e e39, Enum::YENXO_FIRST3e e40};                \
        [[maybe_unused]] static constexpr auto strings() noexcept {                      \
            return boost::hana::make_tuple(boost::hana::make_tuple(YENXO_RESTe e1),      \
                                           boost::hana::make_tuple(YENXO_RESTe e2),      \
                                           boost::hana::make_tuple(YENXO_RESTe e3),      \
                                           boost::hana::make_tuple(YENXO_RESTe e4),      \
                                           boost::hana::make_tuple(YENXO_RESTe e5),      \
                                           boost::hana::make_tuple(YENXO_RESTe e6),      \
                                           boost::hana::make_tuple(YENXO_RESTe e7),      \
                                           boost::hana::make_tuple(YENXO_RESTe e8),      \
                                           boost::hana::make_tuple(YENXO_RESTe e9),      \
                                           boost::hana::make_tuple(YENXO_RESTe e10),     \
                                           boost::hana::make_tuple(YENXO_RESTe e11),     \
                                           boost::hana::make_tuple(YENXO_RESTe e12),     \
                                           boost::hana::make_tuple(YENXO_RESTe e13),     \
                                           boost::hana::make_tuple(YENXO_RESTe e14),     \
                                           boost::hana::make_tuple(YENXO_RESTe e15),     \
                                           boost::hana::make_tuple(YENXO_RESTe e16),     \
                                           boost::hana::make_tuple(YENXO_RESTe e17),     \
                                           boost::hana::make_tuple(YENXO_RESTe e18),     \
                                           boost::hana::make_tuple(YENXO_RESTe e19),     \
                                           boost::hana::make_tuple(YENXO_RESTe e20),     \
                                           boost::hana::make_tuple(YENXO_RESTe e21),     \
                                           boost::hana::make_tuple(YENXO_RESTe e22),     \
                                           boost::hana::make_tuple(YENXO_RESTe e23),     \
                                           boost::hana::make_tuple(YENXO_RESTe e24),     \
                                           boost::hana::make_tuple(YENXO_RESTe e25),     \
                                           boost::hana::make_tuple(YENXO_RESTe e26),     \
                                           boost::hana::make_tuple(YENXO_RESTe e27),     \
                                           boost::hana::make_tuple(YENXO_RESTe e28),     \
                                           boost::hana::make_tuple(YENXO_RESTe e29),     \
                                           boost::hana::make_tuple(YENXO_RESTe e30),     \
                                           boost::hana::make_tuple(YENXO_RESTe e31),     \
                                           boost::hana::make_tuple(YENXO_RESTe e32),     \
                                           boost::hana::make_tuple(YENXO_RESTe e33),     \
                                           boost::hana::make_tuple(YENXO_RESTe e34),     \
                                           boost::hana::make_tuple(YENXO_RESTe e35),     \
                                           boost::hana::make_tuple(YENXO_RESTe e36),     \
                                           boost::hana::make_tuple(YENXO_RESTe e37),     \
                                           boost::hana::make_tuple(YENXO_RESTe e38),     \
                                           boost::hana::make_tuple(YENXO_RESTe e39),     \
                                           boost::hana::make_tuple(YENXO_RESTe e40));    \
        }                                                                                \
        [[maybe_unused]] static char const* toString(Enum x) {                           \
            switch (x) {                                                                 \
            case Enum::YENXO_FIRST3e e1:                                                 \
                return YENXO_THIRD3e e1;                                                 \
            case Enum::YENXO_FIRST3e e2:                                                 \
                return YENXO_THIRD3e e2;                                                 \
            case Enum::YENXO_FIRST3e e3:                                                 \
                return YENXO_THIRD3e e3;                                                 \
            case Enum::YENXO_FIRST3e e4:                                                 \
                return YENXO_THIRD3e e4;                                                 \
            case Enum::YENXO_FIRST3e e5:                                                 \
                return YENXO_THIRD3e e5;                                                 \
            case Enum::YENXO_FIRST3e e6:                                                 \
                return YENXO_THIRD3e e6;                                                 \
            case Enum::YENXO_FIRST3e e7:                                                 \
                return YENXO_THIRD3e e7;                                                 \
            case Enum::YENXO_FIRST3e e8:                                                 \
                return YENXO_THIRD3e e8;                                                 \
            case Enum::YENXO_FIRST3e e9:                                                 \
                return YENXO_THIRD3e e9;                                                 \
            case Enum::YENXO_FIRST3e e10:                                                \
                return YENXO_THIRD3e e10;                                                \
            case Enum::YENXO_FIRST3e e11:                                                \
                return YENXO_THIRD3e e11;                                                \
            case Enum::YENXO_FIRST3e e12:                                                \
                return YENXO_THIRD3e e12;                                                \
            case Enum::YENXO_FIRST3e e13:                                                \
                return YENXO_THIRD3e e13;                                                \
            case Enum::YENXO_FIRST3e e14:                                                \
                return YENXO_THIRD3e e14;                                                \
            case Enum::YENXO_FIRST3e e15:                                                \
                return YENXO_THIRD3e e15;                                                \
            case Enum::YENXO_FIRST3e e16:                                                \
                return YENXO_THIRD3e e16;                                                \
            case Enum::YENXO_FIRST3e e17:                                                \
                return YENXO_THIRD3e e17;                                                \
            case Enum::YENXO_FIRST3e e18:                                                \
                return YENXO_THIRD3e e18;                                                \
            case Enum::YENXO_FIRST3e e19:                                                \
                return YENXO_THIRD3e e19;                                                \
            case Enum::YENXO_FIRST3e e20:                                                \
                return YENXO_THIRD3e e20;                                                \
            case Enum::YENXO_FIRST3e e21:                                                \
                return YENXO_THIRD3e e21;                                                \
            case Enum::YENXO_FIRST3e e22:                                                \
                return YENXO_THIRD3e e22;                                                \
            case Enum::YENXO_FIRST3e e23:                                                \
                return YENXO_THIRD3e e23;                                                \
            case Enum::YENXO_FIRST3e e24:                                                \
                return YENXO_THIRD3e e24;                                                \
            case Enum::YENXO_FIRST3e e25:                                                \
                return YENXO_THIRD3e e25;                                                \
            case Enum::YENXO_FIRST3e e26:                                                \
                return YENXO_THIRD3e e26;                                                \
            case Enum::YENXO_FIRST3e e27:                                                \
                return YENXO_THIRD3e e27;                                                \
            case Enum::YENXO_FIRST3e e28:                                                \
                return YENXO_THIRD3e e28;                                                \
            case Enum::YENXO_FIRST3e e29:                                                \
                return YENXO_THIRD3e e29;                                                \
            case Enum::YENXO_FIRST3e e30:                                                \
                return YENXO_THIRD3e e30;                                                \
            case Enum::YENXO_FIRST3e e31:                                                \
                return YENXO_THIRD3e e31;                                                \
            case Enum::YENXO_FIRST3e e32:                                                \
                return YENXO_THIRD3e e32;                                                \
            case Enum::YENXO_FIRST3e e33:                                                \
                return YENXO_THIRD3e e33;                                                \
            case Enum::YENXO_FIRST3e e34:                                                \
                return YENXO_THIRD3e e34;                                                \
            case Enum::YENXO_FIRST3e e35:                                                \
                return YENXO_THIRD3e e35;                                                \
            case Enum::YENXO_FIRST3e e36:                                                \
                return YENXO_THIRD3e e36;                                                \
            case Enum::YENXO_FIRST3e e37:                                                \
                return YENXO_THIRD3e e37;                                                \
            case Enum::YENXO_FIRST3e e38:                                                \
                return YENXO_THIRD3e e38;                                                \
            case Enum::YENXO_FIRST3e e39:                                                \
                return YENXO_THIRD3e e39;                                                \
            case Enum::YENXO_FIRST3e e40:                                                \
                return YENXO_THIRD3e e40;                                                \
            }                                                                            \
            assert(false);                                                               \
            throw yenxo::BadEnumValue(x);                                                \
        }                                                                                \
        [[maybe_unused]] static constexpr std::string_view typeName() noexcept {         \
            return BOOST_HANA_PP_STRINGIZE(Type);                                        \
        }                                                                                \
    };                                                                                   \
    [[maybe_unused]] inline Type##Traits traits(Type) {                                  \
        return {};                                                                       \
    }                                                                                    \
    [[maybe_unused]] inline std::ostream& operator<<(std::ostream& os, Type e) {         \
        return os << Type##Traits::toString(e);                                          \
    }                                                                                    \
    struct ANONYMOUS_STRUCT
