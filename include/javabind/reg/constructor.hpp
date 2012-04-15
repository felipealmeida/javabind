// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

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
