// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_STATIC_FIELD_HPP
#define JVB_STATIC_FIELD_HPP

#include <jvb/class.hpp>

namespace jvb {

template <typename T>
struct static_field : T
{
  typedef T base_type;

  static_field(Class const& cls, environment e, const char* name)
  {
    
  }
};

}

#endif
