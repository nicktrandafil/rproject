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

#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>

#include <moc/ast.hpp>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

BOOST_FUSION_ADAPT_STRUCT(yenxo::moc::Attribute::NameToken, scope, name)
BOOST_FUSION_ADAPT_STRUCT(yenxo::moc::Attribute, name, arguments)
BOOST_FUSION_ADAPT_STRUCT(yenxo::moc::AttributeSpecifier, using_, attribute_list)
BOOST_FUSION_ADAPT_STRUCT(yenxo::moc::Class, head, member_specification)
BOOST_FUSION_ADAPT_STRUCT(yenxo::moc::Class::Head,
                          class_key,
                          attributes,
                          head_name,
                          virt_specifier,
                          base_clause)
BOOST_FUSION_ADAPT_STRUCT(yenxo::moc::Class::HeadName, nested_name, class_name)
BOOST_FUSION_ADAPT_STRUCT(yenxo::moc::Class::BaseClause, base_specifiers)
BOOST_FUSION_ADAPT_STRUCT(yenxo::moc::Class::BaseSpecifier,
                          attributes,
                          virtual_,
                          access_specifier,
                          class_or_decltype)
BOOST_FUSION_ADAPT_STRUCT(yenxo::moc::NestedNameSpecifier, parcels)
BOOST_FUSION_ADAPT_STRUCT(yenxo::moc::File, classes)
BOOST_FUSION_ADAPT_STRUCT(yenxo::moc::ClassOrDecltype, nested_name, type_name)

// TODO Remove.
namespace std {

template <class T>
std::ostream& operator<<(std::ostream& os, optional<T> const& x) {
    return os << *x;
}

} // namespace std

