// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_STRING_HPP
#define JVB_STRING_HPP

#include <jvb/environment.hpp>
#include <jvb/object.hpp>

#include <ostream>

#include <jni.h>

namespace jvb {

struct string
{
  template <std::size_t N>
  string(environment e, const char array[N])
  {
    s = e.raw()->NewStringUTF(array);
  }
  string(jstring s)
    : s(s) {}
  string(environment e, const char* cstring)
  {
    s = e.raw()->NewStringUTF(cstring);
  }

  typedef jstring java_type;

  jstring raw() const { return s; }

  std::string str(jvb::environment e)
  {
    const char* s = e.raw()->GetStringUTFChars(raw(), 0);
    if(s)
    {
      std::string tmp(s);
      e.raw()->ReleaseStringUTFChars(raw(), s);
      return tmp;
    }
    else
      return std::string();
  }

  jstring s;
};

typedef string String;

namespace jcl { namespace java { namespace lang {

using jvb::String;

} } }

}

#endif

