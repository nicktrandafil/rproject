/*
  MIT License

  Copyright (c) 2018 Nicolai Trandafil

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

#include <yenxo/enum_traits.hpp>
#include <yenxo/meta.hpp>
#include <yenxo/when.hpp>

#include <boost/hana/core/is_a.hpp>
#include <boost/hana/fold.hpp>
#include <boost/hana/intersperse.hpp>
#include <boost/hana/transform.hpp>

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <variant>

namespace yenxo {

/// Get the name of a type
///
/// The template `TypeNameImpl` has specializations for:
/// * fundamental types;
/// * any type compatible with either requirement: standard Container or MapContainer. The
/// names are 'list' and 'map' respectively;
/// * any enum defined via `YENXO_DEFINE_ENUM`. Define,
/// @snippet test/type_name.cpp sn_enum
/// Test,
/// @snippet test/type_name.cpp sn_enum_checks
/// * `std::integral_constant`. The function object should be enabled for underlying type;
/// * `std::optional`. The function object should be enabled for underlying type;
///
/// There are few ways to enable the function object for user defined types:
/// * specialize the `TypeNameImpl`;
/// @snippet test/type_name.cpp sn_spec
/// * provide `auto typeNameImpl(T const*)` function discoverable via ADL lookup;
/// @snippet test/type_name.cpp sn_adl
/// * provide `auto typeName()` static member.
/// @snippet test/type_name.cpp sn_static_method
///
/// Checks for user defined types:
/// @snippet test/type_name.cpp sn_udt_checks
///
/// \ingroup group-utility
#ifdef YENXO_DOXYGEN_INVOKED
constexpr auto typeName = [](type) { return TypeNameImpl<type>::apply(); };
#else
template <class T, class = void>
struct TypeNameImpl : TypeNameImpl<T, When<true>> {};

struct TypeNameT {
    template <class T>
    constexpr auto operator()(boost::hana::basic_type<T>) const;
};

constexpr TypeNameT typeName;

template <class T, bool condition>
struct TypeNameImpl<T, When<condition>> {
    [[noreturn]] static std::string_view apply() {
        static_assert(T::has_no_type_name);
        throw 0;
    }
};

template <>
struct TypeNameImpl<std::nullptr_t> {
    static constexpr std::string_view apply() noexcept {
        return "nullptr";
    }
};

template <>
struct TypeNameImpl<bool> {
    static constexpr std::string_view apply() noexcept {
        return "boolean";
    }
};

// integer

template <>
struct TypeNameImpl<uint16_t> {
    static constexpr std::string_view apply() noexcept {
        return "uint16";
    }
};

template <>
struct TypeNameImpl<int16_t> {
    static constexpr std::string_view apply() noexcept {
        return "int16";
    }
};

template <>
struct TypeNameImpl<uint32_t> {
    static constexpr std::string_view apply() noexcept {
        return "uint32";
    }
};

template <>
struct TypeNameImpl<int32_t> {
    static constexpr std::string_view apply() noexcept {
        return "int32";
    }
};

template <>
struct TypeNameImpl<uint64_t> {
    static constexpr std::string_view apply() noexcept {
        return "uint64";
    }
};

template <>
struct TypeNameImpl<int64_t> {
    static constexpr std::string_view apply() noexcept {
        return "int64";
    }
};

// character

template <>
struct TypeNameImpl<char> {
    static constexpr std::string_view apply() noexcept {
        return "char";
    }
};

template <>
struct TypeNameImpl<uint8_t> {
    static constexpr std::string_view apply() noexcept {
        return "uint8";
    }
};

template <>
struct TypeNameImpl<int8_t> {
    static constexpr std::string_view apply() noexcept {
        return "int8";
    }
};

template <>
struct TypeNameImpl<wchar_t> {
    static constexpr std::string_view apply() noexcept {
        return "wchar";
    }
};

template <class T, T v>
struct TypeNameImpl<std::integral_constant<T, v>> {
    static std::string apply() {
        if constexpr (std::is_enum_v<T>) {
            return std::string(typeName(boost::hana::type_c<T>)) + "{"
                 + std::string(std::to_string(static_cast<std::underlying_type_t<T>>(v)))
                 + "}";
        } else {
            return std::string(typeName(boost::hana::type_c<T>)) + "{"
                 + std::string(std::to_string(v)) + "}";
        }
    }
};

template <class T>
struct TypeNameImpl<T, When<boost::hana::is_a<boost::hana::string_tag, T>>> {
    static std::string apply() {
        return boost::hana::to<char const*>(T()) + std::string(" literal");
    }
};

// floating point

template <>
struct TypeNameImpl<float> {
    static constexpr std::string_view apply() noexcept {
        return "float";
    }
};

template <>
struct TypeNameImpl<double> {
    static constexpr std::string_view apply() noexcept {
        return "double";
    }
};

template <>
struct TypeNameImpl<long double> {
    static constexpr std::string_view apply() noexcept {
        return "long double";
    }
};

// string

template <>
struct TypeNameImpl<std::string> {
    static constexpr std::string_view apply() noexcept {
        return "string";
    }
};

// collections

template <class T>
struct TypeNameImpl<T,
                    When<isContainer(boost::hana::type_c<T>)
                         && isPair(boost::hana::type_c<typename T::value_type>)>> {
    static std::string apply() {
        return "map of "
             + std::string(typeName(boost::hana::type_c<typename T::key_type>)) + "-"
             + std::string(typeName(boost::hana::type_c<typename T::mapped_type>));
    }
};

template <class T>
struct TypeNameImpl<T,
                    When<isContainer(boost::hana::type_c<T>)
                         && !isPair(boost::hana::type_c<typename T::value_type>)>> {
    static std::string apply() {
        return "list of "
             + std::string(typeName(boost::hana::type_c<typename T::value_type>));
    }
};

// optional

template <class T>
struct TypeNameImpl<T, When<isOptional(boost::hana::type_c<T>)>> {
    static std::string apply() {
        return "optional "
             + static_cast<std::string>(
                       typeName(boost::hana::type_c<typename T::value_type>));
    }
};

// variant

template <>
struct TypeNameImpl<std::monostate> {
    static std::string_view apply() noexcept {
        return "null";
    }
};

template <class T>
struct TypeNameImpl<T, When<detail::Valid<std::variant_alternative_t<0, T>>::value>> {
private:
    template <class... Args>
    static boost::hana::tuple<boost::hana::type<Args>...> types(
            std::variant<Args...> const&);

public:
    static std::string apply() {
        return "one of ["
             + boost::hana::fold(boost::hana::intersperse(
                                         boost::hana::transform(
                                                 decltype(types(std::declval<T>()))(),
                                                 [](auto type) {
                                                     return static_cast<std::string>(
                                                             typeName(type));
                                                 }),
                                         ", "),
                                 "",
                                 boost::hana::_ + boost::hana::_)
             + "]";
    }
};

// non intrusive

template <class T>
struct TypeNameImpl<
        T,
        When<detail::Valid<decltype(typeNameImpl(std::declval<T const*>()))>::value>> {
    static constexpr std::string_view apply() noexcept(
            noexcept(typeNameImpl(std::declval<T const*>()))) {
        return typeNameImpl(static_cast<T const*>(nullptr));
    }
};

template <class T>
struct TypeNameImpl<T, When<detail::Valid<decltype(EnumTraits<T>::typeName())>::value>> {
    static constexpr auto apply() noexcept(noexcept(EnumTraits<T>::typeName())) {
        return EnumTraits<T>::typeName();
    }
};

template <class T>
struct TypeNameImpl<T, When<detail::Valid<decltype(T::typeName())>::value>> {
    static constexpr auto apply() noexcept(noexcept(T::typeName())) {
        return T::typeName();
    }
};

template <class T>
constexpr auto TypeNameT::operator()(boost::hana::basic_type<T>) const {
    return TypeNameImpl<std::remove_cv_t<std::remove_reference_t<T>>>::apply();
}
#endif

} // namespace yenxo
