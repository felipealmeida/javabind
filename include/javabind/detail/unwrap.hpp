// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_UNWRAP_HPP
#define JAVABIND_DETAIL_UNWRAP_HPP

#include <javabind/class.hpp>
#include <javabind/object.hpp>
#include <javabind/string.hpp>

namespace javabind { namespace detail {

#define JAVABIND_UNWRAP(z, n, data) javabind::detail::unwrap(BOOST_PP_CAT(data, n))
#define JAVABIND_TRAILING_UNWRAP(z, n, data) \
    BOOST_PP_COMMA() javabind::detail::unwrap(BOOST_PP_CAT(data, n))

template <typename T>
T unwrap(T t) { return t; }

inline ::jobject unwrap(object o) { return o.raw(); }

    //inline ::jclass unwrap(class_ c) { return c.raw(); }

inline ::jstring unwrap(string s) { return s.raw(); }

} }

#endif
