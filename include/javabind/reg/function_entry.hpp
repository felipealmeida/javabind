// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_REG_FUNCTION_ENTRY_HPP
#define JAVABIND_REG_FUNCTION_ENTRY_HPP

#include <boost/fusion/container/vector.hpp>

namespace javabind { namespace reg {

template <typename Sig, typename F, bool st, typename S = boost::fusion::vector0<> >
struct function_entry
{
  enum { is_static = st };

  function_entry(const char* name, F f, S s = boost::fusion::vector0<>())
    : name(name), f(f), s(s) {}

  const char* name;
  F f;
  S s;
};

} }

#endif
