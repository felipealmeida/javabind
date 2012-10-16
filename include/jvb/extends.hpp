// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_EXTENDS_HPP
#define JVB_EXTENDS_HPP

#include <jvb/class.hpp>
#include <jvb/environment.hpp>

namespace jvb {

template <typename T>
struct extends : T
{
  typedef extends<T> class_;

  extends(jvb::environment e, const char* name)
    : T(e), cls(e, name)
  {}

  jvb::jcl::java::lang::Class get_class() const { return cls; }
private:
  jvb::jcl::java::lang::Class cls;
};

}
#endif
