// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_METHOD_HPP
#define JAVABIND_METHOD_HPP

#include <javabind/object.hpp>
#include <javabind/detail/overload_set.hpp>
#include <javabind/detail/call_void_method_functor.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/mpl/push_front.hpp>

#include <jni.h>

namespace javabind {

template <typename F>
struct method : detail::overload_set
<method<F>, boost::function_types::function_arity<F>::type::value+1
 ,
 typename boost::mpl::push_front
 <
   typename boost::function_types::parameter_types<F>::type
   , javabind::object
 >::type
 , typename boost::function_types::result_type<F>::type
 , detail::call_void_method_functor
 >
{
  typedef detail::call_void_method_functor functor_type;
  typedef detail::overload_set
  <method<F>, boost::function_types::function_arity<F>::type::value+1
   ,
   typename boost::mpl::push_front
   <
     typename boost::function_types::parameter_types<F>::type
     , javabind::object
   >::type
   , typename boost::function_types::result_type<F>::type
   , detail::call_void_method_functor
  > base_type;
  method( ::jmethodID id, JNIEnv* env)
    : base_type(functor_type(id, env)) {}

  jmethodID raw() const { return base_type::functor().raw(); }
};

}

#endif
