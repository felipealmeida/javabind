// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_UNWRAP_HPP
#define JVB_DETAIL_UNWRAP_HPP

#include <jvb/array.hpp>
#include <jvb/class.hpp>
#include <jvb/object.hpp>
#include <jvb/string.hpp>
#include <jvb/primitives.hpp>

namespace jvb { namespace detail {

#define JVB_UNWRAP(z, n, data) jvb::detail::unwrap(e, BOOST_PP_CAT(data, n))
#define JVB_TRAILING_UNWRAP(z, n, data) \
    BOOST_PP_COMMA() jvb::detail::unwrap(e, BOOST_PP_CAT(data, n))

inline jstring unwrap(environment e, const char* c)
{
  assert(c != 0);
  jstring str = e.raw()->NewStringUTF(c);
  assert(str != 0);
  return str;
}
inline ::jboolean unwrap(environment e, bool o) { return o; }
inline ::jbyte unwrap(environment e, byte o) { return o.raw(); }
inline ::jchar unwrap(environment e, char_ o) { return o.raw(); }
inline ::jshort unwrap(environment e, short_ o) { return o.raw(); }
inline ::jint unwrap(environment e, int_ o) { return o.raw(); }
inline ::jlong unwrap(environment e, long_ o) { return o.raw(); }
inline ::jfloat unwrap(environment e, float_ o) { return o.raw(); }
inline ::jdouble unwrap(environment e, double_ o) { return o.raw(); }
inline ::jobject unwrap(environment e, object o) { return o.raw(); }
inline ::jstring unwrap(environment e, string s) { return s.raw(); }
inline ::jbyteArray unwrap(environment e, array<byte> a) { return a.raw(); }
inline ::jcharArray unwrap(environment e, array<char_> a) { return a.raw(); }
// inline ::jshortArray unwrap(environment e, array<short_> a) { return a.raw(); }
// inline ::jintArray unwrap(environment e, array<int_> a) { return a.raw(); }
// inline ::jlongArray unwrap(environment e, array<long_> a) { return a.raw(); }
// inline ::jfloatArray unwrap(environment e, array<float_> a) { return a.raw(); }
// inline ::jdoubleArray unwrap(environment e, array<double_> a) { return a.raw(); }
inline ::jobjectArray unwrap(environment e, array<object> a) { return a.raw(); }
// inline ::jstringArray unwrap(environment e, array<string> a) { return a.raw(); }

} }

#endif
