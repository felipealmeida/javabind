// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_REG_FUNCTION_ENTRY_HPP
#define JAVABIND_REG_FUNCTION_ENTRY_HPP

#include <boost/fusion/container/vector.hpp>

namespace javabind { namespace reg {

template <typename Sig, typename F, typename S = boost::fusion::vector0<> >
struct function_entry
{
  function_entry(const char* name, F f, S s = S())
    : name(name), f(f), s(s) {}

  const char* name;
  F f;
  S s;
};

} }

#endif
