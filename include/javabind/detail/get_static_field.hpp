// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_FIELD_GET_STATIC_FIELD_HPP
#define JAVABIND_DETAIL_FIELD_GET_STATIC_FIELD_HPP

#include <javabind/detail/tag.hpp>
#include <javabind/object.hpp>

namespace javabind { namespace detail {

inline jint get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<jint>)
{
  return env->GetStaticIntField(cls, id);
}

inline jdouble get_static_field(JNIEnv* env, jclass cls, jfieldID id, tag<jdouble>)
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
