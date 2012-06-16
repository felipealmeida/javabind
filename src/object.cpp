// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <javabind/class.hpp>

#include <javabind/object.hpp>

#include <ostream>

namespace javabind {

javabind::class_ object::class_() const
{
  return javabind::class_(env->GetObjectClass(o), env);
}

string object::to_string() const
{
  const char sig[] = "()Ljava/lang/String;";
  jmethodID to_string_id = env->GetMethodID(env->GetObjectClass(o), "toString", sig);
  assert(to_string_id != 0);
  jstring s = static_cast<jstring>(static_cast<void*>(env->CallObjectMethod(o, to_string_id)));
  return string(s, env);
}

std::ostream& operator<<(std::ostream& os, object o)
{
  std::ostream::sentry sen(os);
  JNIEnv* env = o.environment();
  assert(env != 0);
  if(o != object::nil(o.environment()))
  {
    string str = o.to_string();
    os << str;
  }
  else
  {
    os << "[nil]";
  }
  return os;
}


}

