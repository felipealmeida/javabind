// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_CONSTRUCTOR_HPP
#define JVB_CONSTRUCTOR_HPP

#include <jvb/class.hpp>
#include <jvb/detail/overload_set.hpp>
#include <jvb/detail/new_object_functor.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/mpl/push_front.hpp>

#include <jni.h>

namespace jvb {

template <typename F>
struct constructor : detail::overload_set
<constructor<F>, boost::function_types::function_arity<F>::type::value+1
 ,
 typename boost::mpl::push_front
 <
   typename boost::function_types::parameter_types<F>::type
   , jvb::class_
 >::type
 , typename boost::function_types::result_type<F>::type
 , detail::new_object_functor<typename boost::function_types::result_type<F>::type> const
 >
{
  typedef detail::new_object_functor<typename boost::function_types::result_type<F>::type>
  functor_type;
  typedef detail::overload_set
<constructor<F>, boost::function_types::function_arity<F>::type::value+1
 , typename boost::mpl::push_front
   <
     typename boost::function_types::parameter_types<F>::type
     , jvb::class_
   >::type
 , typename boost::function_types::result_type<F>::type
 , detail::new_object_functor<typename boost::function_types::result_type<F>::type> const
 > base_type;
  constructor( ::jmethodID id)
    : base_type(functor_type(id)) {}
};

}

#endif
