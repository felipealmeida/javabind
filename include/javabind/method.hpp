// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_METHOD_HPP
#define JAVABIND_METHOD_HPP

#include <javabind/object.hpp>

#include <jni.h>

namespace javabind {

namespace detail {


}

template <typename F>
struct method
{
  method( ::jmethodID id, JNIEnv* env)
    : id(id), env(env) {}

  void operator()(object o, string a1) const
  {
    env->CallVoidMethod(o.o, id, a1.s);
  }

  jmethodID id;
  JNIEnv* env;
};

}

#endif
