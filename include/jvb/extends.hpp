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

template <typename D, typename T>
struct extends : T
{
  typedef D class_type;
  typedef extends<D, T> base_type;

  extends(jvb::environment e, const char* name)
    : T(e, name)
  {}
};

}
#endif
