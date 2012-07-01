// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_OBJECT_HPP
#define JVB_OBJECT_HPP

#include <jvb/class.hpp>

#include <jni.h>
#include <ostream>

namespace jvb {

struct object
{
  object() : obj(0) {}
  object(jobject obj)
    : obj(obj)
  {
  }

//   jvb::class_ class_() const;
  jobject raw() const { return obj; }

//   typedef ::jobject java_type;

//   typedef bool(object::*test_type)() const;
//   operator test_type() const
//   {
//     return test()? &object::test : test_type(0);
//   }

//   string to_string() const;
  static object nil(JNIEnv* env) { return object(0); }
//   JNIEnv* environment() const { return env; }
private:
  bool test() const { return obj != 0; }

  ::jobject obj;
};

std::ostream& operator<<(std::ostream& os, object o);

typedef object Object;

namespace jcl { namespace java { namespace lang {

typedef jvb::object Object;

} } }

}

#endif