namespace yenxo::moc {
namespace {

template <class It, typename Skip>
struct Grammar : qi::grammar<It, File(), Skip> {
    Grammar()
            : Grammar::base_type(file, "file") {
        using phx::at_c;
        using phx::begin;
        using phx::construct;
        using phx::end;
        using phx::insert;
        using phx::push_back;
        using phx::val;
        using namespace qi;

        // clang-format off
        line_comment       = lit("//") >> no_skip[*(char_ - eol - eoi)] >> (eol | eoi);
        multi_line_comment = lit("/*") >> no_skip[*(char_ - lit("*/"))] >> lit("*/");

        attribute_specifier       =    lit("[") >> lit("[")
                                    >> -attribute_using_prefix[at_c<0>(_val) = _1]
                                    >> -attribute_list[at_c<1>(_val) = _1]
                                    >> lit("]") >> lit("]")
        ;
        attribute_using_prefix    = lit("using") >> omit[no_skip[space]] >> attribute_namespace >> lit(":");
        attribute_namespace       = identifier.alias();
        attribute_list            = (attribute % lit(",")) >> -lit(",");
        attribute                 = attribute_token >> -attribute_argument_clause;
        attribute_token           = attribute_scoped_token[_val = _1] | identifier[at_c<1>(_val) = _1];
        attribute_scoped_token    = attribute_namespace >> lit("::") >> identifier;
        attribute_argument_clause = lit("(") >> no_skip[-balanced_token_seq] >> lit(")");
        balanced_token_seq        = +balanced_token;
        balanced_token            =    (char_("(") >> balanced_token_seq >> char_(")"))
                                     | (char_("[") >> balanced_token_seq >> char_("]"))
                                     | (char_("{") >> balanced_token_seq >> char_("}"))
                                     | (token - "(" - ")" - "[" - "]" - "{" - "}")
                                     | space
        ;

        identifier               = lexeme[identifier_nondigit >> *(identifier_nondigit | as_string[digit])];
        identifier_nondigit      = nondigit | universal_character_name;
        nondigit                 = alpha | char_('_');
        universal_character_name =   (string("\\u") >> repeat(8)[xdigit])
                                   | (string("\\U") >> repeat(16)[xdigit]);

        token = identifier | literal | operator_or_punctuator;

        literal =   hold[lexeme[user_defined_literal]]
                  | hold[lexeme[floating_point_literal]]
                  | hold[lexeme[character_literal]]
                  | lexeme[integer_literal]
                  | lexeme[string_literal]
                  | lexeme[boolean_literal]
                  | lexeme[pointer_literal]
        ;

        integer_literal  =   hold[(binary_literal >> -integer_suffix)]
                           | hold[(octal_literal >> -integer_suffix)]
                           | (decimal_literal >> -integer_suffix)
                           | (hexadecimal_literal >> -integer_suffix)
        ;
        integer_suffix   =   hold[unsigned_suffix >> long_long_suffix]
                           | hold[unsigned_suffix >> long_suffix]
                           | hold[long_long_suffix >> unsigned_suffix]
                           | hold[long_suffix >> unsigned_suffix]
                           | (unsigned_suffix | long_long_suffix | long_long_suffix)
        ;
        unsigned_suffix  = char_("u") | char_("U");
        long_suffix      = char_("l") | char_("L");
        long_long_suffix = string("ll") | string("LL");

        binary_literal = (string("0b") | string("0B")) >> binary_digit >> *(-char_("'") >> binary_digit);
        binary_digit   = char_("0") | char_("1");

        octal_literal = char_("0") >> +(-char_("'") >> octal_digit);
        octal_digit   =   char_("0") | char_("1") | char_("2") | char_("3") | char_("4") | char_("5") | char_("6")
                        | char_("7")
        ;

        decimal_literal = (digit - "0") >> *(-char_("'") >> digit);

        hexadecimal_literal = hexadecimal_prefix >> xdigit >> *(-char_("'") >> xdigit);
        hexadecimal_prefix  = string("0x") | string("0X");

        encoding_prefix             = string("u8") | char_("u") | char_("U") | char_("L");
        character_literal           = -encoding_prefix >> char_("'") >> c_char_sequence >> char_("'");
        basic_c_char                = char_ - "'" - "\\" - "\n";
        c_char_sequence             = +(basic_c_char | escape_sequence);
        escape_sequence             =   hold[simple_escape_sequence]
                                      | hold[numeric_escape_sequence]
                                      | conditional_escape_sequence
        ;
        simple_escape_sequence      = char_("\\") >> simple_sequence_char;
        simple_sequence_char        =   char_('\'')
                                      | char_("\"")
                                      | char_("?")
                                      | char_("\\")
                                      | char_("a")
                                      | char_("b")
                                      | char_("f")
                                      | char_("n")
                                      | char_("r")
                                      | char_("t")
                                      | char_("v")
        ;
        numeric_escape_sequence     = hold[octal_escape_sequence] | hold[hexadecimal_escape_sequence];
        octal_escape_sequence       = char_("\\") >> repeat(1, 3)[octal_digit];
        hexadecimal_escape_sequence = string("\\x") >> +xdigit;
        conditional_escape_sequence = char_("\\") >> (char_ - octal_digit - simple_sequence_char - 'u' - 'U' - 'x');

        floating_point_literal         =   hold[decimal_floating_point_literal]
                                         | hexadecimal_floating_point_literal
        ;

        decimal_floating_point_literal =   hold[   fractional_constant
                                                >> -exponent_part
                                                >> -floating_point_suffix]
                                         | (   digit_sequence
                                            >> exponent_part
                                            >> -floating_point_suffix)
        ;
        fractional_constant            =   hold[-digit_sequence >> char_(".") >> digit_sequence]
                                         | (digit_sequence >> char_("."))
        ;
        digit_sequence                 = digit >> *(-char_("'") >> digit);
        exponent_part                  = (char_("e") | char_("E")) >> -sign >> digit_sequence;

        sign = char_("+") | char_("-");

        floating_point_suffix              = char_("f") | char_("l") | char_("F") | char_("L");
        hexadecimal_floating_point_literal =    hexadecimal_prefix
                                             >> hexadecimal_fractional_constant
                                             >> binary_exponent_part
                                             >> -floating_point_suffix
        ;
        hexadecimal_fractional_constant    =   hold[   -hexadecimal_digit_sequence
                                                    >> char_(".")
                                                    >> hexadecimal_digit_sequence]
                                             | (hexadecimal_digit_sequence >> char_("."))
        ;
        hexadecimal_digit_sequence         = xdigit >> *(-char_("'") >> xdigit);
        binary_exponent_part               = (char_("p") | char_("P")) >> -sign >> digit_sequence;

        string_literal       =   hold[-encoding_prefix >> char_("\"") >> -s_char_sequence >> char_("\"")]
                               | (-encoding_prefix >> char_("R") >> raw_string)
        ;
        s_char_sequence      = +s_char;
        s_char               =   hold[basic_s_char]
                               | hold[escape_sequence]
                               | universal_character_name
        ;
        basic_s_char         = char_ - "\"" - "\\" - "\n";
        raw_string           =    char_("\"")            [push_back(_val, _1)]
                               >> -d_char_sequence       [insert(_val, end(_val), begin(_1), end(_1)), _a = _1]
                               >> char_("(")             [push_back(_val, _1)]
                               >> -r_char_sequence(_a)   [insert(_val, end(_val), begin(_1), end(_1))]
                               >> char_(")")             [push_back(_val, _1)]
                               >> end_d_char_sequence(_a)[insert(_val, end(_val), begin(_1), end(_1))]
                               >> char_("\"")            [push_back(_val, _1)]
        ;
        r_char_sequence      = +r_char(_r1);
        r_char               = char_ - (")" >> lit(_r1) >> "\"");
        d_char_sequence      = +d_char;
        d_char               = char_ - (space | "(" | ")" | "\\");
        end_d_char_sequence  = string(_r1);

        boolean_literal = string("true") | string("false");
        pointer_literal = string("nullptr");

        user_defined_literal                =   hold[user_defined_floating_point_literal]
                                              | user_defined_integer_literal
                                              | user_defined_string_literal
                                              | user_defined_character_literal
        ;
        user_defined_integer_literal        =   hold[binary_literal >> (ud_suffix - integer_suffix)]
                                              | hold[octal_literal >> (ud_suffix - integer_suffix)]
                                              | (decimal_literal >> (ud_suffix - integer_suffix))
                                              | (hexadecimal_literal >> (ud_suffix - integer_suffix))
        ;
        ud_suffix                           = identifier.alias();
        user_defined_floating_point_literal =   hold[fractional_constant >> -exponent_part >> (ud_suffix - floating_point_suffix)]
                                              | hold[digit_sequence >> exponent_part >> (ud_suffix - floating_point_suffix)]
                                              | hold[   hexadecimal_prefix
                                                     >> hexadecimal_fractional_constant
                                                     >> binary_exponent_part
                                                     >> (ud_suffix - floating_point_suffix)
                                                ]
                                              | (   hexadecimal_prefix
                                                 >> hexadecimal_digit_sequence
                                                 >> binary_exponent_part
                                                 >> (ud_suffix - floating_point_suffix)
                                                )
        ;
        user_defined_string_literal         = string_literal >> ud_suffix;
        user_defined_character_literal      = character_literal >> ud_suffix;

        operator_or_punctuator =
                string("{")|  string("}")|  string("[")|  string("]")|  string("(")|  string(")")|
                string("<:")| string(":>")| string("<%")| string("%>")| string(";")|  string(":")|   string("...")|
                string("?")|  string("::")| string(".")|  string(".*")| string("->")| string("->*")| string("~")|
                string("!")|  string("+")|  string("-")|  string("*")|  string("/")|  string("%")|   string("^")|   string("&")|  string("|")|
                string("=")|  string("+=")| string("-=")| string("*=")| string("/=")| string("%=")|  string("^=")|  string("&=")| string("|=")|
                string("==")| string("!=")| string("<")|  string(">")|  string("<=")| string(">=")|  string("<=>")| string("&&")| string("||")|
                string("<<")|     string(">>")|    string("<<=")|    string(">>=")|   string("++")|       string("--")|       string(",")|
                string("and")|    string("or")|    string("xor")|    string("not")|   string("bitand")|   string("bitor")|    string("compl")|
                string("and_eq")| string("or_eq")| string("xor_eq")| string("not_eq")
        ;

        class_specifier            = class_head >> "{" >> class_member_specification >> "}";
        class_member_specification = eps[_val = construct<Class::MemberSpecification>()];
        class_head                 = class_key
                                     >> *attribute_specifier
                                     >> class_head_name
                                     >> -class_virt_specifier
                                     >> -class_base_clause
        ;
        class_key                  =   string("class")[_val = val(ClassKey::class_)]
                                     | string("struct")[_val = val(ClassKey::struct_)]
                                     | string("union")[_val = val(ClassKey::union_)]
        ;
        class_virt_specifier       = lit("final")[_val = val(ClassVirtSpecifier::final_)];
        class_head_name            = -nested_name_specifier >> class_name;
        class_name                 = identifier.alias();
        nested_parcel              = identifier.alias();
        type_name                  = identifier.alias();
        nested_name_specifier      = hold["::"] || +(nested_parcel >> "::")[push_back(at_c<0>(_val), _1)];
        class_base_clause		   = ":" >> (class_base_specifier % ",")[at_c<0>(_val) = _1];
        class_base_specifier       =    (*attribute_specifier)[at_c<0>(_val) = _1]
                                     >> -(
                                            lit("virtual")  [at_c<1>(_val) = val(true)]
                                          ^ access_specifier[at_c<2>(_val) = _1]
                                         )
                                     >> class_or_decltype[at_c<3>(_val) = _1]
        ;
        class_or_decltype          = -nested_name_specifier >> type_name;
        access_specifier           =   string("public")   [_val = val(AccessSpecifier::public_)]
                                     | string("protected")[_val = val(AccessSpecifier::protected_)]
                                     | string("private")  [_val = val(AccessSpecifier::private_)]
        ;
        // clang-format on

        line_comment.name("Line comment");
        multi_line_comment.name("Multi line comment");
        file.name("File");
        class_specifier.name("Class");
        attribute_specifier.name("attribute-specifier");
        attribute_using_prefix.name("attribute-using-prefix");
        attribute_namespace.name("attribute-namespace");
        attribute_list.name("attribute-list");
        attribute.name("attribute");
        attribute_token.name("attribute-token");
        attribute_scoped_token.name("attribute-scoped-token");
        attribute_argument_clause.name("attribute-argument-clause");
        token.name("token");
        balanced_token_seq.name("balanced-token-seq");
        balanced_token.name("balanced-token");
        identifier.name("identifier");
        identifier_nondigit.name("identifier-nondigit");
        nondigit.name("nondigit");
        universal_character_name.name("universal-character-name");
        literal.name("literal");
        integer_literal.name("integer-literal");
        binary_literal.name("binary-literal");
        binary_digit.name("binary-digit");
        octal_literal.name("octal-literal");
        octal_digit.name("octal-digit");
        decimal_literal.name("decimal-literal");
        hexadecimal_literal.name("hexadecimal-literal");
        raw_string.name("raw-string");
        d_char_sequence.name("d-char-sequence");
        end_d_char_sequence.name("end-d-char-sequence");
        r_char_sequence.name("r-char-sequence");
    }

