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

#include <yenxo/define_enum.hpp>
#include <yenxo/string_conversion.hpp>
#include <yenxo/variant_conversion.hpp>

#include <catch2/catch.hpp>

#include <sstream>

using namespace yenxo;

namespace {

YENXO_DEFINE_ENUM(
        E1_1,
        (e1, , "e_1", "e_2", "e_3", "e_4", "e_5", "e_6", "e_7", "e_8", "e_9", "e_10"));

YENXO_DEFINE_ENUM(E1, e1);

YENXO_DEFINE_ENUM(E,
                  e1,
                  (e2),
                  (e3, ),
                  (e4, 10),
                  (e5, 11, "e55"),
                  (e6, , "e66"),
                  (e7, , ),
                  e8,
                  e9,
                  e10,
                  e11,
                  e12,
                  e13,
                  e14,
                  e15,
                  e16,
                  e17,
                  e18,
                  e19,
                  e20,
                  e21,
                  e22,
                  e23,
                  e24,
                  e25,
                  e26,
                  e27,
                  e28,
                  e29,
                  e30,
                  e31,
                  e32);

} // namespace

TEST_CASE("Check YENXO_DEFINE_ENUM", "[define_enum]") {
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
    REQUIRE_THROWS_WITH(fromString<E1_1>("e_11"), "'e_11' is not of type 'E1_1'");

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
    REQUIRE_THROWS_WITH(fromVariant<E1_1>(Variant("e_11")),
                        "'e_11' is not of type 'E1_1'");

    //

    REQUIRE(toString(E1::e1) == "e1");
    REQUIRE(fromString<E1>("e1") == E1::e1);

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

    REQUIRE(toString(E::e17) == "e17");
    REQUIRE(fromString<E>("e17") == E::e17);

    REQUIRE(toString(E::e18) == "e18");
    REQUIRE(fromString<E>("e18") == E::e18);

    REQUIRE(toString(E::e19) == "e19");
    REQUIRE(fromString<E>("e19") == E::e19);

    REQUIRE(toString(E::e20) == "e20");
    REQUIRE(fromString<E>("e20") == E::e20);

    REQUIRE(toString(E::e21) == "e21");
    REQUIRE(fromString<E>("e21") == E::e21);

    REQUIRE(toString(E::e22) == "e22");
    REQUIRE(fromString<E>("e22") == E::e22);
    REQUIRE(toVariant(E::e22) == Variant("e22"));
    REQUIRE(fromVariant<E>(Variant("e22")) == E::e22);

    REQUIRE(toString(E::e23) == "e23");
    REQUIRE(fromString<E>("e23") == E::e23);
    REQUIRE(toVariant(E::e23) == Variant("e23"));
    REQUIRE(fromVariant<E>(Variant("e23")) == E::e23);

    REQUIRE(toString(E::e24) == "e24");
    REQUIRE(fromString<E>("e24") == E::e24);
    REQUIRE(toVariant(E::e24) == Variant("e24"));
    REQUIRE(fromVariant<E>(Variant("e24")) == E::e24);

    REQUIRE(toString(E::e25) == "e25");
    REQUIRE(fromString<E>("e25") == E::e25);
    REQUIRE(toVariant(E::e25) == Variant("e25"));
    REQUIRE(fromVariant<E>(Variant("e25")) == E::e25);

    REQUIRE(toString(E::e26) == "e26");
    REQUIRE(fromString<E>("e26") == E::e26);
    REQUIRE(toVariant(E::e26) == Variant("e26"));
    REQUIRE(fromVariant<E>(Variant("e26")) == E::e26);

    REQUIRE(toString(E::e27) == "e27");
    REQUIRE(fromString<E>("e27") == E::e27);
    REQUIRE(toVariant(E::e27) == Variant("e27"));
    REQUIRE(fromVariant<E>(Variant("e27")) == E::e27);

    REQUIRE(toString(E::e28) == "e28");
    REQUIRE(fromString<E>("e28") == E::e28);
    REQUIRE(toVariant(E::e28) == Variant("e28"));
    REQUIRE(fromVariant<E>(Variant("e28")) == E::e28);

    REQUIRE(toString(E::e29) == "e29");
    REQUIRE(fromString<E>("e29") == E::e29);
    REQUIRE(toVariant(E::e29) == Variant("e29"));
    REQUIRE(fromVariant<E>(Variant("e29")) == E::e29);

    REQUIRE(toString(E::e30) == "e30");
    REQUIRE(fromString<E>("e30") == E::e30);
    REQUIRE(toVariant(E::e30) == Variant("e30"));
    REQUIRE(fromVariant<E>(Variant("e30")) == E::e30);

    REQUIRE(toString(E::e31) == "e31");
    REQUIRE(fromString<E>("e31") == E::e31);
    REQUIRE(toVariant(E::e31) == Variant("e31"));
    REQUIRE(fromVariant<E>(Variant("e31")) == E::e31);

    REQUIRE(toString(E::e32) == "e32");
    REQUIRE(fromString<E>("e32") == E::e32);
    REQUIRE(toVariant(E::e32) == Variant("e32"));
    REQUIRE(fromVariant<E>(Variant("e32")) == E::e32);

    REQUIRE_THROWS_AS(fromString<E>("e156"), StringConversionError);
    REQUIRE_THROWS_WITH(fromString<E>("e156"), "'e156' is not of type 'E'");

#ifdef NDEBUG
    REQUIRE_THROWS_AS(toString(E(9)), BadEnumValue);
    REQUIRE_THROWS_WITH(toString(E(9)), "'9' is not of type 'E'");
#endif

    REQUIRE(toVariant(E::e16) == Variant("e16"));
    REQUIRE(fromVariant<E>(Variant("e16")) == E::e16);

    REQUIRE(toVariant(E::e20) == Variant("e20"));
    REQUIRE(fromVariant<E>(Variant("e20")) == E::e20);

    REQUIRE(toVariant(E::e21) == Variant("e21"));
    REQUIRE(fromVariant<E>(Variant("e21")) == E::e21);

    REQUIRE_THROWS_AS(fromVariant<E>(Variant("e156")), VariantBadType);
    REQUIRE_THROWS_WITH(fromVariant<E>(Variant("e156")), "'e156' is not of type 'E'");

    std::ostringstream os;
    os << E::e3;
    REQUIRE(os.str() == "e3");
}
