// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_FIELD_GET_STATIC_FIELD_HPP
#define JVB_DETAIL_FIELD_GET_STATIC_FIELD_HPP

#include <jvb/detail/tag.hpp>
#include <jvb/object.hpp>
#include <jvb/string.hpp>
#include <jvb/environment.hpp>

namespace jvb { namespace detail {

inline bool get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<bool>)
{
  return env->GetStaticBooleanField(cls, id) != 0;
}

inline jbyte get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<byte>)
{
  return env->GetStaticByteField(cls, id);
}

inline jchar get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<char_>)
{
  return env->GetStaticCharField(cls, id);
}

inline jshort get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<short_>)
{
  return env->GetStaticShortField(cls, id);
}

inline jint get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<int_>)
{
  return env->GetStaticIntField(cls, id);
}

inline jlong get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<long_>)
{
  return env->GetStaticLongField(cls, id);
}

inline jfloat get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<float_>)
{
  return env->GetStaticFloatField(cls, id);
}

inline jdouble get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<double_>)
{
  return env->GetStaticDoubleField(cls, id);
}

inline jobject get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<jobject>)
{
  return env->GetStaticObjectField(cls, id);
}

inline object get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<object>)
{
  return object(env->GetStaticObjectField(cls, id));
}

inline string get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<jstring>)
{
  return string(jstring(env->GetStaticObjectField(cls, id)));
}

template <typename T>
inline T get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<T>
                   , typename boost::enable_if<boost::is_base_of<object, T> >::type* = 0)
{
  assert(!env->ExceptionCheck());
  return T(env->GetStaticObjectField(cls, id));
}

template <typename T>
inline jvb::array<T> get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<array<T> >)
{
  typedef jvb::array<T> array;
  assert(!env->ExceptionCheck());
  return static_cast<typename array::java_type>
    (static_cast<void*>(env->GetStaticObjectField(cls, id)));
}

} }

#endif
