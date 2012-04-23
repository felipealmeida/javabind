// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_NUMBER_HPP
#define JAVABIND_NUMBER_HPP

#ifndef JAVABIND_DISABLE_IOSTREAMS
#include <ostream>
#endif

#include <jni.h>

namespace javabind {

template <typename T, typename Tag = void>
struct number
{
  typedef T java_type;
  
  number(T r)
  : r(r) {}

  T raw() const { return r; }
  operator T() const { return r; }

private:
  T r;
};

#ifndef JAVABIND_DISABLE_IOSTREAMS
template <typename T, typename Tag>
std::ostream& operator<<(std::ostream& os, number<T, Tag> i)
{
  return os << i.raw();
}
#endif

}

#endif
