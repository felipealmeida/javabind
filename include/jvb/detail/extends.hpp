// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_EXTENDS_HPP
#define JVB_DETAIL_EXTENDS_HPP

#include <jvb/object.hpp>

#include <jni.h>

namespace jvb { namespace detail {

template <typename T = jvb::object>
struct extends
{
  typedef T type;
};

} }

#endif
