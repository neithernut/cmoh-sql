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


}
}
}


#endif
