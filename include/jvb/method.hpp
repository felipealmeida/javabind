// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_METHOD_HPP
#define JVB_METHOD_HPP

#include <jvb/object.hpp>
#include <jvb/detail/overload_set.hpp>
#include <jvb/detail/select_call_functor.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/mpl/push_front.hpp>

#include <jni.h>

namespace jvb {

template <typename F>
struct method : detail::overload_set
 <
  /*method<F>//, boost::function_types::function_arity<F>::type::value+1
    ,*/ typename boost::mpl::push_front
  <
     typename boost::function_types::parameter_types<F>::type
     , jvb::environment
  >::type
 , typename boost::function_types::result_type<F>::type
 , typename detail::select_call_functor
   <
     typename boost::function_types::result_type<F>::type
   >::type
 >
{
  typedef typename detail::select_call_functor
   <
     typename boost::function_types::result_type<F>::type
   >::type functor_type;
  typedef detail::overload_set
  </*method<F>//, boost::function_types::function_arity<F>::type::value+1
     ,*/ typename boost::mpl::push_front
   <
     typename boost::function_types::parameter_types<F>::type
   , jvb::environment
   >::type
   , typename boost::function_types::result_type<F>::type
   , functor_type
  > base_type;

  method() : obj(0), method_id(0)
  {
  }
  method(jobject obj, const char* name)
    : obj(obj), method_id(0)
  {
  }

private:
  jobject obj;
  jmethodID method_id;
};

// template <typename F>
// struct method : detail::overload_set
// <method<F>, boost::function_types::function_arity<F>::type::value+1
//  ,
//  typename boost::mpl::push_front
//  <
//    typename boost::function_types::parameter_types<F>::type
//    , jvb::object
//  >::type
//  , typename boost::function_types::result_type<F>::type
//  , typename detail::select_call_functor
//    <
//      typename boost::function_types::result_type<F>::type
//    >::type
//  >
// {
//   typedef typename detail::select_call_functor
//    <
//      typename boost::function_types::result_type<F>::type
//    >::type functor_type;
//   typedef detail::overload_set
//   <method<F>, boost::function_types::function_arity<F>::type::value+1
//    ,
//    typename boost::mpl::push_front
//    <
//      typename boost::function_types::parameter_types<F>::type
//      , jvb::object
//    >::type
//    , typename boost::function_types::result_type<F>::type
//    , functor_type
//   > base_type;
//   method( ::jmethodID id )
//     : base_type(functor_type(id)) {}

//   jmethodID raw() const { return base_type::functor().raw(); }
// };

}

#endif
