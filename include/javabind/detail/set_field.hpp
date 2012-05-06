// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_FIELD_SET_FIELD_HPP
#define JAVABIND_DETAIL_FIELD_SET_FIELD_HPP

#include <javabind/detail/tag.hpp>
#include <javabind/detail/unwrap.hpp>
#include <javabind/object.hpp>
#include <javabind/primitives.hpp>

#include <cassert>
#include <stdexcept>

namespace javabind { namespace detail {

inline void set_field(JNIEnv* env, jobject o, jfieldID id, int_ v)
{
  assert(!env->ExceptionCheck());
  env->SetIntField(o, id, unwrap(v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetIntField");
  assert(env->GetIntField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, double_ v)
{
  assert(!env->ExceptionCheck());
  env->SetDoubleField(o, id, unwrap(v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetDoubleField");
  assert(env->GetDoubleField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, long_ v)
{
  assert(!env->ExceptionCheck());
  env->SetLongField(o, id, unwrap(v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetLongField");
  assert(env->GetLongField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, object v)
{
  assert(!env->ExceptionCheck());
  env->SetObjectField(o, id, unwrap(v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetObjectField");
}

} }

#endif
