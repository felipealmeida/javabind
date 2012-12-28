// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_ARRAY_FUNCTIONS_HPP
#define JVB_DETAIL_ARRAY_FUNCTIONS_HPP

#include <jvb/primitives.hpp>
#include <jvb/error.hpp>

#include <jni.h>

namespace jvb { namespace detail {

template <typename T, typename Enable = void>
struct array_functions;

template <>
struct array_functions<bool>
{
  static jboolean* get_array_elements(environment e, jbooleanArray ar, jboolean* is_copy)
  {
    return e.raw()->GetBooleanArrayElements(ar, is_copy);
  }
  static void release_array_elements(environment e, jbooleanArray ar, jboolean* raw_ar, jint mode)
  {
    e.raw()->ReleaseBooleanArrayElements(ar, raw_ar, mode);
  }
  static void set_array_region(environment e, jbooleanArray ar, jint start, jint len
                               , jboolean const* raw_ar)
  {
    e.raw()->SetBooleanArrayRegion(ar, start, len, const_cast<jboolean*>(raw_ar));
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
  static void set_array_region(environment e, jcharArray ar, jint start, jint len
                               , jchar const* raw_ar)
  {
    e.raw()->SetCharArrayRegion(ar, start, len, const_cast<jchar*>(raw_ar));
  }
};

template <>
struct array_functions<short_>
{
  static jshort* get_array_elements(environment e, jshortArray ar, jboolean* is_copy)
  {
    return e.raw()->GetShortArrayElements(ar, is_copy);
  }
  static void release_array_elements(environment e, jshortArray ar, jshort* raw_ar
                                     , jint mode)
  {
    e.raw()->ReleaseShortArrayElements(ar, raw_ar, mode);
  }
  static void set_array_region(environment e, jshortArray ar, jint start, jint len
                               , jshort const* raw_ar)
  {
    e.raw()->SetShortArrayRegion(ar, start, len, const_cast<jshort*>(raw_ar));
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
struct array_functions<long_>
{
  static jlong* get_array_elements(environment e, jlongArray ar, jboolean* is_copy)
  {
    return e.raw()->GetLongArrayElements(ar, is_copy);
  }
  static void release_array_elements(environment e, jlongArray ar, jlong* raw_ar
                                     , jint mode)
  {
    e.raw()->ReleaseLongArrayElements(ar, raw_ar, mode);
  }
  static void set_array_region(environment e, jlongArray ar, jint start, jint len
                               , jlong const* raw_ar)
  {
    e.raw()->SetLongArrayRegion(ar, start, len, const_cast<jlong*>(raw_ar));
  }
};

template <>
struct array_functions<float_>
{
  static jfloat* get_array_elements(environment e, jfloatArray ar, jboolean* is_copy)
  {
    return e.raw()->GetFloatArrayElements(ar, is_copy);
  }
  static void release_array_elements(environment e, jfloatArray ar, jfloat* raw_ar
                                     , jint mode)
  {
    e.raw()->ReleaseFloatArrayElements(ar, raw_ar, mode);
  }
  static void set_array_region(environment e, jfloatArray ar, jint start, jint len
                               , jfloat const* raw_ar)
  {
    e.raw()->SetFloatArrayRegion(ar, start, len, const_cast<jfloat*>(raw_ar));
  }
};

template <>
struct array_functions<double_>
{
  static jdouble* get_array_elements(environment e, jdoubleArray ar, jboolean* is_copy)
  {
    return e.raw()->GetDoubleArrayElements(ar, is_copy);
  }
  static void release_array_elements(environment e, jdoubleArray ar, jdouble* raw_ar
                                     , jint mode)
  {
    e.raw()->ReleaseDoubleArrayElements(ar, raw_ar, mode);
  }
  static void set_array_region(environment e, jdoubleArray ar, jint start, jint len
                               , jdouble const* raw_ar)
  {
    e.raw()->SetDoubleArrayRegion(ar, start, len, const_cast<jdouble*>(raw_ar));
  }
};

} }

#endif
