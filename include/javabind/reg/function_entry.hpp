// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_REG_FUNCTION_ENTRY_HPP
#define JAVABIND_REG_FUNCTION_ENTRY_HPP

namespace javabind { namespace reg {

template <typename Sig, typename F>
struct function_entry
{
  function_entry(const char* name, F f)
    : name(name), f(f) {}

  const char* name;
  F f;
};

} }

#endif
