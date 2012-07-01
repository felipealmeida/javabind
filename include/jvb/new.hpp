// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_NEW_HPP
#define JVB_NEW_HPP

#include <jvb/environment.hpp>
#include <jvb/reference.hpp>

namespace jvb {

template <typename T>
ref<T> new_(environment e)
{
  return ref<T>(e);
}

}

#endif