    qi::rule<It, std::string(), Skip> line_comment;
    qi::rule<It, std::string(), Skip> multi_line_comment;
    qi::rule<It, File(), Skip> file;

    qi::rule<It, Class(), Skip> class_specifier;
    qi::rule<It, Class::Head(), Skip> class_head;
    qi::rule<It, Class::MemberSpecification(), Skip> class_member_specification;
    qi::rule<It, ClassKey(), Skip> class_key;
    qi::rule<It, Class::HeadName(), Skip> class_head_name;
    qi::rule<It, ClassVirtSpecifier(), Skip> class_virt_specifier;
    qi::rule<It, Class::BaseClause(), Skip> class_base_clause;
    qi::rule<It, Class::BaseSpecifier(), Skip> class_base_specifier;
    qi::rule<It, ClassOrDecltype(), Skip> class_or_decltype;
    qi::rule<It, Identifier(), Skip> class_name;
    qi::rule<It, Identifier(), Skip> type_name;
    qi::rule<It, Identifier(), Skip> nested_parcel;
    qi::rule<It, NestedNameSpecifier(), Skip> nested_name_specifier;
    qi::rule<It, AccessSpecifier(), Skip> access_specifier;

    qi::rule<It, AttributeSpecifier(), Skip> attribute_specifier;
    qi::rule<It, std::string(), Skip> attribute_using_prefix;
    qi::rule<It, std::string(), Skip> attribute_namespace;
    qi::rule<It, std::vector<Attribute>(), Skip> attribute_list;
    qi::rule<It, Attribute(), Skip> attribute;
    qi::rule<It, Attribute::NameToken(), Skip> attribute_token;
    qi::rule<It, Attribute::NameToken(), Skip> attribute_scoped_token;
    qi::rule<It, std::string(), Skip> attribute_argument_clause;
    qi::rule<It, std::string()> balanced_token_seq;
    qi::rule<It, std::string()> balanced_token;

