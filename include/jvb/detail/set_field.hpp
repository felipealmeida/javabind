// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_FIELD_SET_FIELD_HPP
#define JVB_DETAIL_FIELD_SET_FIELD_HPP

#include <jvb/detail/tag.hpp>
#include <jvb/detail/unwrap.hpp>
#include <jvb/object.hpp>
#include <jvb/primitives.hpp>

#include <cassert>
#include <stdexcept>

namespace jvb { namespace detail {

inline void set_field(JNIEnv* env, jobject o, jfieldID id, bool v)
{
  assert(!env->ExceptionCheck());
  env->SetBooleanField(o, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetBooleanField");
  assert(env->GetBooleanField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, byte v)
{
  assert(!env->ExceptionCheck());
  env->SetByteField(o, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetIntField");
  assert(env->GetByteField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, char_ v)
{
  assert(!env->ExceptionCheck());
  env->SetCharField(o, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetIntField");
  assert(env->GetCharField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, short_ v)
{
  assert(!env->ExceptionCheck());
  env->SetShortField(o, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetIntField");
  assert(env->GetShortField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, int_ v)
{
  assert(!env->ExceptionCheck());
  env->SetIntField(o, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetIntField");
  assert(env->GetIntField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, long_ v)
{
  assert(!env->ExceptionCheck());
  env->SetLongField(o, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetLongField");
  assert(env->GetLongField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, float_ v)
{
  assert(!env->ExceptionCheck());
  env->SetFloatField(o, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetFloatField");
  assert(env->GetFloatField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, double_ v)
{
  assert(!env->ExceptionCheck());
  env->SetDoubleField(o, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetDoubleField");
  assert(env->GetDoubleField(o, id) == v);
}

inline void set_field(JNIEnv* env, jobject o, jfieldID id, object v)
{
  assert(!env->ExceptionCheck());
  env->SetObjectField(o, id, unwrap(env, v));
  if(env->ExceptionCheck())
    throw std::runtime_error("Exception thrown in SetObjectField");
}

} }

#endif
