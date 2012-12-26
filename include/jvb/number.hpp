// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_NUMBER_HPP
#define JVB_NUMBER_HPP

#ifndef JVB_DISABLE_IOSTREAMS
#include <ostream>
#endif

#include <jni.h>

namespace jvb {

template <typename T, typename Tag>
struct number
{
  typedef T java_type;
  
  number() : r(T()) {}
  number(T r)
  : r(r) {}

  T raw() const { return r; }
  operator T() const { return r; }

private:
  T r;
};

template <typename T, typename Tag>
bool operator==(number<T, Tag> lhs, number<T, Tag> rhs)
{
  return lhs.raw() == rhs.raw();
}

#ifndef JVB_DISABLE_IOSTREAMS
template <typename T, typename Tag>
std::ostream& operator<<(std::ostream& os, number<T, Tag> i)
{
  return os << i.raw();
}
#endif

}

#endif
