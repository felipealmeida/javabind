// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_ARRAY_FUNCTIONS_HPP
#define JVB_DETAIL_ARRAY_FUNCTIONS_HPP

#include <jvb/primitives.hpp>

#include <jni.h>

namespace jvb { namespace detail {

template <typename T>
struct array_functions;

template <>
struct array_functions<char_>
{
  static jchar* get_array_elements(environment e, jcharArray ar, jboolean* is_copy)
  {
    return e.raw()->GetCharArrayElements(ar, is_copy);
  }
  static void release_array_elements(environment e, jcharArray ar, jchar* raw_ar
                                     , jint mode)
  {
    e.raw()->ReleaseCharArrayElements(ar, raw_ar, mode);
  }
  static void set_array_region(environment e, jcharArray ar, jchar start, jchar len
                               , jchar const* raw_ar)
  {
    e.raw()->SetCharArrayRegion(ar, start, len, const_cast<jchar*>(raw_ar));
  }
};

template <>
struct array_functions<int_>
{
  static jint* get_array_elements(environment e, jintArray ar, jboolean* is_copy)
  {
    return e.raw()->GetIntArrayElements(ar, is_copy);
  }
  static void release_array_elements(environment e, jintArray ar, jint* raw_ar
                                     , jint mode)
  {
    e.raw()->ReleaseIntArrayElements(ar, raw_ar, mode);
  }
  static void set_array_region(environment e, jintArray ar, jint start, jint len
                               , jint const* raw_ar)
  {
    e.raw()->SetIntArrayRegion(ar, start, len, const_cast<jint*>(raw_ar));
  }
};

template <>
struct array_functions<byte>
{
  static jbyte* get_array_elements(environment e, jbyteArray ar, jboolean* is_copy)
  {
    return e.raw()->GetByteArrayElements(ar, is_copy);
  }
  static void release_array_elements(environment e, jbyteArray ar, jbyte* raw_ar
                                     , jint mode)
  {
    e.raw()->ReleaseByteArrayElements(ar, raw_ar, mode);
  }
  static void set_array_region(environment e, jbyteArray ar, jint start, jint len
                               , jbyte const* raw_ar)
  {
    e.raw()->SetByteArrayRegion(ar, start, len, const_cast<jbyte*>(raw_ar));
  }
};

} }

#endif