    // NOTE Does not exclude control characters.
    qi::rule<It, std::string()> identifier;
    qi::rule<It, std::string()> identifier_nondigit;
    qi::rule<It, std::string()> nondigit;
    qi::rule<It, std::string()> universal_character_name;

    qi::rule<It, std::string()> token;

    qi::rule<It, std::string()> literal;
    qi::rule<It, std::string()> operator_or_punctuator;

    qi::rule<It, std::string()> integer_literal;
    qi::rule<It, std::string()> integer_suffix;
    qi::rule<It, char()> unsigned_suffix;
    qi::rule<It, char()> long_suffix;
    qi::rule<It, std::string()> long_long_suffix;
    qi::rule<It, std::string()> binary_literal;
    qi::rule<It, char()> binary_digit;
    qi::rule<It, std::string()> octal_literal;
    qi::rule<It, char()> octal_digit;
    qi::rule<It, std::string()> decimal_literal;
    qi::rule<It, std::string()> hexadecimal_literal;
    qi::rule<It, std::string()> hexadecimal_prefix;

    qi::rule<It, std::string()> character_literal;
    qi::rule<It, std::string()> encoding_prefix;
    qi::rule<It, std::string()> c_char_sequence;
    qi::rule<It, std::string()> basic_c_char;
    qi::rule<It, std::string()> escape_sequence;
    qi::rule<It, std::string()> simple_escape_sequence;
    qi::rule<It, std::string()> simple_sequence_char;
    qi::rule<It, std::string()> numeric_escape_sequence;
    qi::rule<It, std::string()> octal_escape_sequence;
    qi::rule<It, std::string()> hexadecimal_escape_sequence;
    qi::rule<It, std::string()> conditional_escape_sequence;
    qi::rule<It, std::string()> floating_point_literal;
    qi::rule<It, std::string()> decimal_floating_point_literal;
    qi::rule<It, std::string()> hexadecimal_floating_point_literal;
    qi::rule<It, std::string()> hexadecimal_fractional_constant;
    qi::rule<It, std::string()> fractional_constant;
    qi::rule<It, std::string()> digit_sequence;
    qi::rule<It, std::string()> exponent_part;
    qi::rule<It, std::string()> sign;
    qi::rule<It, std::string()> floating_point_suffix;
    qi::rule<It, std::string()> hexadecimal_digit_sequence;
    qi::rule<It, std::string()> binary_exponent_part;
    qi::rule<It, std::string()> string_literal;
    qi::rule<It, std::string()> s_char_sequence;
    qi::rule<It, std::string()> s_char;
    qi::rule<It, std::string()> basic_s_char;
    qi::rule<It, std::string(), qi::locals<std::string>> raw_string;
    qi::rule<It, std::string(std::string)> r_char_sequence;
    qi::rule<It, std::string(std::string)> r_char;
    qi::rule<It, std::string()> d_char_sequence;
    qi::rule<It, char()> d_char;
    qi::rule<It, std::string(std::string)> end_d_char_sequence;
    qi::rule<It, std::string()> boolean_literal;
    qi::rule<It, std::string()> pointer_literal;
    qi::rule<It, std::string()> user_defined_literal;
    qi::rule<It, std::string()> user_defined_integer_literal;
    qi::rule<It, std::string()> user_defined_string_literal;
    qi::rule<It, std::string()> user_defined_character_literal;
    qi::rule<It, std::string()> ud_suffix;
    qi::rule<It, std::string()> user_defined_floating_point_literal;
};

} // namespace
} // namespace yenxo::moc
