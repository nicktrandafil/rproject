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


// tested
#include <serialize/define_enum.hpp>
#include <serialize/string_conversion.hpp>
#include <serialize/variant_conversion.hpp>

// 3rd
#include <catch2/catch.hpp>


using namespace serialize;


namespace {


DEFINE_ENUM(E1,
    e1
);


DEFINE_ENUM(E1_1,
    (e1,,"e_1", "e_2", "e_3", "e_4", "e_5", "e_6", "e_7", "e_8", "e_9", "e_10")
);


DEFINE_ENUM(E,
    e1,
    (e2),
    (e3,),
    (e4, 10),
    (e5, 11, "e55"),
    (e6,, "e66"),
    (e7,,),
    e8,
    e9,
    e10,
    e11,
    e12,
    e13,
    e14,
    e15,
    e16
);


}


TEST_CASE("Check DEFINE_ENUM", "[define_enum]") {
    REQUIRE(toString(E1::e1) == "e1");
    REQUIRE(fromString<E1>("e1") == E1::e1);

    REQUIRE(toString(E1_1::e1) == "e_1");
    REQUIRE(fromString<E1_1>("e_2") == E1_1::e1);
    REQUIRE(fromString<E1_1>("e_3") == E1_1::e1);
    REQUIRE(fromString<E1_1>("e_4") == E1_1::e1);
    REQUIRE(fromString<E1_1>("e_5") == E1_1::e1);
    REQUIRE(fromString<E1_1>("e_6") == E1_1::e1);
    REQUIRE(fromString<E1_1>("e_7") == E1_1::e1);
    REQUIRE(fromString<E1_1>("e_8") == E1_1::e1);
    REQUIRE(fromString<E1_1>("e_9") == E1_1::e1);
    REQUIRE(fromString<E1_1>("e_10") == E1_1::e1);

    REQUIRE_THROWS_AS(fromString<E1_1>("e_11"), StringConversionError);
    REQUIRE_THROWS_WITH(fromString<E1_1>("e_11"), "'e_11' is not a 'E1_1' value");

    REQUIRE(toVariant(E1_1::e1) == Variant("e_1"));
    REQUIRE(fromVariant<E1_1>(Variant("e_2")) == E1_1::e1);
    REQUIRE(fromVariant<E1_1>(Variant("e_3")) == E1_1::e1);
    REQUIRE(fromVariant<E1_1>(Variant("e_4")) == E1_1::e1);
    REQUIRE(fromVariant<E1_1>(Variant("e_5")) == E1_1::e1);
    REQUIRE(fromVariant<E1_1>(Variant("e_6")) == E1_1::e1);
    REQUIRE(fromVariant<E1_1>(Variant("e_7")) == E1_1::e1);
    REQUIRE(fromVariant<E1_1>(Variant("e_8")) == E1_1::e1);
    REQUIRE(fromVariant<E1_1>(Variant("e_9")) == E1_1::e1);
    REQUIRE(fromVariant<E1_1>(Variant("e_10")) == E1_1::e1);

    REQUIRE_THROWS_AS(fromVariant<E1_1>(Variant("e_11")), VariantBadType);
    REQUIRE_THROWS_WITH(fromVariant<E1_1>(Variant("e_11")), "'e_11' is not a 'E1_1' value");

    //

    REQUIRE(toString(E::e1) == "e1");
    REQUIRE(fromString<E>("e1") == E::e1);

    REQUIRE(toString(E::e2) == "e2");
    REQUIRE(fromString<E>("e2") == E::e2);

    REQUIRE(toString(E::e3) == "e3");
    REQUIRE(fromString<E>("e3") == E::e3);

    REQUIRE(toString(E::e4) == "e4");
    REQUIRE(fromString<E>("e4") == E::e4);
    REQUIRE(static_cast<std::underlying_type_t<E>>(E::e4) == 10);

    REQUIRE(toString(E::e5) == "e55");
    REQUIRE(fromString<E>("e55") == E::e5);

    REQUIRE(toString(E::e6) == "e66");
    REQUIRE(fromString<E>("e66") == E::e6);

    REQUIRE(toString(E::e7) == "e7");
    REQUIRE(fromString<E>("e7") == E::e7);

    REQUIRE(toString(E::e8) == "e8");
    REQUIRE(fromString<E>("e8") == E::e8);

    REQUIRE(toString(E::e9) == "e9");
    REQUIRE(fromString<E>("e9") == E::e9);

    REQUIRE(toString(E::e10) == "e10");
    REQUIRE(fromString<E>("e10") == E::e10);

    REQUIRE(toString(E::e11) == "e11");
    REQUIRE(fromString<E>("e11") == E::e11);

    REQUIRE(toString(E::e12) == "e12");
    REQUIRE(fromString<E>("e12") == E::e12);

    REQUIRE(toString(E::e13) == "e13");
    REQUIRE(fromString<E>("e13") == E::e13);

    REQUIRE(toString(E::e14) == "e14");
    REQUIRE(fromString<E>("e14") == E::e14);

    REQUIRE(toString(E::e15) == "e15");
    REQUIRE(fromString<E>("e15") == E::e15);

    REQUIRE(toString(E::e16) == "e16");
    REQUIRE(fromString<E>("e16") == E::e16);

    REQUIRE_THROWS_AS(fromString<E>("e156"), StringConversionError);
    REQUIRE_THROWS_WITH(fromString<E>("e156"), "'e156' is not a 'E' value");

#ifdef NDEBUG
    REQUIRE_THROWS_AS(toString(E(9)), BadEnumValue);
    REQUIRE_THROWS_WITH(toString(E(9)), "'9' is not a 'E' value");
#endif

    REQUIRE(toVariant(E::e16) == Variant("e16"));
    REQUIRE(fromVariant<E>(Variant("e16")) == E::e16);

    REQUIRE_THROWS_AS(fromVariant<E>(Variant("e156")), VariantBadType);
    REQUIRE_THROWS_WITH(fromVariant<E>(Variant("e156")), "'e156' is not a 'E' value");
}
