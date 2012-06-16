// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JAVABIND_OBJECT_HPP
#define JAVABIND_OBJECT_HPP

#include <javabind/string.hpp>

#include <jni.h>
#include <ostream>

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

  typedef bool(object::*test_type)() const;
  operator test_type() const
  {
    return test()? &object::test : test_type(0);
  }

  string to_string() const;
  static object nil(JNIEnv* env) { return object(0, env); }
  JNIEnv* environment() const { return env; }
private:
  bool test() const { return o != 0; }

  jobject o;
  JNIEnv* env;
};

std::ostream& operator<<(std::ostream& os, object o);

}

#endif

