// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JAVABIND_REG_CONSTRUCTOR_HPP
#define JAVABIND_REG_CONSTRUCTOR_HPP

namespace javabind { namespace reg {

struct default_constructor_tag {};

template <typename F>
struct constructor
{
  constructor(F f)
    : f(f) {}

  F f;
};

} }

#endif
