// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_OBJECT_HPP
#define JAVABIND_OBJECT_HPP

#include <javabind/string.hpp>

#include <jni.h>

namespace javabind {

struct class_;

struct object
{
  object() : o(0), env(0) {}
  object(jobject o, JNIEnv* env)
    : o(o), env(env) {}

  javabind::class_ class_() const;
  jobject raw() const { return o; }

  typedef ::jobject java_type;

  jobject o;
  JNIEnv* env;
};

}

#endif

