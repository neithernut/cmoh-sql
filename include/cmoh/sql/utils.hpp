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
#ifndef CMOH_SQL_UTILS_HPP__
#define CMOH_SQL_UTILS_HPP__


// std includes
#include <ostream>
#include <utility>


namespace cmoh {
namespace sql {
namespace util {


/**
 * Join objects in an outstream, separated by a separator
 *
 * Use this function to join objects of arbitrary type in an `std::ostream`.
 * The separator specified is used for separating the objects.
 */
template <
    typename Separator,
    typename Arg0,
    typename ...Args
>
void
join(
    std::ostream& stream, ///< stream to use for joining
    Separator&& separator, ///< separator to insert between objects
    Arg0&& arg0, ///< first of the objects to join
    Args&&... args ///< rest of the objects to join
) {
    stream << arg0 << separator;
    join(
        stream,
        std::forward<Separator>(separator),
        std::forward<Args>(args)...
    );
}

// overload for recursion termination/joining a single object
template <
    typename Separator,
    typename Arg0
>
void
join(
    std::ostream& stream,
    Separator&& separator,
    Arg0&& arg0
) {
    stream << arg0;
}


/**
 * Join elements in a tuple using an outstream
 *
 * Use this function to join tuple elements using an `std::ostream`.
 * The separator specified is used for separating the objects.
 */
template <
    typename Separator,
    typename Tuple,
    std::size_t ...indices
>
void
join_tuple(
    std::ostream& stream,
    Separator&& separator,
    Tuple&& tuple,
    std::integer_sequence<std::size_t, indices...>&&
) {
    join(
        stream,
        std::forward<Separator>(separator),
        std::get<indices>(std::forward<Tuple>(tuple))...
    );
}

// convenience overloads
template <
    typename Separator,
    typename Tuple
>
void
join_tuple(
    std::ostream& stream,
    Separator&& separator,
    Tuple&& tuple
) {
    join(
        stream,
        std::forward<Separator>(separator),
        std::forward<Tuple>(tuple),
        std::make_index_sequence<std::tuple_size<std::decay<Tuple>>::value>{}
    );
}


}
}
}


#endif
