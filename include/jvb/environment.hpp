// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ENVIRONMENT_HPP
#define JVB_ENVIRONMENT_HPP

// #include <jvb/class.hpp>
// #include <jvb/string.hpp>

// #include <boost/function_types/parameter_types.hpp>
// #include <boost/function.hpp>

// #include <boost/mpl/pop_front.hpp>

#include <cassert>

#include <jni.h>

// #include <cassert>
// #include <stdexcept>
// #include <memory>

namespace jvb {

struct environment
{
  environment()
    : e(0)
  {
  }
  environment(JNIEnv* e)
  : e(e)
  {
    assert(e != 0);
  }

  // class_ find_class(const char* name) const
  // {
  //   jclass cls = e->FindClass(name);
  //   if(cls == 0)
  //     throw std::runtime_error("Couldn't find class");
  //   return class_(cls, e);
  // }
  // class_ find_class(std::string const& name) const { return find_class(name.c_str()); }

  // string create_string_utf(const char* s)
  // {
  //   return string(e->NewStringUTF(s), e);
  // }

  // class_ define_class(const char* name, jobject classloader, jbyte* buf, std::size_t size) const
  // {
  //   jclass c = e->DefineClass(name, classloader, buf, size);
  //   if(c == 0)
  //     throw std::runtime_error("Couldn't define class");
  //   return class_(c, e);
  // }

  // bool exception_pending() const
  // {
  //   return e->ExceptionCheck();
  // }

  JNIEnv* raw() const { return e; }
private:
  JNIEnv* e;
};

}

#endif
