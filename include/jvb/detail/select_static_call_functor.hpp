// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_SELECT_STATIC_CALL_FUNCTOR_HPP
#define JVB_DETAIL_SELECT_STATIC_CALL_FUNCTOR_HPP

#include <jvb/detail/call_static_void_method_functor.hpp>
#include <jvb/detail/call_static_boolean_method_functor.hpp>
#include <jvb/primitives.hpp>

namespace jvb { namespace detail {

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
