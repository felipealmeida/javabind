// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_SELECT_STATIC_CALL_FUNCTOR_HPP
#define JVB_DETAIL_SELECT_STATIC_CALL_FUNCTOR_HPP

#include <jvb/detail/call_static_void_method_functor.hpp>
#include <jvb/detail/call_static_boolean_method_functor.hpp>
#include <jvb/detail/call_static_byte_method_functor.hpp>
#include <jvb/detail/call_static_char_method_functor.hpp>
#include <jvb/detail/call_static_double_method_functor.hpp>
#include <jvb/detail/call_static_float_method_functor.hpp>
#include <jvb/detail/call_static_int_method_functor.hpp>
#include <jvb/detail/call_static_long_method_functor.hpp>
#include <jvb/detail/call_static_object_method_functor.hpp>
#include <jvb/detail/call_static_short_method_functor.hpp>
#include <jvb/primitives.hpp>

namespace jvb { namespace detail {

template <typename T, typename Enable = void>
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

template <>
struct select_static_call_functor<byte>
{
  typedef call_static_byte_method_functor type;
};

template <>
struct select_static_call_functor<char_>
{
  typedef call_static_char_method_functor type;
};

template <>
struct select_static_call_functor<double_>
{
  typedef call_static_double_method_functor type;
};

template <>
struct select_static_call_functor<float_>
{
  typedef call_static_float_method_functor type;
};

template <>
struct select_static_call_functor<short_>
{
  typedef call_static_short_method_functor type;
};

template <>
struct select_static_call_functor<int_>
{
  typedef call_static_int_method_functor type;
};

template <>
struct select_static_call_functor<long_>
{
  typedef call_static_long_method_functor type;
};

template <typename T>
struct select_static_call_functor
 <T, typename boost::enable_if<boost::is_base_of<object, T> >::type>
{
  typedef call_static_object_method_functor<T> type;
};

} }

#endif
