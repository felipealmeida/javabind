// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_FIELD_GET_FIELD_HPP
#define JVB_DETAIL_FIELD_GET_FIELD_HPP

#include <jvb/detail/tag.hpp>
#include <jvb/object.hpp>
#include <jvb/primitives.hpp>

#include <cassert>

namespace jvb { namespace detail {

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
