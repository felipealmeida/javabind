// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_CLASS_HPP
#define JAVABIND_CLASS_HPP

#include <javabind/method.hpp>
#include <javabind/field_descriptor_traits.hpp>
#include <javabind/detail/get_static_field.hpp>

#include <jni.h>

#include <stdexcept>

namespace javabind {

template <typename T>
struct static_field;

struct class_
{
  class_( ::jclass cls, JNIEnv* env)
    : cls(cls), env(env)
  {
  }

  template <typename F>
  method<F> method(const char* name) const
  {
    return method<F>(env->GetMethodID(cls, name, "(Ljava/lang/String;)V"), env);
  }

  template <typename T>
  javabind::static_field<T> static_field(const char* name) const
  {
    jfieldID id = env->GetStaticFieldID(cls, name, field_descriptor_traits<T>::value);
    if(id == 0)
      throw std::runtime_error("Couldn't find field");
    return javabind::static_field<T>(id, env);
  }

  template <typename T>
  javabind::static_field<T> static_field(const char* name, const char* type) const
  {
    jfieldID id = env->GetStaticFieldID(cls, name, type);
    if(id == 0)
      throw std::runtime_error("Couldn't find field");
    return javabind::static_field<T>(id, env);
  }

  ::jclass cls;
  JNIEnv* env;
};

}

#include <javabind/field.hpp>

#endif
