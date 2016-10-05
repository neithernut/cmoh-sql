/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Julian Ganz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef CMOH_SQL_STATEMENT_EXPRESSION_HPP__
#define CMOH_SQL_STATEMENT_EXPRESSION_HPP__


// std includes
#include <ostream>


namespace cmoh {
namespace sql {
namespace statenemt {
namespace expression {


/**
 * Basic expression
 *
 * This class represents an empty expression.
 */
struct expression {};


/**
 * Expression yielding a value of a certain type
 */
template <
    typename Type
>
struct typed_expression {
    typedef Type type;
};


/**
 * Expression representing a column
 *
 * Use this value to represent a column
 */
template <
    typename Attribute
>
struct column : typed_expression<typename Attribute::type> {
    typedef Attribute attribute;
};


/**
 * Literal representation
 */
template <
    typename Type
>
struct literal : typed_expression<Type> {
    constexpr literal(Type&& value) : value{value} {}

    const Type value;
};


/**
 * Representation of a check for equality
 */
template <
    typename LHS,
    typename RHS
>
struct equality_expression : typed_expression<bool> {
    typedef LHS lhs_type;
    typedef RHS rhs_type;

    static_assert(
        std::is_same<typename lhs_type::type, typename rhs_type::type>::value,
        "Type missmatch between left hand side and right hand side."
    );

    constexpr equality_expression(lhs_type&& lhs, rhs_type&& rhs) :
        lhs{std::forward<LHS>(lhs)}, rhs{std::forward<RHS>(rhs)} {}

    const lhs_type lhs;
    const rhs_type rhs;
};


}


// overload for shifting a column expression to an ostream
template <
    typename ...T
>
std::ostream&
operator << (
    std::ostream& stream,
    expression::column<T...> const& exp
) {
    return stream << decltype(exp)::attribute::key();
}


// overload for shifting an equality expression to an ostream
template <
    typename ...T
>
std::ostream&
operator << (
    std::ostream& stream,
    expression::equality_expression<T...> const& exp
) {
    return stream << exp.lhs << " = " << exp.rhs;
}


// overloads for putting things together
template <
    typename LHS,
    typename RHS
>
constexpr
expression::equality_expression<LHS, RHS>
operator == (
    LHS&& lhs,
    RHS&& rhs
) {
    return {std::forward<LHS>(lhs), std::forward<RHS>(rhs)};
}


}
}
}


#endif
