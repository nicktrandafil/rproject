#pragma once


// local
#include <meta.hpp>
#include <variant.hpp>
#include <when.hpp>

// boost
#include <boost/hana.hpp>

// std
#include <type_traits>


namespace detail {


///
/// Unified converstion of T to Variant
///
template <typename T, typename = void>
struct ToVariant : ToVariant<T, When<true>> {};


///
/// Specialization to types with `static Variant T::toVariant(T)`
///
template <typename T, bool condition>
struct ToVariant<T, When<condition>> {
    static_assert(
            rp::callable(T::toVariant, rp::Type<T>()),
            "The type T must have T::toVariant(T) static member function");

    static_assert(
            std::is_same_v<decltype(T::toVariant(std::declval<T>())), Variant>,
            "The return type of T::toVariant must be Variant");

    Variant operator()(T const& x) const { return T::toVariant(x); }
};


///
/// Specialization for types for which Variant have constructor
///
template <typename T>
struct ToVariant<T, When<rp::detail::Valid<
        decltype(Variant(std::declval<T>()))>::value>> {
    Variant operator()(T x) const { return Variant(x); }
};


///
/// Convinient shortcut function
///
template <typename T>
constexpr Variant toVariant(T&& t) {
    return ToVariant<std::decay_t<T>>()(std::forward<T>(t));
}


///
/// Unified converstion of Variant to T
///
template <typename T, typename = void>
struct FromVariant : FromVariant<T, When<true>> {};


///
/// Specialization to types with `static T T::fromVariant(Variant)`
///
template <typename T, bool condition>
struct FromVariant<T, When<condition>> {
    static_assert(
            rp::callable(T::fromVariant, rp::Type<Variant>()),
            "The type T must have static member function fromVariant(Variant)");
    static_assert(
            std::is_same_v<decltype(T::fromVariant(Variant())), T>,
            "The return type of T::fromVariant must be T");

    T operator()(Variant const& x) const { return T::fromVariant(x); }
};


///
/// Specialization for types for which Variant have conversion
///
template <typename T>
struct FromVariant<T,
        When<rp::detail::Valid<decltype(static_cast<T>(Variant()))>::value>> {
    T operator()(Variant const& x) const { return static_cast<T>(x); }
};


///
/// Convinient shortcut function
///
template <typename T>
constexpr T fromVariant(Variant const& v) {
    return FromVariant<T>()(v);
}


///
/// Convinient shortcut function
///
template <typename T>
constexpr void fromVariant(T& x, Variant const& v) {
    x = FromVariant<T>()(v);
}


///
/// Is `T` the `std::optional` type
///
template <typename T>
struct IsOptional : std::false_type {};


template <typename T>
struct IsOptional<std::optional<T>> : std::true_type {};


template <typename T>
constexpr auto isOptional(rp::Type<T>) {
    return IsOptional<std::remove_reference_t< std::decay_t<T>>>::value;
}


template <typename T, typename = void>
struct HasDefaultMemVals : HasDefaultMemVals<T, When<true>> {};


template <typename T, bool any>
struct HasDefaultMemVals<T, When<any>> : std::false_type {};


template <typename T>
struct HasDefaultMemVals<T,
        When<rp::callable(T::defaultMemVals)>>
            : std::true_type
{};


///
/// Has field `name` in class `C` a default value
///
template <typename T, typename S>
constexpr auto hasDefaultValue(S name) {
    static_assert(
                HasDefaultMemVals<T>::value,
                "The T must have `T::DefaultMemVals` static member");
    return boost::hana::find(T::defaultMemVals(), name) != boost::hana::nothing;
}


} // namespace detail


namespace mixin {


///
/// Adds conversion support to and from `Variant`
/// Specifically, adds members:
///     `static Variant toVariant(Derived)`
///     `static Derived fromVariant(Variant)`
///
template <typename Derived>
struct Var {
    static Variant toVariant(Derived const& x) {
        Variant::Map ret;

        boost::hana::for_each(x, boost::hana::fuse([&](auto name, auto value) {
            ret[boost::hana::to<char const*>(name)] = detail::toVariant(value);
        }));

        return Variant(ret);
    }

    static Derived fromVariant(Variant const& x) {
        using namespace std::literals;
        Derived ret;
        auto const& map = x.map();

        boost::hana::for_each(boost::hana::accessors<Derived>(),
                       boost::hana::fuse([&](auto name, auto value) {
            auto& tmp = value(ret);
            auto const it = map.find(boost::hana::to<char const*>(name));
            if (map.end() == it) {
                throw std::logic_error(
                            boost::hana::to<char const*>(name) +
                            " not found in map"s);
            } else {
                detail::fromVariant(tmp, it->second);
            }
        }));

        return ret;
    }
};


///
/// Adds conversion support to and from `Variant`, defaulting missings fields
/// Specifically adds members:
///     `static Variant toVariant(Derived)`
/// 	`static Derived fromVariant(Variant)`
///
template <typename Derived>
struct VarDef {
    static Variant toVariant(Derived const& x) {
        Variant::Map ret;

        boost::hana::for_each(x, boost::hana::fuse([&](auto name, auto value) {
            if constexpr (detail::isOptional(rp::type_c<decltype(value)>)) {
                if (value.has_value()) {
                    ret[boost::hana::to<char const*>(name)] =
                            detail::toVariant(*value);
                }
            } else {
                ret[boost::hana::to<char const*>(name)] =
                        detail::toVariant(value);
            }
        }));

        return Variant(ret);
    }

    static Derived fromVariant(Variant const& x) {
        using namespace std::literals;

        Derived ret;
        auto const& map = x.map();

        boost::hana::for_each(boost::hana::accessors<Derived>(),
                       boost::hana::fuse([&](auto name, auto value) {
            auto& tmp = value(ret);
            auto const it = map.find(boost::hana::to<char const*>(name));

            if (map.end() == it) {
                if constexpr (detail::hasDefaultValue<Derived>(name)) {
                    tmp = Derived::defaultMemVals()[name];
                } else if constexpr (!detail::isOptional(rp::type_c<decltype(tmp)>)) {
                    throw std::logic_error(
                                boost::hana::to<char const*>(name) +
                                " not found in map, and default"
                                " value is not provided"s);
                }

            } else {
                if constexpr (detail::isOptional(rp::type_c<decltype(tmp)>)) {
                    detail::fromVariant(*tmp, it->second);
                } else {
                    detail::fromVariant(tmp, it->second);
                }
            }
        }));

        return ret;
    }
};


///
/// Adds member `void update(Variant)`
///
template <typename Derived>
struct UpdateFromVar {
    void update(Variant const& x) {
        Derived& self = static_cast<Derived&>(*this);
        auto const& map = x.map();
        for (auto const& v: map) {
            bool found{false};
            boost::hana::for_each(boost::hana::accessors<Derived>(),
                                  boost::hana::fuse([&](auto name, auto value) {
                if (boost::hana::to<char const*>(name) != v.first) { return; }
                auto& tmp = value(self);
                detail::fromVariant(tmp, v.second);
                found = true;
            }));

            if (!found) {
                throw std::logic_error(v.first + " no such member");
            }
        }
    }
};


} // namespace