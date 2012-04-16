// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_SELECT_CALL_FUNCTOR_HPP
#define JAVABIND_DETAIL_SELECT_CALL_FUNCTOR_HPP

#include <javabind/detail/call_void_method_functor.hpp>
#include <javabind/detail/call_boolean_method_functor.hpp>

namespace javabind { namespace detail {

template <typename T>
struct select_call_functor;

template <>
struct select_call_functor<void>
{
  typedef call_void_method_functor type;
};

template <>
struct select_call_functor<jboolean>
{
  typedef call_boolean_method_functor type;
};

} }

#endif
