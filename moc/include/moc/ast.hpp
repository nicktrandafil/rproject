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
#include <yenxo/define_enum.hpp>
#include <yenxo/ostream_traits.hpp>

#include <type_safe/strong_typedef.hpp>

#include <optional>
#include <string>
#include <variant>
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

DEFINE_ENUM(ClassKey, class_, struct_, union_);
DEFINE_ENUM(ClassVirtSpecifier, final_);
DEFINE_ENUM(AccessSpecifier, public_, protected_, private_);

struct Empty {
    YENXO_EQUALITY_COMPARISON_OPERATORS(Empty)
    YENXO_OSTREAM_OPERATOR(Empty)

    static std::string_view typeName() noexcept {
        return "Empty";
    }
};

struct Identifier
        : type_safe::strong_typedef<Identifier, std::string>
        , type_safe::strong_typedef_op::equality_comparison<Identifier> {
    using strong_typedef::strong_typedef;

    inline friend std::ostream& operator<<(std::ostream& os, Identifier const& val) {
        return os << static_cast<type_safe::underlying_type<Identifier>>(val);
    }
};

struct NestedNameSpecifier {
    YENXO_EQUALITY_COMPARISON_OPERATORS(NestedNameSpecifier)
    YENXO_OSTREAM_OPERATOR(NestedNameSpecifier)

    static std::string_view typeName() noexcept {
        return "NestedNameSpecifier";
    }

    std::vector<Identifier> parcels;
};

struct ClassOrDecltype {
    YENXO_EQUALITY_COMPARISON_OPERATORS(ClassOrDecltype)
    YENXO_OSTREAM_OPERATOR(ClassOrDecltype)

    static std::string_view typeName() noexcept {
        return "ClassOrDecltype";
    }

    std::optional<NestedNameSpecifier> nested_name;
    Identifier type_name;
};

struct Class {
    YENXO_EQUALITY_COMPARISON_OPERATORS(Class)
    YENXO_OSTREAM_OPERATOR(Class)

    static std::string_view typeName() noexcept {
        return "Class";
    }

    struct HeadName {
        YENXO_EQUALITY_COMPARISON_OPERATORS(HeadName)
        YENXO_OSTREAM_OPERATOR(HeadName)

        static std::string_view typeName() noexcept {
            return "HeadName";
        }

        std::optional<NestedNameSpecifier> nested_name;
        Identifier class_name;
    };

    struct BaseSpecifier {
        YENXO_EQUALITY_COMPARISON_OPERATORS(BaseSpecifier)
        YENXO_OSTREAM_OPERATOR(BaseSpecifier)

        static std::string_view typeName() noexcept {
            return "BaseSpecifier";
        }

        std::vector<AttributeSpecifier> attributes;
        bool virtual_{false};
        std::optional<AccessSpecifier> access_specifier;
        ClassOrDecltype class_or_decltype;
    };

    struct BaseClause {
        YENXO_EQUALITY_COMPARISON_OPERATORS(BaseClause)
        YENXO_OSTREAM_OPERATOR(BaseClause)

        static std::string_view typeName() noexcept {
            return "BaseClause";
        }

        std::vector<BaseSpecifier> base_specifiers;
    };

    struct Head {
        YENXO_EQUALITY_COMPARISON_OPERATORS(Head)
        YENXO_OSTREAM_OPERATOR(Head)

        static std::string_view typeName() noexcept {
            return "Head";
        }

        ClassKey class_key;
        std::vector<AttributeSpecifier> attributes;
        std::optional<HeadName> head_name;
        std::optional<ClassVirtSpecifier> virt_specifier;
        std::optional<BaseClause> base_clause;
    };

    struct MemberSpecification {
        YENXO_EQUALITY_COMPARISON_OPERATORS(MemberSpecification)

        static std::string_view typeName() noexcept {
            return "MemberSpecification";
        }

        inline friend std::ostream& operator<<(std::ostream& os,
                                               MemberSpecification const& val) {
            return std::visit([&os](auto const& x) -> decltype(auto) { return os << x; },
                              val.variants);
        }

        std::variant<Empty> variants;
    };

    Head head;
    MemberSpecification member_specification;
};

struct File {
    std::vector<Class> classes;
};

} // namespace yenxo::moc

BOOST_HANA_ADAPT_STRUCT(yenxo::moc::Attribute, name, arguments);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::Attribute::NameToken, scope, name);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::AttributeSpecifier, using_, attribute_list);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::Class::HeadName, nested_name, class_name);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::Class::BaseSpecifier,
                        attributes,
                        virtual_,
                        access_specifier,
                        class_or_decltype);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::Class::BaseClause, base_specifiers);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::Class::Head,
                        class_key,
                        attributes,
                        head_name,
                        virt_specifier,
                        base_clause);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::Class::MemberSpecification, variants);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::Class, head, member_specification);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::NestedNameSpecifier, parcels);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::Empty);
BOOST_HANA_ADAPT_STRUCT(yenxo::moc::ClassOrDecltype, nested_name, type_name);
