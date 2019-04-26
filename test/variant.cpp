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


// tested
#include <serialize/variant.hpp>

// local
#include <serialize/type_name.hpp>

// 3rd
#include <catch2/catch.hpp>
#include <rapidjson/document.h>

// boost
#include <boost/hana.hpp>

// std
#include <limits.h>
#include <sstream>


namespace hana = boost::hana;


using namespace serialize;


TEST_CASE("Check Variant", "[Variant]") {
    SECTION("boolean") {
        bool const expected{true};
        auto const x = Variant(expected);
        REQUIRE(expected == x.boolean());
        REQUIRE_THROWS_AS(Variant().boolean(), VariantEmpty);
        REQUIRE_THROWS_AS(Variant("").boolean(), VariantBadType);
        REQUIRE(Variant().booleanOr(true) == true);
    }

    SECTION("char") {
        char const expected{7};
        auto const x = Variant(expected);
        REQUIRE(expected == x.character());
        REQUIRE_THROWS_AS(Variant().character(), VariantEmpty);
        REQUIRE_THROWS_AS(Variant("").character(), VariantBadType);
        REQUIRE(Variant().characterOr(1) == 1);
    }

    SECTION("short int") {
        unsigned short int const expected{3};
        auto const x = Variant(expected);
        REQUIRE(expected == x.ushortInt());
        REQUIRE_THROWS_AS(Variant().ushortInt(), VariantEmpty);
        REQUIRE_THROWS_AS(Variant("").ushortInt(), VariantBadType);
        REQUIRE(Variant().ushortIntOr(1) == 1);
    }

    SECTION("short int") {
        short int const expected{6};
        auto const x = Variant(expected);
        REQUIRE(expected == x.shortInt());
        REQUIRE_THROWS_AS(Variant().shortInt(), VariantEmpty);
        REQUIRE_THROWS_AS(Variant("").shortInt(), VariantBadType);
        REQUIRE(Variant().shortIntOr(1) == 1);
    }

    SECTION("integer") {
        int const expected{7};
        auto const x = Variant(expected);
        REQUIRE(expected == x.integer());
        REQUIRE_THROWS_AS(Variant().integer(), VariantEmpty);
        REQUIRE_THROWS_AS(Variant("").integer(), VariantBadType);
        REQUIRE(Variant().integerOr(1) == 1);
    }

    SECTION("uint") {
        unsigned int const expected{8};
        auto const x = Variant(expected);
        REQUIRE(expected == x.uint());
        REQUIRE_THROWS_AS(Variant().uint(), VariantEmpty);
        REQUIRE_THROWS_AS(Variant("").uint(), VariantBadType);
        REQUIRE(Variant().uintOr(1) == 1);
    }

    SECTION("longInt") {
        signed long const expected{12};
        auto const x = Variant(expected);
        REQUIRE(expected == x.longInt());
        REQUIRE_THROWS_AS(Variant().longInt(), VariantEmpty);
        REQUIRE_THROWS_AS(Variant("").longInt(), VariantBadType);
        REQUIRE(Variant().longInteOr(12) == 12);
    }

    SECTION("ulongInt") {
        unsigned long const expected{13};
        auto const x = Variant(expected);
        REQUIRE(expected == x.ulongInt());
        REQUIRE_THROWS_AS(Variant().ulongInt(), VariantEmpty);
        REQUIRE_THROWS_AS(Variant("").ulongInt(), VariantBadType);
        REQUIRE(Variant().ulongIntOr(expected) == expected);
    }

    SECTION("floating") {
        double const expected{5.1};
        auto const x = Variant(expected);
        REQUIRE(expected == x.floating());
        REQUIRE_THROWS_AS(Variant().floating(), VariantEmpty);
        REQUIRE_THROWS_AS(Variant("").floating(), VariantBadType);
        REQUIRE(Variant().floatingOr(1.1) == 1.1);
    }

    SECTION("string") {
        std::string const expected = "ab";
        auto const x = Variant(expected);
        REQUIRE(expected == x.str());
        REQUIRE_THROWS_AS(Variant().str(), VariantEmpty);
        REQUIRE_THROWS_AS(Variant(5).str(), VariantBadType);
        REQUIRE(Variant().strOr("abc") == "abc");
    }

    SECTION("Variant::Vec") {
        auto const expected = Variant::Vec{Variant(1), Variant("ab")};
        auto const x = Variant(expected);
        REQUIRE(expected == x.vec());
        REQUIRE_THROWS_AS(Variant().vec(), VariantEmpty);
        REQUIRE_THROWS_AS(Variant(5).vec(), VariantBadType);
        REQUIRE(Variant().vecOr(Variant::Vec{Variant("abc")}) ==
                Variant::Vec{Variant("abc")});
    }

    SECTION("Variant::Map") {
        auto const expected = Variant::Map{std::pair("1", Variant(1))};
        auto const x = Variant(expected);
        REQUIRE(expected == x.map());
        REQUIRE_THROWS_AS(Variant().map(), VariantEmpty);
        REQUIRE_THROWS_AS(Variant(5).map(), VariantBadType);
        REQUIRE(Variant().mapOr(Variant::Map{std::pair("1", Variant(1))}) ==
                Variant::Map{std::pair("1", Variant(1))});
    }

    SECTION("allow representable integral type conversions") {
        auto const types = hana::make_tuple(
            hana::type_c<bool>,
            hana::type_c<char>,
            hana::type_c<unsigned char>,
            hana::type_c<short int>,
            hana::type_c<unsigned short int>,
            hana::type_c<int>,
            hana::type_c<unsigned int>);

        hana::for_each(
            types,
            [&](auto x) {
                hana::for_each(
                    types,
                    [](auto y) {
                        using X = typename decltype(x)::type;
                        using Y = typename decltype(y)::type;
                        using YLimiets = std::numeric_limits<Y>;

                        auto const y_min = YLimiets::min();

                        // no fails

                        // min bound
                        auto const y_min_in_x = static_cast<X>(y_min);
                        if (std::to_string(y_min) == std::to_string(y_min_in_x)) {
                            REQUIRE(static_cast<Y>(Variant(y_min_in_x)) == y_min);
                            REQUIRE(Variant(y_min_in_x).asOr<Y>(1) == y_min);
                        }

                        auto const y_max = YLimiets::max();

                        // max bound
                        auto const y_max_in_x = static_cast<X>(y_max);
                        if (std::to_string(y_max) == std::to_string(y_max_in_x)) {
                            REQUIRE(static_cast<Y>(Variant(y_max_in_x)) == y_max);
                            REQUIRE(Variant(y_max_in_x).asOr<Y>(1) == y_max);
                        }

                        REQUIRE(static_cast<Y>(Variant(X(1))) == Y(1));

                        // fails

                        // min - 1 out of range
                        auto const y_min_in_x_1 = static_cast<X>(static_cast<double>(y_min) - 1);
                        if (std::to_string(static_cast<double>(y_min) - 1) ==
                                std::to_string(static_cast<double>(y_min_in_x_1))) {
                            REQUIRE_THROWS_AS(
                                static_cast<Y>(Variant(y_min_in_x_1)),
                                VariantIntegralOverflow);
                            REQUIRE_THROWS_AS(
                                Variant(y_min_in_x_1).asOr<Y>(1),
                                VariantIntegralOverflow);
                            REQUIRE_THROWS_WITH(
                                static_cast<Y>(Variant(y_min_in_x_1)),
                                "The type '" +
                                        std::string(unqualifiedTypeName<Y>()) +
                                        "' can not hold the value '" +
                                        std::to_string(y_min_in_x_1) + "'");
                            REQUIRE_THROWS_WITH(
                                Variant(y_min_in_x_1).asOr<Y>(1),
                                "The type '" +
                                        std::string(unqualifiedTypeName<Y>()) +
                                        "' can not hold the value '" +
                                        std::to_string(y_min_in_x_1) + "'");
                        }

                        // max + 1 out of range
                        auto const y_max_in_x_1 = static_cast<X>(static_cast<double>(y_max) + 1);
                        if (std::to_string(static_cast<double>(y_max) + 1) ==
                                std::to_string(static_cast<double>(y_max_in_x_1))) {
                            REQUIRE_THROWS_AS(
                                static_cast<Y>(Variant(y_max_in_x_1)),
                                VariantIntegralOverflow);
                            REQUIRE_THROWS_AS(
                                Variant(y_max_in_x_1).asOr<Y>(1),
                                VariantIntegralOverflow);
                            REQUIRE_THROWS_WITH(
                                static_cast<Y>(Variant(y_max_in_x_1)),
                                "The type '" +
                                        std::string(unqualifiedTypeName<Y>()) +
                                        "' can not hold the value '" +
                                        std::to_string(y_max_in_x_1) + "'");
                            REQUIRE_THROWS_WITH(
                                Variant(y_max_in_x_1).asOr<Y>(1),
                                "The type '" +
                                        std::string(unqualifiedTypeName<Y>()) +
                                        "' can not hold the value '" +
                                        std::to_string(y_max_in_x_1) + "'");
                        }
                    });
            });

        REQUIRE_THROWS_AS(Variant(1.1).integer(), VariantBadType);
        REQUIRE_THROWS_AS(Variant(Variant::Vec()).integer(), VariantBadType);
        REQUIRE_THROWS_AS(Variant(Variant::Map()).integer(), VariantBadType);
    }

    SECTION("from JSON") {
        SECTION("int") {
            auto const raw = R"(5)";
            Variant expected(5);
            REQUIRE(expected == Variant::from(rapidjson::Document().Parse(raw)));
        }

        SECTION("map") {
            auto const raw = R"(
                {
                    "x": 6,
                    "y": [1, 2],
                    "z": {
                        "a": "a",
                        "b": "b"
                    }
                }
            )";
            Variant expected{Variant::Map{
                std::make_pair("x", Variant(6)),
                std::make_pair("y", Variant(Variant::Vec{Variant(1), Variant(2)})),
                std::make_pair("z", Variant(Variant::Map{
                    std::make_pair("a", Variant("a")),
                    std::make_pair("b", Variant("b"))}))
            }};
            REQUIRE(expected == Variant::from(rapidjson::Document().Parse(raw)));
        }
    }

    SECTION("to JSON") {
        SECTION("int") {
            rapidjson::Document expected;
            expected.SetInt(6);
            rapidjson::Document json;
            Variant(int(6)).to(json);
            REQUIRE(expected == json);
        }

        SECTION("map") {
            auto const raw = R"(
                {
                    "x": 6,
                    "y": [1, 2],
                    "z": {
                        "a": "a",
                        "b": "b"
                    }
                }
            )";

            rapidjson::Document expected;
            expected.Parse(raw);

            rapidjson::Document json;
            Variant{Variant::Map{
                std::make_pair("x", Variant(6)),
                        std::make_pair("y", Variant(Variant::Vec{Variant(1), Variant(2)})),
                std::make_pair("z", Variant(Variant::Map{
                    std::make_pair("a", Variant("a")),
                    std::make_pair("b", Variant("b"))}))
            }}.to(json);

            REQUIRE(expected == json);
        }

        SECTION("string") {
            Variant var(VariantMap({std::make_pair("a", Variant("b"))}));
            auto const json_str = var.toJson();
            REQUIRE(json_str == R"({"a":"b"})");
            REQUIRE(var == Variant::fromJson(json_str));
            REQUIRE_THROWS_AS(Variant::fromJson("{abc"), std::runtime_error);
        }

        SECTION("char") {
            Variant const var(char(1));
            rapidjson::Document expected;
            expected.SetInt(1);
            rapidjson::Document actual;
            var.to(actual);
            REQUIRE(actual == expected);
        }

        SECTION("short") {
            Variant const var(short(1));
            rapidjson::Document expected;
            expected.SetInt(1);
            rapidjson::Document actual;
            var.to(actual);
            REQUIRE(actual == expected);
        }

        SECTION("unsigned short") {
            unsigned short const tmp = 1;
            Variant const var(tmp);
            rapidjson::Document expected;
            expected.SetUint(1);
            rapidjson::Document actual;
            var.to(actual);
            REQUIRE(actual == expected);
        }
    }

    SECTION("ostream") {
        Variant var1{Variant::Map{std::make_pair("x", Variant(6))}};
        Variant var2{Variant::Map{std::make_pair("y", Variant(Variant::Vec{Variant(1), Variant(2)}))}};
        Variant var3(5);
        Variant var4;
        Variant var5("abc");

        auto const expected1 = "{ x: 6; }";
        auto const expected2 = "{ y: [ 1, 2 ]; }";
        auto const expected3 = "5";
        auto const expected4 = "Null";
        auto const expected5 = "abc";

        std::ostringstream os;
        os << var1;
        REQUIRE(expected1 == os.str());

        os.clear();
        os.str("");
        os << var2;
        REQUIRE(expected2 == os.str());

        os.clear();
        os.str("");
        os << var3;
        REQUIRE(expected3 == os.str());

        os.clear();
        os.str("");
        os << var4;
        REQUIRE(expected4 == os.str());

        os.clear();
        os.str("");
        os << var5;
        REQUIRE(expected5 == os.str());
    }

    SECTION("Conversion for user defined types") {
        struct X {
            static Variant toVariant(X const& x) { return Variant(x.x); }
            static X fromVariant(Variant const& x) { return X{x.integer()}; }
            bool operator==(X const& rhs) const { return x == rhs.x; }
            int x;
        };

        REQUIRE(Variant(1) == Variant(X{1}));
        REQUIRE(X{1} == static_cast<X>(Variant(1)));
        REQUIRE(X{1} == X(Variant(1)));
    }

    SECTION("Assign") {
        Variant v1(1);
        Variant v2("abc");
        v2 = v1;
        REQUIRE(v2 == Variant(1));
    }

    SECTION("Comparison") {
        REQUIRE(Variant(1) == Variant(1));
        REQUIRE(Variant(2) != Variant(1));
    }

    SECTION("From JSON") {
        auto const json = R"(
            [{"abc": 1}]
        )";

        REQUIRE(Variant::from(rapidjson::Document().Parse(json)) ==
                Variant(Variant::Vec{
                            Variant(Variant::Map{{"abc", Variant(1)}})}));
    }

    SECTION("typeInfo") {
        REQUIRE(Variant(int(1)).typeInfo() == typeid(int(1)));
    }
}
