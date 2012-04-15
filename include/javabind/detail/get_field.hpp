// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_FIELD_GET_FIELD_HPP
#define JAVABIND_DETAIL_FIELD_GET_FIELD_HPP

#include <javabind/detail/tag.hpp>
#include <javabind/object.hpp>

#include <cassert>

namespace javabind { namespace detail {

inline jint get_field(JNIEnv* env, jobject o, jfieldID id, tag<jint>)
{
  assert(!env->ExceptionCheck());
  return env->GetIntField(o, id);
}

inline jdouble get_field(JNIEnv* env, jobject o, jfieldID id, tag<jdouble>)
{
  assert(!env->ExceptionCheck());
  return env->GetDoubleField(o, id);
}

inline jlong get_field(JNIEnv* env, jobject o, jfieldID id, tag<jlong>)
{
  assert(!env->ExceptionCheck());
  return env->GetLongField(o, id);
}

inline jobject get_field(JNIEnv* env, jobject o, jfieldID id, tag<jobject>)
{
  assert(!env->ExceptionCheck());
  return env->GetObjectField(o, id);
}

inline object get_field(JNIEnv* env, jobject o, jfieldID id, tag<object>)
{
  assert(!env->ExceptionCheck());
  return object(env->GetObjectField(o, id), env);
}

} }

#endif
