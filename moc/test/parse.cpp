/*
  MIT License

  Copyright (c) 2021 Nicolai Trandafil

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

#include "moc/parse.hpp"

#include "moc/parse-inl.h"

#include <catch2/catch.hpp>

#include <data/attribute-gen.h>
#include <data/class-gen.h>
#include <data/identifier-gen.h>
#include <data/literal-gen.h>

using namespace std;
using namespace yenxo::moc;

namespace {

std::string_view view(uint8_t* a, size_t s) {
    return string_view(reinterpret_cast<char const*>(const_cast<unsigned char const*>(a)),
                       s);
}

} // namespace

TEST_CASE("comments") {
    Grammar<std::string_view::iterator, qi::space_type> const grammar;
    std::string actual;

    SECTION("line") {
        auto const line = grammar.line_comment;
        constexpr auto input = R"(
            // a comment
        )"sv;
        auto const ok =
                qi::phrase_parse(begin(input), end(input), line, qi::space, actual);
        REQUIRE(ok);
        REQUIRE(actual == " a comment");
    }

    SECTION("multi-line") {
        auto const line = grammar.multi_line_comment;
        constexpr auto input = R"(
            /* a comment
               b comment */
        )"sv;
        auto const ok =
                qi::phrase_parse(begin(input), end(input), line, qi::space, actual);
        REQUIRE(ok);
        REQUIRE(actual == R"( a comment
               b comment )");
    }
}

namespace {

template <class T, class A>
bool parse(T& actual, A const& attr, uint8_t* data, size_t size, std::string_view case_) {
    auto const input = view(data, size);
    auto const _00 = input.find(case_);
    REQUIRE(_00 != std::string_view::npos);
    return qi::phrase_parse(
            std::next(begin(input), static_cast<std::ptrdiff_t>(_00 + case_.size())),
            end(input),
            attr,
            qi::space,
            actual);
}

} // namespace

TEST_CASE("identifier") {
    Grammar<std::string_view::iterator, qi::space_type> const grammar;
    auto const identifier = grammar.identifier;
    std::string actual;

    SECTION("upper case, lower case, _, digit") {
        REQUIRE(parse(actual,
                      identifier,
                      test_data_identifier_cpp,
                      test_data_identifier_cpp_len,
                      "/*0*/"));
        REQUIRE(actual == "Ab_c_1");
    }

    SECTION("universal character name") {
        REQUIRE(parse(actual,
                      identifier,
                      test_data_identifier_cpp,
                      test_data_identifier_cpp_len,
                      "/*1*/"));
        REQUIRE(actual == "\\u90000000");
    }

    SECTION("wide universal character name") {
        REQUIRE(parse(actual,
                      identifier,
                      test_data_identifier_cpp,
                      test_data_identifier_cpp_len,
                      "/*2*/"));
        REQUIRE(actual == "\\U0000900090000000");
    }

    SECTION("two universal character names") {
        REQUIRE(parse(actual,
                      identifier,
                      test_data_identifier_cpp,
                      test_data_identifier_cpp_len,
                      "/*3*/"));
        REQUIRE(actual == "\\u90000000a1\\u90000000");
    }
}

