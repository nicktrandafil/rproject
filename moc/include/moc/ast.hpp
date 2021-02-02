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

#pragma once

#include <yenxo/comparison_traits.hpp>
#include <yenxo/ostream_traits.hpp>

#include <optional>
#include <string>
#include <vector>

namespace yenxo::moc {

struct Attribute {
    YENXO_EQUALITY_COMPARISON_OPERATORS(Attribute)
    YENXO_OSTREAM_OPERATOR(Attribute)

    struct NameToken {
        YENXO_EQUALITY_COMPARISON_OPERATORS(NameToken)
        YENXO_OSTREAM_OPERATOR(NameToken)

        static std::string_view typeName() noexcept {
            return "Attribute::NameToken";
        }

        std::optional<std::string> scope;
        std::string name;
    };

    static std::string_view typeName() noexcept {
        return "Attribute";
    }

    NameToken name;
    std::optional<std::string> arguments;
};

struct AttributeSpecifier {
    YENXO_EQUALITY_COMPARISON_OPERATORS(AttributeSpecifier)
    YENXO_OSTREAM_OPERATOR(AttributeSpecifier)

    static std::string_view typeName() noexcept {
        return "AttributeSpecifier";
    }

    std::optional<std::string> using_;
    std::vector<Attribute> attribute_list;
};

struct Class : trait::EqualityComparison<Class> {
    Class() = default;
    Class(char const* name, bool struct_)
            : name(name)
            , struct_(struct_) {
    }

    std::string name;
    bool struct_;
};

struct File {
    std::vector<Class> classes;
};

} // namespace yenxo::moc

BOOST_HANA_ADAPT_STRUCT(yenxo::moc::Attribute, name, arguments);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::Attribute::NameToken, scope, name);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::AttributeSpecifier, using_, attribute_list);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::Class, name, struct_);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::File, classes);
