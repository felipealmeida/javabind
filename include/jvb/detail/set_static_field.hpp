// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_FIELD_SET_STATIC_FIELD_HPP
#define JVB_DETAIL_FIELD_SET_STATIC_FIELD_HPP

#include <jni.h>
#include <jvb/primitives.hpp>

namespace jvb { namespace detail {

inline void set_static_field(JNIEnv* env, jclass c, jfieldID id, byte v)
{
  assert(!env->ExceptionCheck());
  env->SetStaticByteField(c, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetStaticByteField");
  assert(env->GetStaticByteField(c, id) == unwrap(env, v));
}

inline void set_static_field(JNIEnv* env, jclass c, jfieldID id, char_ v)
{
  assert(!env->ExceptionCheck());
  env->SetStaticCharField(c, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetStaticCharField");
  assert(env->GetStaticCharField(c, id) == unwrap(env, v));
}

inline void set_static_field(JNIEnv* env, jclass c, jfieldID id, short_ v)
{
  assert(!env->ExceptionCheck());
  env->SetStaticShortField(c, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetStaticShortField");
  assert(env->GetStaticShortField(c, id) == unwrap(env, v));
}

inline void set_static_field(JNIEnv* env, jclass c, jfieldID id, int_ v)
{
  assert(!env->ExceptionCheck());
  env->SetStaticIntField(c, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetStaticIntField");
  assert(env->GetStaticIntField(c, id) == unwrap(env, v));
}

inline void set_static_field(JNIEnv* env, jclass c, jfieldID id, long_ v)
{
  assert(!env->ExceptionCheck());
  env->SetStaticLongField(c, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetStaticLongField");
  assert(env->GetStaticLongField(c, id) == unwrap(env, v));
}

inline void set_static_field(JNIEnv* env, jclass c, jfieldID id, float_ v)
{
  assert(!env->ExceptionCheck());
  env->SetStaticFloatField(c, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetStaticFloatField");
  assert(env->GetStaticFloatField(c, id) == unwrap(env, v));
}

inline void set_static_field(JNIEnv* env, jclass c, jfieldID id, double_ v)
{
  assert(!env->ExceptionCheck());
  env->SetStaticDoubleField(c, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetStaticDoubleField");
  assert(env->GetStaticDoubleField(c, id) == unwrap(env, v));
}

inline void set_static_field(JNIEnv* env, jclass c, jfieldID id, object v)
{
  assert(!env->ExceptionCheck());
  env->SetStaticObjectField(c, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetStaticObjectField");
}

} }

#endif
