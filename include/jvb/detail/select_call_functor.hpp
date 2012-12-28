// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_SELECT_CALL_FUNCTOR_HPP
#define JVB_DETAIL_SELECT_CALL_FUNCTOR_HPP

#include <jvb/detail/call_void_method_functor.hpp>
#include <jvb/detail/call_boolean_method_functor.hpp>
#include <jvb/detail/call_byte_method_functor.hpp>
#include <jvb/detail/call_char_method_functor.hpp>
#include <jvb/detail/call_int_method_functor.hpp>
#include <jvb/detail/call_short_method_functor.hpp>
#include <jvb/detail/call_long_method_functor.hpp>
#include <jvb/detail/call_float_method_functor.hpp>
#include <jvb/detail/call_double_method_functor.hpp>
#include <jvb/detail/call_object_method_functor.hpp>
#include <jvb/detail/call_array_method_functor.hpp>
#include <jvb/detail/call_string_method_functor.hpp>
#include <jvb/primitives.hpp>

namespace jvb { namespace detail {

template <typename T, typename Enable = void>
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
struct select_call_functor<byte>
{
  typedef call_byte_method_functor type;
};

template <>
struct select_call_functor<char_>
{
  typedef call_char_method_functor type;
};

template <>
struct select_call_functor<short_>
{
  typedef call_short_method_functor type;
};

template <>
struct select_call_functor<int_>
{
  typedef call_int_method_functor type;
};

template <>
struct select_call_functor<long_>
{
  typedef call_long_method_functor type;
};

template <>
struct select_call_functor<float_>
{
  typedef call_float_method_functor type;
};

template <>
struct select_call_functor<double_>
{
  typedef call_double_method_functor type;
};

template <>
struct select_call_functor<string>
{
  typedef call_string_method_functor type;
};

template <typename T>
struct select_call_functor
 <T, typename boost::enable_if<boost::is_base_of<object, T> >::type>
{
  typedef call_object_method_functor<T> type;
};

template <typename T>
struct select_call_functor<array<T> >
{
  typedef call_array_method_functor<array<T> > type;
};

// template <>
// struct select_call_functor<int_>
// {
//   typedef call_int_method_functor type;
// };

// template <>
// struct select_call_functor<array<byte> >
// {
//   typedef call_array_byte_method_functor type;
// };

// template <>
// struct select_call_functor<array<object> >
// {
//   typedef call_array_object_method_functor type;
// };

} }

#endif
