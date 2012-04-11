// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_CLASS_HPP
#define JAVABIND_CLASS_HPP

#include <javabind/method.hpp>
#include <javabind/field_descriptor_traits.hpp>
#include <javabind/detail/get_static_field.hpp>

#include <jni.h>

namespace javabind {

struct class_
{
  class_( ::jclass cls, JNIEnv* env)
    : cls(cls), env(env)
  {
  }

  template <typename F>
  method<F> get_method(const char* name) const
  {
    return method<F>(env->GetMethodID(cls, name, "(Ljava/lang/String;)V"), env);
  }

  template <typename T>
  jfieldID get_static_field_id(const char* name) const
  {
    return env->GetStaticFieldID(cls, name, field_descriptor_traits<T>::value);
  }

  jfieldID get_static_field_id(const char* name, const char* type) const
  {
    return env->GetStaticFieldID(cls, name, type);
  }

  template <typename T>
  T get_static_field(jfieldID id) const
  {
    return detail::get_static_field(env, cls, id, detail::tag<T>());
  }

  ::jclass cls;
  JNIEnv* env;
};

}

#endif
