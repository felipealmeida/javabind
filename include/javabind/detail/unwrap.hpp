// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_UNWRAP_HPP
#define JAVABIND_DETAIL_UNWRAP_HPP

#include <javabind/class.hpp>
#include <javabind/object.hpp>
#include <javabind/string.hpp>
#include <javabind/primitives.hpp>

namespace javabind { namespace detail {

#define JAVABIND_UNWRAP(z, n, data) javabind::detail::unwrap(BOOST_PP_CAT(data, n))
#define JAVABIND_TRAILING_UNWRAP(z, n, data) \
    BOOST_PP_COMMA() javabind::detail::unwrap(BOOST_PP_CAT(data, n))

inline ::jboolean unwrap(bool o) { return o; }
inline ::jbyte unwrap(byte o) { return o.raw(); }
inline ::jchar unwrap(char_ o) { return o.raw(); }
inline ::jshort unwrap(short_ o) { return o.raw(); }
inline ::jint unwrap(int_ o) { return o.raw(); }
inline ::jlong unwrap(long_ o) { return o.raw(); }
inline ::jfloat unwrap(float_ o) { return o.raw(); }
inline ::jdouble unwrap(double_ o) { return o.raw(); }
inline ::jobject unwrap(object o) { return o.raw(); }
inline ::jstring unwrap(string s) { return s.raw(); }

} }

#endif
