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
#include <type_traits>


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
    constexpr literal(Type&& value) noexcept : value{value} {}

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

    constexpr equality_expression(lhs_type&& lhs, rhs_type&& rhs) noexcept :
        lhs{std::forward<LHS>(lhs)}, rhs{std::forward<RHS>(rhs)} {}

    const lhs_type lhs;
    const rhs_type rhs;
};


/**
 * Representation of a conjunction
 */
template <
    typename LHS,
    typename RHS
>
struct conjunction : typed_expression<bool> {
    typedef LHS lhs_type;
    typedef RHS rhs_type;

    static_assert(
        std::is_same<typename lhs_type::type, bool>::value &&
        std::is_same<typename rhs_type::type, bool>::value,
        "Only expressions yielding boolean values can be used in a conjunction."
    );

    constexpr conjunction(lhs_type&& lhs, rhs_type&& rhs) noexcept :
        lhs{std::forward<LHS>(lhs)}, rhs{std::forward<RHS>(rhs)} {}

    const lhs_type lhs;
    const rhs_type rhs;
};


/**
 * Representation of a disjunction
 */
template <
    typename LHS,
    typename RHS
>
struct disjunction : typed_expression<bool> {
    typedef LHS lhs_type;
    typedef RHS rhs_type;

    static_assert(
        std::is_same<typename lhs_type::type, bool>::value &&
        std::is_same<typename rhs_type::type, bool>::value,
        "Only expressions yielding boolean values can be used in a disjunction."
    );

    constexpr disjunction(lhs_type&& lhs, rhs_type&& rhs) noexcept :
        lhs{std::forward<LHS>(lhs)}, rhs{std::forward<RHS>(rhs)} {}

    const lhs_type lhs;
    const rhs_type rhs;
};


}


// overload for shifting expressions to an ostream
template <
    typename ...T
>
std::ostream&
operator << (
    std::ostream& stream,
    expression::column<T...> const& exp
) noexcept {
    return stream << decltype(exp)::attribute::key();
}

template <
    typename ...T
>
std::ostream&
operator << (
    std::ostream& stream,
    expression::equality_expression<T...> const& exp
) noexcept {
    return stream << "( " << exp.lhs << " = " << exp.rhs << " )";
}

template <
    typename ...T
>
std::ostream&
operator << (
    std::ostream& stream,
    expression::conjunction<T...> const& exp
) noexcept {
    return stream << "( " << exp.lhs << " AND " << exp.rhs << " )";
}

template <
    typename ...T
>
std::ostream&
operator << (
    std::ostream& stream,
    expression::disjunction<T...> const& exp
) noexcept {
    return stream << "( " << exp.lhs << " OR " << exp.rhs << " )";
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
) noexcept {
    return {std::forward<LHS>(lhs), std::forward<RHS>(rhs)};
}

template <
    typename LHS,
    typename RHS
>
constexpr
expression::conjunction<LHS, RHS>
operator && (
    LHS&& lhs,
    RHS&& rhs
) noexcept {
    return {std::forward<LHS>(lhs), std::forward<RHS>(rhs)};
}

template <
    typename LHS,
    typename RHS
>
constexpr
expression::disjunction<LHS, RHS>
operator || (
    LHS&& lhs,
    RHS&& rhs
) noexcept {
    return {std::forward<LHS>(lhs), std::forward<RHS>(rhs)};
}


}
}
}


#endif
