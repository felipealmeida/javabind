// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_FIELD_SET_STATIC_FIELD_HPP
#define JAVABIND_DETAIL_FIELD_SET_STATIC_FIELD_HPP

#include <jni.h>

namespace javabind { namespace detail {

inline void set_static_field(JNIEnv* env, jclass c, jfieldID id, int_ v)
{
  assert(!env->ExceptionCheck());
  env->SetStaticIntField(c, id, unwrap(v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetStaticIntField");
  assert(env->GetStaticIntField(c, id) == unwrap(v));
}

inline void set_static_field(JNIEnv* env, jclass c, jfieldID id, double_ v)
{
  assert(!env->ExceptionCheck());
  env->SetStaticDoubleField(c, id, unwrap(v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetStaticDoubleField");
  assert(env->GetStaticDoubleField(c, id) == unwrap(v));
}

inline void set_static_field(JNIEnv* env, jclass c, jfieldID id, long_ v)
{
  assert(!env->ExceptionCheck());
  env->SetStaticLongField(c, id, unwrap(v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetStaticLongField");
  assert(env->GetStaticLongField(c, id) == unwrap(v));
}

inline void set_static_field(JNIEnv* env, jclass c, jfieldID id, object v)
{
  assert(!env->ExceptionCheck());
  env->SetStaticObjectField(c, id, unwrap(v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetStaticObjectField");
}

} }

#endif
