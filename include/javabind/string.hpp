// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_STRING_HPP
#define JAVABIND_STRING_HPP

#include <jni.h>

namespace javabind {

struct string
{
  string(jstring s, JNIEnv* env)
    : s(s), env(env) {}

  jstring raw() const { return s; }

  jstring s;
  JNIEnv* env;
};

}

#endif

