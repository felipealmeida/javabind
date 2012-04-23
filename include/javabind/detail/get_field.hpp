// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_FIELD_GET_FIELD_HPP
#define JAVABIND_DETAIL_FIELD_GET_FIELD_HPP

#include <javabind/detail/tag.hpp>
#include <javabind/object.hpp>
#include <javabind/primitives.hpp>

#include <cassert>

namespace javabind { namespace detail {

inline int_ get_field(JNIEnv* env, jobject o, jfieldID id, tag<int_>)
{
  assert(!env->ExceptionCheck());
  return env->GetIntField(o, id);
}

inline double_ get_field(JNIEnv* env, jobject o, jfieldID id, tag<double_>)
{
  assert(!env->ExceptionCheck());
  return env->GetDoubleField(o, id);
}

inline long_ get_field(JNIEnv* env, jobject o, jfieldID id, tag<long_>)
{
  assert(!env->ExceptionCheck());
  return env->GetLongField(o, id);
}

inline object get_field(JNIEnv* env, jobject o, jfieldID id, tag<object>)
{
  assert(!env->ExceptionCheck());
  return object(env->GetObjectField(o, id), env);
}

} }

#endif