TEST_CASE("attribute") {
    Grammar<std::string_view::iterator, qi::space_type> const grammar;
    auto const attribute_specifier = grammar.attribute_specifier;
    AttributeSpecifier actual;

    SECTION("simple") {
        REQUIRE(parse(actual,
                      attribute_specifier,
                      test_data_attribute_cpp,
                      test_data_attribute_cpp_len,
                      "/*0*/"));
        REQUIRE(actual == AttributeSpecifier{{}, {Attribute{{{}, "deprecated"}, {}}}});
    }

    SECTION("default scope specifier") {
        REQUIRE(parse(actual,
                      attribute_specifier,
                      test_data_attribute_cpp,
                      test_data_attribute_cpp_len,
                      "/*1*/"));
        REQUIRE(actual == AttributeSpecifier{{"foo"}, {Attribute{{{}, "boo"}, {}}}});
    }

    SECTION("scoped attribute") {
        REQUIRE(parse(actual,
                      attribute_specifier,
                      test_data_attribute_cpp,
                      test_data_attribute_cpp_len,
                      "/*2*/"));
        REQUIRE(actual == AttributeSpecifier{{}, {Attribute{{{"foo"}, "boo"}, {}}}});
    }

    SECTION("attribute with one string parameter containing unbalanced brackets") {
        REQUIRE(parse(actual,
                      attribute_specifier,
                      test_data_attribute_cpp,
                      test_data_attribute_cpp_len,
                      "/*3*/"));
        REQUIRE(actual == AttributeSpecifier{{}, {Attribute{{{}, "foo"}, {"\"]]\""}}}});
    }
    SECTION("attribute with a string parameter, operator plus and a user defined "
            "literal") {
        REQUIRE(parse(actual,
                      attribute_specifier,
                      test_data_attribute_cpp,
                      test_data_attribute_cpp_len,
                      "/*4*/"));
        REQUIRE(actual
                == AttributeSpecifier{{}, {Attribute{{{}, "foo"}, {"\"]]\" + (11_f)"}}}});
    }
    SECTION("attribute with a just an identifier parameter") {
        REQUIRE(parse(actual,
                      attribute_specifier,
                      test_data_attribute_cpp,
                      test_data_attribute_cpp_len,
                      "/*5*/"));
        REQUIRE(actual == AttributeSpecifier{{}, {Attribute{{{}, "foo"}, {"x3"}}}});
    }
    SECTION("attribute with balanced brackets and a integer user defined parameter") {
        REQUIRE(parse(actual,
                      attribute_specifier,
                      test_data_attribute_cpp,
                      test_data_attribute_cpp_len,
                      "/*6*/"));
        REQUIRE(actual
                == AttributeSpecifier{{}, {Attribute{{{}, "foo"}, {"[x3 (10_z)]"}}}});
    }
    SECTION("attribute with comma delimited parameters") {
        REQUIRE(parse(actual,
                      attribute_specifier,
                      test_data_attribute_cpp,
                      test_data_attribute_cpp_len,
                      "/*7*/"));
        REQUIRE(actual
                == AttributeSpecifier{
                        {}, {Attribute{{{}, "foo"}, {}}, Attribute{{{}, "boo"}, {}}}});
    }
    SECTION("attribute with comma delimited parameters, strip") {
        REQUIRE(parse(actual,
                      attribute_specifier,
                      test_data_attribute_cpp,
                      test_data_attribute_cpp_len,
                      "/*8*/"));
        REQUIRE(actual == AttributeSpecifier{{}, {Attribute{{{}, "foo"}, {}}}});
    }
    SECTION("empty attribute specifier") {
        REQUIRE(parse(actual,
                      attribute_specifier,
                      test_data_attribute_cpp,
                      test_data_attribute_cpp_len,
                      "/*9*/"));
        REQUIRE(actual == AttributeSpecifier{{}, {}});
    }
    SECTION("attribute parameters separated with space") {
        REQUIRE(parse(actual,
                      attribute_specifier,
                      test_data_attribute_cpp,
                      test_data_attribute_cpp_len,
                      "/*10*/"));
        REQUIRE(actual
                == AttributeSpecifier{
                        {}, {Attribute{Attribute::NameToken{{}, "foo"}, {"boo doo"}}}});
    }
}

