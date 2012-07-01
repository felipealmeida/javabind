// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_STRING_HPP
#define JVB_STRING_HPP

#include <ostream>

#include <jni.h>

namespace jvb {

struct string
{
  string(jstring s)
    : s(s) {}

  typedef jstring java_type;

  jstring raw() const { return s; }

  // std::string str()
  // {
  //   const char* s = env->GetStringUTFChars(raw(), 0);
  //   if(s)
  //   {
  //     std::string tmp(s);
  //     env->ReleaseStringUTFChars(raw(), s);
  //     return tmp;
  //   }
  //   else
  //     return std::string();
  // }

  jstring s;
};

// inline std::ostream& operator<<(std::ostream& os, string s)
// {
//   std::ostream::sentry sentry(os);

//   const char* str = s.env->GetStringUTFChars(s.raw(), 0);
//   if(str)
//   {
//     os << str;
//     s.env->ReleaseStringUTFChars(s.raw(), str);
//     return os;
//   }
//   else
//     return os << "[allocation error while returning string]";
// }

}

#endif

