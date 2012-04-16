// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_STRING_HPP
#define JAVABIND_STRING_HPP

#include <ostream>

#include <jni.h>

namespace javabind {

struct string
{
  string(jstring s, JNIEnv* env)
    : s(s), env(env) {}

  jstring raw() const { return s; }

  std::string str()
  {
    const char* s = env->GetStringUTFChars(raw(), 0);
    if(s)
    {
      std::string tmp(s);
      env->ReleaseStringUTFChars(raw(), s);
      return tmp;
    }
    else
      return std::string();
  }


  jstring s;
  JNIEnv* env;
};

inline std::ostream& operator<<(std::ostream& os, string s)
{
  std::ostream::sentry sentry(os);

  const char* str = s.env->GetStringUTFChars(s.raw(), 0);
  if(str)
  {
    os << str;
    s.env->ReleaseStringUTFChars(s.raw(), str);
    return os;
  }
  else
    return os << "[allocation error while returning string]";
}

}

#endif

