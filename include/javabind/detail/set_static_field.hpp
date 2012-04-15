// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_FIELD_SET_STATIC_FIELD_HPP
#define JAVABIND_DETAIL_FIELD_SET_STATIC_FIELD_HPP

#include <jni.h>

namespace javabind { namespace detail {

inline void set_static_field(JNIEnv* env, jclass cls, jfieldID id, jint v)
{
  env->SetStaticIntField(cls, id, v);
}

// inline void set_static_field(JNIEnv* env, jclass cls, jfieldID id, jdouble v)
// {
//   env->SetStaticDoubleField(cls, id, v);
// }

inline void set_static_field(JNIEnv* env, jclass cls, jfieldID id, object v)
{
  env->SetStaticObjectField(cls, id, v.raw());
}

} }

#endif