TEST_CASE("literal") {
    Grammar<std::string_view::iterator, qi::space_type> const grammar;
    auto const literal = grammar.literal;
    std::string actual;

    SECTION("integer") {
        std::string actual;
        SECTION("binary") {
            std::string actual;
            SECTION("simple") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*0*/"));
                REQUIRE(actual == "0b0101");
            }
            SECTION("use separator") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*1*/"));
                REQUIRE(actual == "0B0101'01");
            }
        }
        SECTION("u") {
            REQUIRE(parse(actual,
                          literal,
                          test_data_literal_cpp,
                          test_data_literal_cpp_len,
                          "/*2*/"));
            REQUIRE(actual == "0b0u");
        }
        SECTION("Ul") {
            REQUIRE(parse(actual,
                          literal,
                          test_data_literal_cpp,
                          test_data_literal_cpp_len,
                          "/*3*/"));
            REQUIRE(actual == "0b0UL");
        }
        SECTION("Ull") {
            REQUIRE(parse(actual,
                          literal,
                          test_data_literal_cpp,
                          test_data_literal_cpp_len,
                          "/*4*/"));
            REQUIRE(actual == "0b0Ull");
        }
        SECTION("octal") {
            std::string actual;
            SECTION("simple") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*6*/"));
                REQUIRE(actual == "07");
            }
            SECTION("use separator") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*7*/"));
                REQUIRE(actual == "0'7");
            }
        }
        SECTION("decimal") {
            std::string actual;
            SECTION("simple") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*8*/"));
                REQUIRE(actual == "9");
            }
            SECTION("use separator") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*9*/"));
                REQUIRE(actual == "9'0");
            }
        }
        SECTION("hexadecimal") {
            std::string actual;
            SECTION("simple") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*10*/"));
                REQUIRE(actual == "0X0");
            }
            SECTION("use separator") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*11*/"));
                REQUIRE(actual == "0X0'Ff");
            }
        }
    }

    SECTION("char") {
        std::string actual;
        SECTION("simple") {
            REQUIRE(parse(actual,
                          literal,
                          test_data_literal_cpp,
                          test_data_literal_cpp_len,
                          "/*12*/"));
            REQUIRE(actual == "'c'");
        }
        SECTION("multi-char") {
            REQUIRE(parse(actual,
                          literal,
                          test_data_literal_cpp,
                          test_data_literal_cpp_len,
                          "/*13*/"));
            REQUIRE(actual == "'cc'");
        }
        SECTION("simple-escape") {
            REQUIRE(parse(actual,
                          literal,
                          test_data_literal_cpp,
                          test_data_literal_cpp_len,
                          "/*14*/"));
            REQUIRE(actual == "'\\?'");
        }
        SECTION("octal-escape") {
            REQUIRE(parse(actual,
                          literal,
                          test_data_literal_cpp,
                          test_data_literal_cpp_len,
                          "/*15*/"));
            REQUIRE(actual == "'\\071'");
        }
        SECTION("hexadecimal-escape") {
            REQUIRE(parse(actual,
                          literal,
                          test_data_literal_cpp,
                          test_data_literal_cpp_len,
                          "/*16*/"));
            REQUIRE(actual == "'\\xf1'");
        }
        SECTION("conditional-escape") {
            REQUIRE(parse(actual,
                          literal,
                          test_data_literal_cpp,
                          test_data_literal_cpp_len,
                          "/*17*/"));
            REQUIRE(actual == "'\\l'");
        }
    }

    SECTION("floating-point") {
        SECTION("decimal") {
            std::string actual;
            SECTION("fractional-constant") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*18*/"));
                REQUIRE(actual == "0.0");
            }
            SECTION("fractional-constant2") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*19*/"));
                REQUIRE(actual == "0'1.");
            }
            SECTION("fractional-constant3") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*20*/"));
                REQUIRE(actual == ".0'1");
            }
            SECTION("exponent-part") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*21*/"));
                REQUIRE(actual == "0.e0");
            }
            SECTION("exponent-part") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*22*/"));
                REQUIRE(actual == "0.E+1");
            }
            SECTION("no-fractional-constant") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*24*/"));
                REQUIRE(actual == "0E+1F");
            }
        }
        SECTION("hexadecimal") {
            std::string actual;
            SECTION("hexadecimal-fractional-constant") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*25*/"));
                REQUIRE(actual == "0x.0'1p1f");
            }
        }
    }

    SECTION("string") {
        SECTION("regular") {
            std::string actual;
            SECTION("simple") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*26*/"));
                REQUIRE(actual == "u8\"foo\"");
            }
            SECTION("simple-escape") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*27*/"));
                REQUIRE(actual == "\"\\\"\"");
            }
            // should be covered by c_char_sequence
        }
        SECTION("raw") {
            std::string actual;
            SECTION("simple") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*28*/"));
                REQUIRE(actual == R"x(R"(")")x");
            }
            SECTION("complex") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*29*/"));
                REQUIRE(actual == R"x(R"y(y)y")x");
            }
            SECTION("complex2") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*30*/"));
                REQUIRE(actual == R"x(R"y(y)y)y")x");
            }
        }
    }

    SECTION("boolean") {
        REQUIRE(parse(actual,
                      literal,
                      test_data_literal_cpp,
                      test_data_literal_cpp_len,
                      "/*31*/"));
        REQUIRE(actual == "true");
    }

    SECTION("pointer") {
        std::string actual;
        REQUIRE(parse(actual,
                      literal,
                      test_data_literal_cpp,
                      test_data_literal_cpp_len,
                      "/*32*/"));
        REQUIRE(actual == "nullptr");
    }

    SECTION("user-defined-literal") {
        SECTION("integer") {
            std::string actual;
            SECTION("decimal") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*33*/"));
                REQUIRE(actual == "3_x");
            }
            SECTION("octal") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*34*/"));
                REQUIRE(actual == "03_x");
            }
            SECTION("hexadecimal") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*35*/"));
                REQUIRE(actual == "0x3_x");
            }
            SECTION("binary") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*36*/"));
                REQUIRE(actual == "0b1_x");
            }
        }
        SECTION("floating-point") {
            std::string actual;
            SECTION("fractional-constant") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*38*/"));
                REQUIRE(actual == "0.1e+2_x");
            }
            SECTION("digit-sequence") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*39*/"));
                REQUIRE(actual == "1'1e+2_x");
            }
            SECTION("hexadecimal-fractional-constant") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*40*/"));
                REQUIRE(actual == "0xff.0p+2_x");
            }
            SECTION("hexadecimal-digit-sequence") {
                REQUIRE(parse(actual,
                              literal,
                              test_data_literal_cpp,
                              test_data_literal_cpp_len,
                              "/*41*/"));
                REQUIRE(actual == "0xffp+2_x");
            }
        }
        SECTION("string") {
            REQUIRE(parse(actual,
                          literal,
                          test_data_literal_cpp,
                          test_data_literal_cpp_len,
                          "/*42*/"));
            REQUIRE(actual == "\"foo\"_y");
        }
        SECTION("character") {
            REQUIRE(parse(actual,
                          literal,
                          test_data_literal_cpp,
                          test_data_literal_cpp_len,
                          "/*43*/"));
            REQUIRE(actual == "'f'_z");
        }
    }
}

