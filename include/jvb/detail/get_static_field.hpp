// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_FIELD_GET_STATIC_FIELD_HPP
#define JVB_DETAIL_FIELD_GET_STATIC_FIELD_HPP

#include <jvb/detail/tag.hpp>
#include <jvb/object.hpp>

namespace jvb { namespace detail {

inline jint get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<int_>)
{
  return env->GetStaticIntField(cls, id);
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
  return object(env->GetStaticObjectField(cls, id), env);
}

} }

#endif
