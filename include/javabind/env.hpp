// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_ENV_HPP
#define JAVABIND_ENV_HPP

#include <javabind/class.hpp>
#include <javabind/string.hpp>

#include <jni.h>

#include <cassert>

namespace javabind {

struct env
{
  env(JNIEnv* e)
  : e(e)
  {
    assert(e != 0);
  }

  class_ find_class(const char* name) const
  {
    return class_(e->FindClass(name), e);
  }
  class_ find_class(std::string const& name) const { return find_class(name.c_str()); }

  string create_string_utf(const char* s)
  {
    return string(e->NewStringUTF(s), e);
  }

  JNIEnv* e;
};

}

#endif
