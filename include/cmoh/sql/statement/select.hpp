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
#ifndef CMOH_SQL_STATEMENT_SELECT_HPP__
#define CMOH_SQL_STATEMENT_SELECT_HPP__


// std includes
#include <type_traits>
#include <utility>

// local includes
#include <cmoh/sql/statement/expression.hpp>
#include <cmoh/sql/utils.hpp>


namespace cmoh {
namespace sql {
namespace statenemt {


/**
 * Representation of a select statement
 *
 * Instances of this class represent select statements selecting a number of
 * fields, and with a "WHERE" clause.
 *
 * Users are discouraged from instantiating this template directly. Use the
 * `select()` factory instead.
 */
template <
    typename WhereClause, ///< where clause to use
    typename ...Fields ///< fields to select
>
struct abstract_select {
    typedef std::tuple<Fields...> fields_tuple;
    typedef WhereClause where_clause;


    abstract_select(
        where_clause&& where_clause,
        fields_tuple&& fields
    ) :
        _where_clause{std::forward<where_clause>(where_clause)},
        _fields{std::forward<fields_tuple>(fields)} {}

    abstract_select(
        where_clause&& where_clause,
        Fields&&... fields
    ) :
        _where_clause{std::forward<where_clause>(where_clause)},
        _fields{std::forward<Fields>(fields)...} {}

    abstract_select(abstract_select const&) = default;
    abstract_select(abstract_select&&) = default;


    /**
     * Get the condition for the rows to select
     */
    constexpr
    where_clause
    condition() const noexcept {
        return _where_clause;
    }

    /**
     * Get a tuple containing all the fields
     */
    constexpr
    fields_tuple
    fields() const noexcept {
        return _fields;
    }


private:
    const where_clause _where_clause;
    const fields_tuple _fields;
};


/**
 * Factory for creating the representation of a select statement
 */
template <
    typename ...Fields
>
auto
select(
    Fields&&... fields
) {
    return abstract_select<expression, Fields...>(
        std::forward<Fields>(fields)...
    );
}


// overload for shifting a select statement to an ostream, with where clause
template <
    typename ...Args
>
std::ostream&
operator << (
    std::ostream& stream,
    abstract_select<Args...> const& statement
) {
    stream << "SELECT (";
    join_tuple(stream, ", ", statement.fields());
    stream << ") WHERE" << statement.condition() << ";";
    return stream;
}

// overload for shifting a select statement to an ostream, without where clause
template <
    typename ...Args
>
std::ostream&
operator << (
    std::ostream& stream,
    abstract_select<expression, Args...> const& statement
) {
    stream << "SELECT (";
    join_tuple(stream, ", ", statement.fields());
    stream << ");";
    return stream;
}


}
}
}


#endif
