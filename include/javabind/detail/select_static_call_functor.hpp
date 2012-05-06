// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_SELECT_STATIC_CALL_FUNCTOR_HPP
#define JAVABIND_DETAIL_SELECT_STATIC_CALL_FUNCTOR_HPP

#include <javabind/detail/call_static_void_method_functor.hpp>
#include <javabind/detail/call_static_boolean_method_functor.hpp>
#include <javabind/primitives.hpp>

namespace javabind { namespace detail {

template <typename T>
struct select_static_call_functor;

template <>
struct select_static_call_functor<void>
{
  typedef call_static_void_method_functor type;
};

template <>
struct select_static_call_functor<bool>
{
  typedef call_static_boolean_method_functor type;
};

} }

#endif
