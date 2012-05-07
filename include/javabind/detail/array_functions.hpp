// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_ARRAY_FUNCTIONS_HPP
#define JAVABIND_DETAIL_ARRAY_FUNCTIONS_HPP

#include <javabind/primitives.hpp>

#include <jni.h>

namespace javabind { namespace detail {

template <typename T>
struct array_functions;

template <>
struct array_functions<char_>
{
  static jchar* get_array_elements(JNIEnv* env, jcharArray ar, jboolean* is_copy)
  {
    return env->GetCharArrayElements(ar, is_copy);
  }
  static void release_array_elements(JNIEnv* env, jcharArray ar, jchar* raw_ar
                                     , jint mode)
  {
    env->ReleaseCharArrayElements(ar, raw_ar, mode);
  }
  static void set_array_region(JNIEnv* env, jcharArray ar, jchar start, jchar len
                               , jchar const* raw_ar)
  {
    env->SetCharArrayRegion(ar, start, len, const_cast<jchar*>(raw_ar));
  }
};

template <>
struct array_functions<int_>
{
  static jint* get_array_elements(JNIEnv* env, jintArray ar, jboolean* is_copy)
  {
    return env->GetIntArrayElements(ar, is_copy);
  }
  static void release_array_elements(JNIEnv* env, jintArray ar, jint* raw_ar
                                     , jint mode)
  {
    env->ReleaseIntArrayElements(ar, raw_ar, mode);
  }
  static void set_array_region(JNIEnv* env, jintArray ar, jint start, jint len
                               , jint const* raw_ar)
  {
    env->SetIntArrayRegion(ar, start, len, const_cast<jint*>(raw_ar));
  }
};

template <>
struct array_functions<byte>
{
  static jbyte* get_array_elements(JNIEnv* env, jbyteArray ar, jboolean* is_copy)
  {
    return env->GetByteArrayElements(ar, is_copy);
  }
  static void release_array_elements(JNIEnv* env, jbyteArray ar, jbyte* raw_ar
                                     , jint mode)
  {
    env->ReleaseByteArrayElements(ar, raw_ar, mode);
  }
  static void set_array_region(JNIEnv* env, jbyteArray ar, jint start, jint len
                               , jbyte const* raw_ar)
  {
    env->SetByteArrayRegion(ar, start, len, const_cast<jbyte*>(raw_ar));
  }
};

} }

#endif
