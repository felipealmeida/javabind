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
 <typename boost::mpl::push_front
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
  <typename boost::mpl::push_front
   <
     typename boost::function_types::parameter_types<F>::type
   , jvb::environment
   >::type
   , typename boost::function_types::result_type<F>::type
   , functor_type
  > base_type;

  method() : base_type(functor_type(0, 0)), obj(0), method_id(0)
  {
  }
  method(environment e, jobject obj, const char* name)
    : base_type(functor_type(obj, find_id(e, obj, name))), obj(obj), method_id(0)
  {
  }

private:
  static jmethodID find_id(environment e, jobject obj, const char* name)
  {
    jclass cls = e.raw()->GetObjectClass(obj);
    jmethodID id = e.raw()->GetMethodID(cls, name, "(Ljava/lang/String;)V");
    assert(id != 0);
    return id;
  }

  jobject obj;
  jmethodID method_id;
};

}

#endif
