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
#ifndef CMOH_SQL_ROW_HPP__
#define CMOH_SQL_ROW_HPP__


// std includes
#include <type_traits>
#include <utility>


namespace cmoh {
namespace sql {


/**
 * Type representing a row in a table
 *
 * We don't want to force users to accomodate for primary keys in their classes.
 * This class wraps an object of arbitrary type, together with an id, which may
 * be set by a concrete adapter.
 *
 * Users should not use this class directly. The type will be used internally.
 * For linking primary keys to objects.
 */
template <
    typename Value,
    typename IdType
>
class row {
public:
    typedef Value value_type;
    typedef IdType id_type;


    explicit
    constexpr
    row(
        value_type&& value,
        id_type id = id_type()
    ) : _value(std::forward<value_type>(value)), _id(id) {};

    explicit
    constexpr
    row(
        typename std::enable_if<
            std::is_constructible<value_type>::value,
            id_type
        >::type id = id_type()
    ) : _id(id) {};

    row(const row&) = default;
    row(row&&) = default;


    /**
     * Get a pointer to the stored object
     */
    constexpr
    value_type *
    get() {
        return &_value;
    }


    /**
     * Get the id of this row
     */
    constexpr
    id_type
    id() const {
        return _id;
    }

    /**
     * Set the id of this row
     */
    void
    set_id(
        id_type id
    ) {
        _id = id;
    }


private:
    Value _value;
    IdType _id;
};


}
}


#endif
