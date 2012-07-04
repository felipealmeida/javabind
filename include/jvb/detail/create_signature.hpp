// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_CREATE_SIGNATURE_HPP
#define JVB_DETAIL_CREATE_SIGNATURE_HPP

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/is_member_function_pointer.hpp>

namespace jvb { namespace detail {

template <typename F, bool>
struct create_signature_aux;

template <typename F>
struct create_signature_aux<F, true>
{
  typedef typename boost::function_types::parameter_types<F>::type
    parameter_types;
  typedef typename boost::mpl::push_front
  <parameter_types
   , typename boost::function_types::result_type<F>::type>::type types;
  typedef typename boost::function_types::function_type<types>::type type;
};

template <typename F>
struct create_signature
  : create_signature_aux
  <F, boost::function_types::is_member_function_pointer<F>::type::value>
{};

} }

#endif