TEST_CASE("class") {
    Grammar<std::string_view::iterator, qi::space_type> const grammar;
    auto const class_ = grammar.class_specifier;
    Class actual;
    SECTION("class") {
        REQUIRE(parse(
                actual, class_, test_data_class_cpp, test_data_class_cpp_len, "/*0*/"));
        REQUIRE(actual.head.class_key == ClassKey::class_);
    }
    SECTION("struct") {
        REQUIRE(parse(
                actual, class_, test_data_class_cpp, test_data_class_cpp_len, "/*1*/"));
        REQUIRE(actual.head.class_key == ClassKey::struct_);
    }
    SECTION("union") {
        REQUIRE(parse(
                actual, class_, test_data_class_cpp, test_data_class_cpp_len, "/*2*/"));
        REQUIRE(actual.head.class_key == ClassKey::union_);
    }
    SECTION("attributes") {
        REQUIRE(parse(
                actual, class_, test_data_class_cpp, test_data_class_cpp_len, "/*3*/"));
        REQUIRE(actual.head.attributes
                == std::vector<AttributeSpecifier>{
                        AttributeSpecifier{{}, {Attribute{{{}, "a"}, {}}}},
                        AttributeSpecifier{{}, {Attribute{{{}, "b"}, {}}}},
                });
    }
    SECTION("nested-name-specifier") {
        REQUIRE(parse(
                actual, class_, test_data_class_cpp, test_data_class_cpp_len, "/*4*/"));
        REQUIRE(actual.head.head_name
                == Class::HeadName{NestedNameSpecifier{{
                                           Identifier{"X"},
                                           Identifier{"Foo"},
                                   }},
                                   Identifier{"Boo"}});
    }

    SECTION("virt-specifier") {
        REQUIRE(parse(
                actual, class_, test_data_class_cpp, test_data_class_cpp_len, "/*5*/"));
        REQUIRE(actual.head.virt_specifier == ClassVirtSpecifier::final_);
    }

    SECTION("base-clause") {
        REQUIRE(parse(
                actual, class_, test_data_class_cpp, test_data_class_cpp_len, "/*6*/"));
        REQUIRE(actual.head.base_clause
                == Class::BaseClause{{
                        Class::BaseSpecifier{
                                {}, false, {}, ClassOrDecltype{{}, Identifier{"A"}}},
                        Class::BaseSpecifier{
                                {},
                                false,
                                AccessSpecifier::protected_,
                                ClassOrDecltype{NestedNameSpecifier{{Identifier{"X"},
                                                                     Identifier{"Foo"}}},
                                                Identifier{"Boo"}}},
                        Class::BaseSpecifier{
                                {}, true, {}, ClassOrDecltype{{}, Identifier{"A1"}}},
                        Class::BaseSpecifier{{},
                                             true,
                                             AccessSpecifier::protected_,
                                             ClassOrDecltype{{}, Identifier{"A2"}}},
                        Class::BaseSpecifier{{},
                                             true,
                                             AccessSpecifier::private_,
                                             ClassOrDecltype{{}, Identifier{"A3"}}},
                }});
    }
}
