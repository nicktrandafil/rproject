#include <yenxo/define_enum.hpp>
#include <yenxo/string_conversion.hpp>

#include <boost/hana/assert.hpp>

using namespace yenxo;

YENXO_DEFINE_ENUM(MyEnum,
                  val0,
                  (val1),
                  (val2, 4),
                  (val3, , "string_repr"),
                  (val4, 9, "string_repr2"),
                  (val5, , "s5", "s6"));

int main() {
    // to string conversion
    BOOST_HANA_RUNTIME_CHECK(toString(MyEnum::val0) == "val0");
    BOOST_HANA_RUNTIME_CHECK(toString(MyEnum::val3) == "string_repr");

    // from string conversion
    BOOST_HANA_RUNTIME_CHECK(fromString<MyEnum>("val0") == MyEnum::val0);
    BOOST_HANA_RUNTIME_CHECK(fromString<MyEnum>("s5") == MyEnum::val5);
    BOOST_HANA_RUNTIME_CHECK(fromString<MyEnum>("s6") == MyEnum::val5);
}
