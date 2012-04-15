// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_CONSTRUCTOR_HPP
#define JAVABIND_CONSTRUCTOR_HPP

#include <javabind/class.hpp>
#include <javabind/detail/overload_set.hpp>
#include <javabind/detail/new_object_functor.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/mpl/push_front.hpp>

#include <jni.h>

namespace javabind {

template <typename F>
struct constructor : detail::overload_set
<constructor<F>, boost::function_types::function_arity<F>::type::value+1
 ,
 typename boost::mpl::push_front
 <
   typename boost::function_types::parameter_types<F>::type
   , javabind::class_
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
     , javabind::class_
   >::type
 , typename boost::function_types::result_type<F>::type
 , detail::new_object_functor<typename boost::function_types::result_type<F>::type> const
 > base_type;
  constructor( ::jmethodID id, JNIEnv* env)
    : base_type(functor_type(id, env)) {}
};

}

#endif
