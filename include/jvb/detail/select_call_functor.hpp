// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_SELECT_CALL_FUNCTOR_HPP
#define JVB_DETAIL_SELECT_CALL_FUNCTOR_HPP

#include <jvb/detail/call_void_method_functor.hpp>
#include <jvb/detail/call_boolean_method_functor.hpp>
#include <jvb/detail/call_object_method_functor.hpp>
#include <jvb/detail/call_int_method_functor.hpp>
#include <jvb/detail/call_array_byte_method_functor.hpp>
#include <jvb/detail/call_array_object_method_functor.hpp>
#include <jvb/primitives.hpp>

namespace jvb { namespace detail {

template <typename T>
struct select_call_functor;

template <>
struct select_call_functor<void>
{
  typedef call_void_method_functor type;
};

template <>
struct select_call_functor<bool>
{
  typedef call_boolean_method_functor type;
};

template <>
struct select_call_functor<object>
{
  typedef call_object_method_functor type;
};

template <>
struct select_call_functor<int_>
{
  typedef call_int_method_functor type;
};

template <>
struct select_call_functor<array<byte> >
{
  typedef call_array_byte_method_functor type;
};

template <>
struct select_call_functor<array<object> >
{
  typedef call_array_object_method_functor type;
};

} }

#endif
