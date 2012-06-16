// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JAVABIND_STATIC_METHOD_HPP
#define JAVABIND_STATIC_METHOD_HPP

#include <javabind/class.hpp>
#include <javabind/detail/overload_set.hpp>
#include <javabind/detail/select_static_call_functor.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/mpl/push_front.hpp>

#include <jni.h>

namespace javabind {

template <typename F>
struct static_method : detail::overload_set
<static_method<F>, boost::function_types::function_arity<F>::type::value+1
 ,
 typename boost::mpl::push_front
 <
   typename boost::function_types::parameter_types<F>::type
   , javabind::class_
 >::type
 , typename boost::function_types::result_type<F>::type
 , typename detail::select_static_call_functor
   <
     typename boost::function_types::result_type<F>::type
   >::type
 >
{
  typedef typename detail::select_static_call_functor
   <
     typename boost::function_types::result_type<F>::type
   >::type functor_type;
  typedef detail::overload_set
  <static_method<F>, boost::function_types::function_arity<F>::type::value+1
   ,
   typename boost::mpl::push_front
   <
     typename boost::function_types::parameter_types<F>::type
     , javabind::class_
   >::type
   , typename boost::function_types::result_type<F>::type
   , functor_type
  > base_type;
  static_method( ::jmethodID id, JNIEnv* env)
    : base_type(functor_type(id, env)) {}

  jmethodID raw() const { return base_type::functor().raw(); }
};

}

#endif
