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

#include <yenxo/define_enum.hpp>
#include <yenxo/type_name.hpp>

#include <catch2/catch.hpp>

#include <map>

using namespace yenxo;

namespace {

/// [sn_static_method]
struct Def {
    constexpr static std::string_view typeName() noexcept {
        return "Def";
    }
};
/// [sn_static_method]

/// [sn_adl]
struct Def2 {
    friend constexpr std::string_view typeNameImpl(Def2 const*) noexcept {
        return "Def2";
    }
};
/// [sn_adl]

} // namespace

/// [sn_spec]
namespace {
struct Def3 {};
} // namespace

namespace yenxo {
template <>
struct TypeNameImpl<Def3> {
    static constexpr std::string_view apply() noexcept {
        return "Def3";
    }
};
/// [sn_spec]

} // namespace yenxo

namespace {

/// [sn_enum]
YENXO_DEFINE_ENUM(E1, e1, e2);
/// [sn_enum]

} // namespace

TEST_CASE("Check typeName", "[utilities]") {
    /// [sn_udt_checks]
    static_assert(typeName(boost::hana::type_c<Def>) == "Def");
    REQUIRE(typeName(boost::hana::type_c<Def>) == "Def");
    static_assert(typeName(boost::hana::type_c<Def2>) == "Def2");
    REQUIRE(typeName(boost::hana::type_c<Def2>) == "Def2");
    static_assert(typeName(boost::hana::type_c<Def3>) == "Def3");
    REQUIRE(typeName(boost::hana::type_c<Def3>) == "Def3");
    /// [sn_udt_checks]

    /// [sn_enum_checks]
    static_assert(typeName(boost::hana::type_c<E1>) == "E1");
    REQUIRE(typeName(boost::hana::type_c<E1>) == "E1");
    /// [sn_enum_checks]

    REQUIRE(typeName(boost::hana::type_c<std::integral_constant<E1, E1::e1>>) == "E1{0}");

    REQUIRE(typeName(boost::hana::type_c<std::vector<int>>) == "list of int32");
    REQUIRE(typeName(boost::hana::type_c<std::map<int, std::string>>)
            == "map of int32-string");

    REQUIRE(typeName(boost::hana::type_c<float>) == "float");
    REQUIRE(typeName(boost::hana::type_c<double>) == "double");
    REQUIRE(typeName(boost::hana::type_c<wchar_t>) == "wchar");
    REQUIRE(typeName(boost::hana::type_c<std::optional<char>>) == "optional char");
    REQUIRE(typeName(boost::hana::type_c<std::nullptr_t>) == "nullptr");
    REQUIRE(typeName(boost::hana::type_c<std::monostate>) == "null");
    REQUIRE(typeName(boost::hana::type_c<std::variant<char, bool>>)
            == "one of [char, boolean]");
    REQUIRE(typeName(boost::hana::type_c<bool>) == "boolean");
    REQUIRE(typeName(boost::hana::type_c<char>) == "char");
    REQUIRE(typeName(boost::hana::type_c<int8_t>) == "int8");
    REQUIRE(typeName(boost::hana::type_c<uint8_t>) == "uint8");
    REQUIRE(typeName(boost::hana::type_c<uint16_t>) == "uint16");
    REQUIRE(typeName(boost::hana::type_c<int32_t>) == "int32");
    REQUIRE(typeName(boost::hana::type_c<uint32_t>) == "uint32");
    REQUIRE(typeName(boost::hana::type_c<std::string>) == "string");
}
