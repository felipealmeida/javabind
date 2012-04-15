// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_FIELD_SET_FIELD_HPP
#define JAVABIND_DETAIL_FIELD_SET_FIELD_HPP

#include <javabind/detail/tag.hpp>
#include <javabind/object.hpp>

#include <cassert>
#include <stdexcept>

namespace javabind { namespace detail {

inline void set_field(JNIEnv* env, jobject o, jfieldID id, jint v)
{
  assert(!env->ExceptionCheck());
  env->SetIntField(o, id, v);
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetIntField");
  assert(env->GetIntField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, jdouble v)
{
  assert(!env->ExceptionCheck());
  env->SetDoubleField(o, id, v);
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetDoubleField");
  assert(env->GetDoubleField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, jlong v)
{
  assert(!env->ExceptionCheck());
  env->SetLongField(o, id, v);
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetLongField");
  assert(env->GetLongField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, jobject v)
{
  assert(!env->ExceptionCheck());
  env->SetObjectField(o, id, v);
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetObjectField");
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, object v)
{
  assert(!env->ExceptionCheck());
  env->SetObjectField(o, id, v.raw());
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetObjectField");
}

} }

#endif
